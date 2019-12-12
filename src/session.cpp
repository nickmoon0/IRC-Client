// Standard headers
#include <sys/socket.h>

// Project headers
#include "session.h"

/*
 * Constructors/Destructors
 */

session::session() {
	mainInterface = new interface();
	currentUser = new user();

	respHandler = new responseHandler(currentUser, mainInterface);
}

session::~session() {
	delete respHandler;

	mainInterface->destroyWin();
	delete mainInterface;

	delete currentUser;
}

/*
 * Starting functions
 */

void session::start() {
	mainInterface->initInterface();

	while (true) {
		mainInterface->getInput();
	}

}

/*
 * Listener
 */

int session::listenerFunc(server* serv) {
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