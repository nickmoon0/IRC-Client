#include "listener.h"

/*
 * Constructor
 */

listener::listener(server* serv, user* currentUser) {
	this->serv = serv;
	this->currentUser = currentUser;

	this->listeningThread = nullptr;
}

listener::~listener() {
	delete listeningThread;
}

int listeningThread::joinThread() {
	if (!listeningThread || !listeningThread.joinable()) {
		return -1;
	}

	listeningThread.join();
	return 0;
}

/*
 * Listening
 */ 

int listener::start() {
	listeningThread = new std::thread(&listener::listen, this);
}

int listener::listen() {
	// Get the socket and create message buffer
	int socket = serv->getSocket();
	char msgBuffer[serv->MAX_MESSAGE_LEN];

	// While the connection is open
	while (serv->getConnectionOpen()) {
		
		// Clear the buffer
		memset(msgBuffer, 0, sizeof msgBuffer);
		
		// Receive a message
		int bytesReceived = recv(socket, msgBuffer, serv->MAX_MESSAGE_LEN, 0);
	
		// Check that a message was successfully received
		if (bytesReceived <= 0) {
			// fatal error occured or 
			return -1;
		}

		// Convert buffer to string
		std::string strMsg = msgBuffer;

		// Handle string and clear string-buffer
		respHandler->handleResponse(strMsg);
		strMsg.clear();
	}
	return 0;
}