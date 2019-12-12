#include "responseHandler.h"

/*
 * Contructor
 */

responseHandler::responseHandler(user* currentUser, interface* mainInterface) {
	this->currentUser = currentUser;
	this->mainInterface = mainInterface;
}

/*
 * Handler
 */

void responseHandler::handleResponse(std::string res) {
	mainInterface->outputMessage(res);
}