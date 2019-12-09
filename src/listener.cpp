#include "listener.h"

/*
 * Constructor
 */

listener::listener(user* currentUser, interface* mainInterface) {
	this->resHandler = new responseHandler(currentUser, mainInterface);
}

/*
 * Server/Listening functions
 */

int listener::addServer(std::string serverAddress, std::string port = std::string()) {
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
	sl->sl_listenerThread = new std::thread(&listener::listenerFunc, this, sl->sl_server->getSocket(), &sl->sl_connectionActive);

	return 0;
}

void listener::listenerFunc(int socket, bool* connectionOpen) {
	char msgBuffer[MAX_MSG_LENGTH];

	while (*connectionOpen) {
		memset(msgBuffer, 0, sizeof msgBuffer);

		int bytesReceived = recv(socket, msgBuffer, MAX_MSG_LENGTH, 0);

		// If connection closed by server or fatal error occurs
		if (bytesReceived <= 0) {
			*connectionOpen = false;
			continue;
		}

		std::string strMsg = msgBuffer;
		resHandler->handleResponse(strMsg);
	}
}