#include "responseHandler.h"
#include <vector>

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
	std::string buffer;
	std::vector<std::string> printVec = std::vector<std::string>();

	for (int i = 0; i < res.length(); i++) {
		if (res.at(i) == '\r' && res.at(i + 1) == '\n') {
			printVec.push_back(buffer);
			buffer.clear();
			i++;
			continue;
		}

		if (i == res.length() - 1) {
			buffer += res.at(i);
			printVec.push_back(buffer);
			buffer.clear();
			continue;
		}

		buffer += res.at(i);
	}

	for (int i = 0; i < printVec.size(); i++) {
		mainInterface->outputMessage(printVec.at(i));
	}
}