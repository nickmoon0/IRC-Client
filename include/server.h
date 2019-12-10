#ifndef SERVER_H
#define SERVER_H

// Standard headers
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

// Project headers
#include "user.h"
#include "interface.h"

#include "handling/requestHandler.h"

class server {
public:

	server(user* currentUser, interface* mainInterface, std::string serverAddress, std::string port);
	server(user* currentUser, interface* mainInterface, std::string serverAddress);
	
	// Connection stuff
	int createConnection();

	// Command/Response stuff
	void handleCommand(std::string input);

private:

	// Server details/data
	const char DEFAULT_PORT[5] = "6667";
	std::string port;
	std::string serverAddress;
	std::vector<std::string>* serverIPList;
	int sockfd;
	struct addrinfo* serverInfo;
	int getSocket();

	// Input/Response handling
	user* currentUser;
	interface* mainInterface;

	requestHandler *reqHandler;
};

#endif









