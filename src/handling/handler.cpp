#include "handling/handler.h"

/*
 * Constructor
 */

handler::handler(user* currentUser, interface* mainInterface, int socket) {
	this->currentUser = currentUser;
	this->mainInterface = mainInterface;

	this->socket = socket;
}

/*
 * Misc
 */

std::vector<std::string> handler::splitString(std::string str) {
	std::vector<std::string> returnVec = std::vector<std::string>();
	std::string bufferString;

	char delimiter = ' ';

	for (int i = 0; i < str.length(); i++) {
		if (str.at(i) == delimiter) {
			returnVec.push_back(bufferString);
			bufferString.clear();
			continue;
		} else if (i == str.length() - 1) {
			bufferString += str.at(i);
			returnVec.push_back(bufferString);
			bufferString.clear();
			continue;
		}

		bufferString += str.at(i);
	}

	return returnVec;
}