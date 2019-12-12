#ifndef SESSION_H
#define SESSION_H

// Standard headers
#include <string>
#include <vector>

// Project headers
#include "interface.h"
#include "server.h"
#include "user.h"
#include "responseHandler.h"

struct serverManagementCommands {
	static const std::string CONNECT;
	static const std::string DISCONNECT;
	static const std::string SWITCH; 
};

class session {
public:

	session();
	~session();

	void start();

private:

	// User stuff
	user* currentUser;

	// Interface stuff
	interface* mainInterface;

	// Server stuff
	std::vector<server*>* serverList;

	// Input handling stuff
	const char COMMAND_PREFIX = '.';
	int serverHandling(std::string input);
	
	int addServer(std::vector<std::string> inputVec);
	int removeServer(std::vector<std::string> inputVec);
	int switchServer(std::vector<std::string> inputVec);

	// Listening stuff
	static int listenerFunc(server* serv, responseHandler* respHandler);
	responseHandler *respHandler;

	// Misc
	std::vector<std::string> splitString(std::string str, char delimiter);
};

#endif