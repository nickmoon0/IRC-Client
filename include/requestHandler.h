#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

// Standard headers
#include <string>

// Project headers
#include "interface.h"
#include "user.h"

struct commands {
	const std::string NICK = "nick";
	const std::string JOIN = "join"; // can be used for channel or server depending on what follows command
	
	const std::string PARK = "part"; // Used to leave channel
	const std::string LEAVE = "leave"; // Used to leave server
	const std::string QUIT = "quit"; // Used to quit client
};

class requestHandler {
public:

	requestHandler(user* currentUser, interface* mainInterface);
	~requestHandler();

	void handleInput(std::string input);

private:

	// Handling data
	const char COMMAND_PREFIX = '.';

	// Misc
	user* currentUser;
	interface* mainInterface;

};

#endif