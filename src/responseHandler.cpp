#include "responseHandler.h"
#include <vector>

/*
 * Contructor
 */

responseHandler::responseHandler(user* currentUser, interface* mainInterface, server* serv) {
	this->currentUser = currentUser;
	this->mainInterface = mainInterface;
	this->serv = serv;

	this->MOTDVec = nullptr;
}

/*
 * Handler
 */

// Used to receive message chunk and split into induvidual messages
void responseHandler::handleResponse(std::string res) {
	// Create buffer and vector for induvidual messages
	std::string buffer;
	std::vector<std::string> responseVec = std::vector<std::string>();

	// Split the one long message at \r\n and put into vector
	for (int i = 0; i < res.length(); i++) {

		// Split string at CR-LF as this marks the end of a message
		if (res.at(i) == '\r' && res.at(i + 1) == '\n') {
			responseVec.push_back(buffer);
			buffer.clear();
			i++; // Add 1 to i because the next character is \n so we need to skip it
			
			continue;
		}

		if (i == res.length() - 1) { // If the loop is at the end just add the rest of the message to the buffer
			buffer += res.at(i);
			responseVec.push_back(buffer);
			buffer.clear();
			continue;
		}

		buffer += res.at(i);
	}

	for (int i = 0; i < responseVec.size(); i++) {
		directMessage(responseVec.at(i));
	}

}

// This is used to direct each message to its correct handler
void responseHandler::directMessage(std::string msg) {
	// ---------------------------------------------------------
	// Split string into vector

	std::string buffer;
	std::vector<std::string> msgVec = std::vector<std::string>();
	char delimiter = ' ';


	for (int i = 0; i < msg.length(); i++) {
		
		if (msg.at(i) == delimiter) {
			msgVec.push_back(buffer);
			buffer.clear();
			continue;
		}

		buffer += msg.at(i);

		if (i == msg.length() - 1) {
			msgVec.push_back(buffer);
			buffer.clear();
			continue;
		}
	
	}

	// ---------------------------------------------------------
	// Determine what the command for each msg is and handle it
	
	// If not enough parameters or arguments are provided
	if (msgVec.size() <= 1) {
		//mainInterface->outputMessage("Malformed server response:");
		//printRawMessage(msg); // Print whole message raw
		return;
	}

	int replyNum;
	std::string commandStr = msgVec.at(1);

	try {
	
		replyNum = std::stoi(commandStr);
		// Numeric reply

		switch (replyNum) {

			// Standard replies
			case RPL_WELCOME:
			case RPL_YOURHOST:
			case RPL_CREATED:
			handleStandard(msgVec);
			break;

			// LUSER replies
			case RPL_LUSERCLIENT:
			case RPL_LUSEROP:
			case RPL_LUSERUNKNOWN:
			case RPL_LUSERCHANNELS:
			case RPL_LUSERME:
			handleLusers(msgVec);
			break;

			case RPL_MOTDSTART:
			case RPL_MOTD:
			case RPL_ENDOFMOTD:
			handleMOTD(msgVec);
			break;

			default:
			break;
		}

	} catch (std::invalid_argument e) {
	
		//mainInterface->outputMessage("Non-numeric reply: " + msg);
	
	} catch (std::out_of_range e) {

		// Malformed server response
	
	}


}

/*
 * Specific handlers
 */

// -------------------------------------------------------------------------------------
// Standard 

void responseHandler::handleStandard(std::vector<std::string> msgVec) {
	// Check to make sure that response is standard

	if (msgVec.at(0).at(0) != MESSAGE_PREFIX) {
		mainInterface->outputMessage("Mishandled response (Accidentally sent to handleStandardResponse)");
		mainInterface->outputMessage("Message command: " + msgVec.at(1));
		return;
	}

	std::string src = msgVec.at(0).substr(1); // Make the prefix a string without ':' at front	
	std::string dst = msgVec.at(2);

	// Iterate through the rest of the message to get the body
	int bodyStartIndex = 3;
	std::string body = getBody(bodyStartIndex, msgVec);

	std::string toPrint = "[" + src + " -> " + dst + "] " + body;

	mainInterface->outputMessage(toPrint);

}

// -------------------------------------------------------------------------------------
// Lusers

void responseHandler::handleLusers(std::vector<std::string> msgVec) {
	std::string src = msgVec.at(0).substr(1); // Need substr 1 to remove prefix
	std::string dst = msgVec.at(2);
	std::string num; // Number of clients or users or channels or whatever
	std::string body;

	std::string toPrint;

	// Change how message is constructed/displayed if it is RPL_LUSERME
	std::string command = msgVec.at(1);
	int bodyStartIndex;
	if (std::stoi(command) == RPL_LUSERME) {
		bodyStartIndex = 3;

		body = getBody(bodyStartIndex, msgVec);
		toPrint = "[" + src + " -> " + dst + "] " + body;

	} else {
		bodyStartIndex = 4;
		body = getBody(bodyStartIndex, msgVec);
		num = msgVec.at(3);
		toPrint = "[" + src + " -> " + dst + "] " + num + " " + body;
	
	}

	mainInterface->outputMessage(toPrint);	
}

// -------------------------------------------------------------------------------------
// MOTD

void responseHandler::handleMOTD(std::vector<std::string> msgVec) {
	
	// Create new vector object if one does not already exist
	if (MOTDVec == nullptr) {
		MOTDVec = new std::vector<std::string>();
	}

	std::string command = msgVec.at(1);

	// If it is the start of a message OR if it is body/middle of message
	if (command == std::to_string(RPL_MOTDSTART) || command == std::to_string(RPL_MOTD)) {
		int bodyStartIndex = 3;
		MOTDVec->push_back(getBody(bodyStartIndex, msgVec));
		return;
	}

	// If the whole message has been received
	if (command == std::to_string(RPL_ENDOFMOTD)) {

		std::string printString;
		for (int i = 0; i < MOTDVec->size(); i++) {
			printString += MOTDVec->at(i) + "\n";
		}

		mainInterface->outputMessage(printString);

		delete MOTDVec;
		MOTDVec = nullptr;
	}
}

/*
 * Misc
 */

std::string responseHandler::getBody(int startIndex, std::vector<std::string> msgVec) {
	std::string body;

	for (int i = startIndex; i < msgVec.size(); i++) {
		body += msgVec.at(i) + " ";
	}

	if (body.at(0) == MESSAGE_PREFIX) {
		body = body.substr(1);
	}

	return body; 
}

/*
 * Print raw message
 */

void responseHandler::printRawMessage(std::string res) {
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