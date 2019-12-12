// Standard headers
#include <sys/socket.h>

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

	mainInterface = new interface();
	currentUser = new user();

	respHandler = new responseHandler(currentUser, mainInterface);
}

session::~session() {
	delete respHandler;

	mainInterface->destroyWin();
	delete mainInterface;

	delete currentUser;

	for (int i = 0; i < serverList->size(); i++) {
		serverList->at(i)->joinThread();
	}
	delete serverList;
}

/*
 * Starting functions
 */

void session::start() {
	mainInterface->initInterface();

	while (true) {
		std::string input = mainInterface->getInput();

		if (serverHandling(input) != 0) {
			// handleResponse(input)
		}
	}

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
			// Switch
		} else {
			return 1;
		}
		return 0;
	} 
	return 1;
}

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

		if (serverList->at(i)->getServerAddress() == serverAddress) {
			mainInterface->outputMessage("Server has already been added");
			return -1;
		}

		for (int x = 0; x < serverList->at(i)->getServerIPList()->size(); x++) {
			if (serverList->at(i)->getServerIPList()->at(x) == serverAddress) {
				mainInterface->outputMessage("Server has already been added");
				return -1;
			}
		}

	}

	mainInterface->outputMessage("No conflicts found");

	server* s;

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
	int (*listenerFunc_ptr)(server* serv, responseHandler* respHandler) = listenerFunc;
	s->startListener(listenerFunc_ptr, respHandler);

	serverList->push_back(s);
	mainInterface->outputMessage(serverAddress + " has been successfully added");
	s = nullptr;
	return 0;
}

int session::removeServer(std::vector<std::string> inputVec) {

}

int session::switchServer(std::vector<std::string> inputVec) {

}

/*
 * Listener
 */

int session::listenerFunc(server* serv, responseHandler* respHandler) {
	// Get the socket and create message buffer
	int socket = serv->getSocket();
	char msgBuffer[serv->MAX_MESSAGE_LEN];

	// While the connection is open
	while (serv->getConnectionOpen()) {
		
		memset(msgBuffer, 0, sizeof msgBuffer);
		
		int bytesReceived = recv(socket, msgBuffer, serv->MAX_MESSAGE_LEN, 0);
	
		if (bytesReceived <= 0) {
			// fatal error occured or 
			return -1;
		}

		std::string strMsg = msgBuffer;
		respHandler->handleResponse(strMsg);
	}
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



