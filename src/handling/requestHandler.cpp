#include "handling/requestHandler.h"

/*
 * Commands initialisation
 */

const std::string commands::JOIN = "join";

/*
 * Constructor
 */

requestHandler::requestHandler(user* currentUser, interface* mainInterface, int socket) : handler(currentUser, mainInterface, socket) {

}

/*
 * Handler
 */

void requestHandler::handleInput(std::string input, int socket) {
	if (input.at(0) == this->COMMAND_PREFIX) {
		
		std::vector<std::string> inputVec = splitString(input.substr(1));

		if (inputVec.at(0) == commands::JOIN) {
			// Execute join command
		}

	} else {
	
		// message
	
	}
}