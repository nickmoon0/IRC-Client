#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

// Standard headers
#include <string>

// Project headers
#include "handling/handler.h"

#include "user.h"
#include "interface.h"

struct commands {
	static const std::string JOIN; // used to join channel
};

class requestHandler : public handler {
public:

	requestHandler(user* currentUser, interface* mainInterface, int socket);
	void handleInput(std::string input, int socket);

private:

	const char COMMAND_PREFIX = '.';

	// currentUser in parent class
	// mainInterface in parent class

};

#endif