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
	std::string toPrint;

	// Remove all new line characters before printing
    for (int i = 0; i < res.length(); i++) {
		if (res.at(i) == '\n') {
			continue;
		}

		//if (res.at(i) == '^') {
		//	continue;
		//}

		toPrint += res.at(i);
	}

	mainInterface->outputMessage(toPrint);
	//mainInterface->outputMessage("");
}