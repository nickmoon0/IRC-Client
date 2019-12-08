#include "responseHandler.h"

/*
 * Contructor
 */

responseHandler::responseHandler(user* currentUser, interface* mainInterface) {
	this->currentUser = currentUser;
	this->mainInterface = mainInterface;
}