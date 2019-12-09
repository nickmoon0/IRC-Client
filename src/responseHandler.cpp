#include "responseHandler.h"

/*
 * Contructor
 */

responseHandler::responseHandler(user* currentUser, interface* mainInterface) {
	this->currentUser = currentUser;
	this->mainInterface = mainInterface;

	this->serverList = new std::vector<ServerListener*>();
}

/*
 * Server/Listening functions
 */

int responseHandler::addServer(std::string serverAddress, std::string port = std::string()) {
	// Create empty variables
	server* s;
	ServerListener* sl;	


	// Will initialise server differently depending on whether or not a port was specified
	if (port.empty()) {
		s = new server(serverAddress); // Without port
	} else {
		s = new server(serverAddress, port); // with port
	}

	// If it cant connect to the server delete the server object and return -1
	if(s->createConnection() < 0) {
		delete s;
		return -1;
	}

	sl->sl_server = s;
	sl->sl_connectionActive = true;
	sl->sl_listenerThread = new std::thread(&responseHandler::listenerFunc, this);

}

void responseHandler::listenerFunc() {

}