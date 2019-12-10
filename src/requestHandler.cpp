#include "requestHandler.h"

/*
 * Constructor/Destructor
 */

requestHandler::requestHandler(user* currentUser, interface* mainInterface) {
	this->currentUser = currentUser;
	this->mainInterface = mainInterface;
}

/*
 * Handling
 */

void requestHandler::handleInput(std::string input) {
	if (input.at(0) == COMMAND_PREFIX) {
		
	}
}