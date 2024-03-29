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

class server {
public:

	// Server details/data
	const char DEFAULT_PORT[5] = "6667";
	const int MAX_MESSAGE_LEN = 512;

	// constructors
	server(std::string serverAddress, std::string port);
	server(std::string serverAddress);

	// Connection stuff
	int createConnection();
	int getSocket();
	std::string getPort();
	bool getConnectionOpen();

	std::string getServerAddress();
	std::vector<std::string>* getServerIPList();

	// Send stuff
	int sendMessage(std::string msg);

private:

	std::string port;
	std::string serverAddress;

	std::vector<std::string>* serverIPList;

	int sockfd;
	struct addrinfo* serverInfo;

	// Listener stuff
	std::thread *listenerThread;
	bool connectionOpen;
};

#endif