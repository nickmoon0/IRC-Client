#include "responseHandler.h"

/*
 * Constructor
 */

responseHandler::responseHandler(interface* mainInterface) {
	this->mainInterface = mainInterface;
	this->serverList = new std::vector<ServerReceiver*>();
}

/*
 * Getting server ready
 */

int responseHandler::addServer(server* s) {
	
}

/*
 * Handling response
 */

void responseHandler::handleResponse(int socket) {

}

