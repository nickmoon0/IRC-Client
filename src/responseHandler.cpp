#include "responseHandler.h"
#include <vector>

/*
 * Contructor
 */

responseHandler::responseHandler(user* currentUser, interface* mainInterface, server* serv) {
	this->currentUser = currentUser;
	this->mainInterface = mainInterface;
	this->serv = serv;
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
		mainInterface->outputMessage("Malformed server response:");
		printRawMessage(msg); // Print whole message raw
		return;
	}

	int replyNum;
	std::string commandStr = msgVec.at(1);

	try {
	
		replyNum = std::stoi(commandStr);
		// Numeric reply

		switch (replyNum) {

			// Standard replies
			case serverReply::RPL_WELCOME:
			case serverReply::RPL_YOURHOST:
			case serverReply::RPL_CREATED:
			handleStandard(msgVec);
			break;

			// LUSER replies
			case serverReply::RPL_LUSERCLIENT:
			case serverReply::RPL_LUSEROP:
			case serverReply::RPL_LUSERUNKNOWN:
			case serverReply::RPL_LUSERCHANNELS:
			case serverReply::RPL_LUSERME:
			handleLusers(msgVec);
			break;

			default:
			break;
		}

	} catch (std::invalid_argument e) {
	
		mainInterface->outputMessage("Non-numeric reply: " + msg);
	
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
	std::string body;
	int bodyStartIndex = 3;
	
	for (int i = bodyStartIndex; i < msgVec.size(); i++) {
		body += msgVec.at(i) + " "; 
	}
	body = body.substr(1); // Remove colon from message body	

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
	if (std::stoi(command) == RPL_LUSERME) {
		
		body = msgVec.at(3).substr(1); // Use substr to remove prefix
		toPrint = "[" + src + " -> " + dst + "] " + body;

	} else {

		body = msgVec.at(4).substr(1);
		num = msgVec.at(3);
		toPrint = "[" + src + " -> " + dst + "] " + num + " " + body;
	
	}

	mainInterface->outputMessage(toPrint);	
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