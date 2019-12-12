#ifndef SERVER_H
#define SERVER_H

// Standard headers
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

// Standard headers
#include <thread>

// Project headers

class server {
public:

	// constructors
	server(std::string serverAddress, std::string port);
	server(std::string serverAddress);

	// Connection stuff
	int createConnection();
	int getSocket();

	// Thread stuff
	int joinThread();
	//int startListener(int (*listenerFunc)());
private:

	// Server details/data
	const char DEFAULT_PORT[5] = "6667";
	
	std::string port;
	std::string serverAddress;

	std::vector<std::string>* serverIPList;

	int sockfd;
	struct addrinfo* serverInfo;

	// Listener stuff
	std::thread *listenerThread;
};

#endif