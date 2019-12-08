#ifndef SERVER_H
#define SERVER_H

// Standard headers
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

// Project headers

class server {
public:

	server(std::string serverAddress, std::string port);
	server(std::string serverAddress);
	
private:

	// Server details
	const char DEFAULT_PORT[5] = "6667";
	std::string port;
	std::string serverAddress;

};

#endif