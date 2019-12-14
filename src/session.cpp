// Standard headers
#include <sys/socket.h>
#include <iostream>
// Project headers
#include "session.h"

/*
 * Server management commands
 */

const std::string serverManagementCommands::CONNECT = "connectto";
const std::string serverManagementCommands::DISCONNECT = "disconnect";
const std::string serverManagementCommands::SWITCH = "switch";

/*
 * Constructors/Destructors
 */

session::session() {
	serverList = new std::vector<server*>();
	listenerList = new std::vector<listener*>();

	mainInterface = new interface();
	currentUser = new user();

	currentServer = nullptr;
}

session::~session() {
	mainInterface->destroyWin();
	delete mainInterface;
	
	if (listenerList) {
		for (int i = 0; i < listenerList->size(); i++) {
			listenerList->at(i)->joinThread();
		}
		delete listenerList;
	}

	if (currentUser) {
		delete currentUser;
	}
	if (serverList) {
		delete serverList;
	}
	
}

/*
 * Starting functions
 */

void session::start() {
	mainInterface->initInterface();

	while (true) {
		std::string input = mainInterface->getInput();

		if (input == "test") {
			mainInterface->outputMessage("looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
			continue;
		}

		if (input.empty()) {
			continue;
		}

		if (serverHandling(input) != 0) {
			sendRawMsg(input);
		}
	}

}

int session::sendRawMsg(std::string input) {
	if (!currentServer) {
		mainInterface->outputMessage("No server selected");
		return -1;
	}

	if(currentServer->sendMessage(input) < 0) {
		mainInterface->outputMessage("Failed to send message");
		return -1;
	}
	return 0;
}

/*
 * Input handling stuff
 */

int session::serverHandling(std::string input) {
	if (input.at(0) == COMMAND_PREFIX) {
		std::vector<std::string> commandVec = splitString(input.substr(1), ' ');

		if (commandVec.at(0) == serverManagementCommands::CONNECT) {
			
			if(addServer(commandVec) < 0) {
				mainInterface->outputMessage("Failed to add server");
			}

		} else if (commandVec.at(0) == serverManagementCommands::DISCONNECT) {
			// Disconnect
		} else if (commandVec.at(0) == serverManagementCommands::SWITCH) {
			
			switchServer(commandVec);

		} else {
			return 1;
		}
		return 0;
	} 
	return 1;
}

// ---------------------------------------------------------------------
// Add server

int session::addServer(std::vector<std::string> inputVec) {
	// if too little parameters are provided
	if (inputVec.size() <= 1) {
		return -1;
	}

	// Set the server address
	std::string serverAddress = inputVec.at(1);
	mainInterface->outputMessage("Adding server: " + serverAddress);

	// Check to make sure server has not already been added
	for (int i = 0; i < serverList->size(); i++) {

		// If the entered server address
		if (serverList->at(i)->getServerAddress() == serverAddress) {
			mainInterface->outputMessage("Server has already been added");
			return -1;
		}

		// If the serverIPList has been generated
		if (serverList->at(i)->getServerIPList()) {

			// Iterate through serverIPList and make sure none of those match entered address
			for (int x = 0; x < serverList->at(i)->getServerIPList()->size(); x++) {
				if (serverList->at(i)->getServerIPList()->at(x) == serverAddress) {
					mainInterface->outputMessage("Server has already been added");
					return -1;
				}
			}	
		}
		

	}

	mainInterface->outputMessage("No conflicts found");

	server* s;

	// Create server with port and address
	if (inputVec.size() < 3) { // If no port is provided
		
		s = new server(serverAddress);
		mainInterface->outputMessage("Adding server on default port: " + std::string(s->DEFAULT_PORT));
	
	} else if (inputVec.size() >= 3) { // If port is provided
		
		// Set port and create server
		std::string port = inputVec.at(2);
		s = new server(serverAddress, port);
		mainInterface->outputMessage("Adding server on port: " + port);

	}

	// Create connection to server 
	if (s->createConnection() < 0) {
		// Delete server object and return -1 if this fails
		mainInterface->outputMessage(std::string("Failed to create connection with ") + serverAddress + std::string(" on port ") + s->getPort());
		delete s;
		return -1;
	}

	mainInterface->outputMessage("Connected to server");
	serverList->push_back(s);

	// Starting listener
	listener* l = new listener(s, currentUser);
	
	if (l->start(mainInterface) < 0) {
		mainInterface->outputMessage("Failed to start listener for " + serverAddress + ". You will not receive messages from this server");
		delete l;
	} else { // Use an else statement and continue with function as you may be able to create a listener for server later
		listenerList->push_back(l);
		mainInterface->outputMessage("Successfully created listener for server");	
	}
	

	mainInterface->outputMessage(serverAddress + " has been successfully added");
	s = nullptr;

	// Switching server
	std::vector<std::string> switchVec = std::vector<std::string>();

	switchVec.push_back(serverManagementCommands::SWITCH);
	switchVec.push_back(serverList->at(serverList->size() - 1)->getServerAddress());
	
	switchServer(switchVec);
	
	return 0;
}

// ---------------------------------------------------------------------
// Remove server

int session::removeServer(std::vector<std::string> inputVec) {
	return 0;
}

// ---------------------------------------------------------------------
// Switch server

int session::switchServer(std::vector<std::string> inputVec) {
	// If not enough parameters are provided
	if (inputVec.size() <= 1) {
		mainInterface->outputMessage("Not enough parameters provided");
		return -1;
	}

	std::string toSwitch = inputVec.at(1);

	// Check if number was entered
	try {
		long num = stol(toSwitch);
		if (num >= 0) {
			if (num >= serverList->size()) {
				mainInterface->outputMessage("Index for switch is out of range");
				mainInterface->outputMessage("Please remember to use 0 based index\'s");
				return -1;
			}
			currentServer = serverList->at(num);
			mainInterface->outputMessage("Switched to server: " + currentServer->getServerAddress());
			return 0;
		}
	} catch (std::invalid_argument err) {}
	
	server* s;

	// Checking that server exists in serverList
	for (int i = 0; i < serverList->size(); i++) {
		
		// If serverList->at(i) matches the server to switch to
		if (serverList->at(i)->getServerAddress() == toSwitch) {
			// Set s as the server and break
			s = serverList->at(i);
			break;
		}

	}

	// If no server was found
	if (!s) {
		mainInterface->outputMessage("Server was not found");
		return -1;
	}

	currentServer = s;
	mainInterface->outputMessage("Switched to server: " + currentServer->getServerAddress());
	return 0;
}

/*
 * Misc
 */

std::vector<std::string> session::splitString(std::string str, char delimiter) {
	std::vector<std::string> returnVec = std::vector<std::string>();
	std::string buffer;

	for (int i = 0; i < str.length(); i++) {
		if (str.at(i) == delimiter) {
			returnVec.push_back(buffer);
			buffer.clear();
			continue;
		}

		if (i == str.length() - 1) {
			buffer += str.at(i);
			returnVec.push_back(buffer);
			buffer.clear();
			continue;
		}

		buffer += str.at(i);
	}

	return returnVec;
}



