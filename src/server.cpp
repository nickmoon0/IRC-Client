// Standard headers
#include <arpa/inet.h>
#include <cstring>

// Project headers
#include "server.h"

/*
 * Constructor
 */

server::server(std::string serverAddress, std::string port) {
	this->serverAddress = serverAddress;
	this->port = port;

	serverIPList = new std::vector<std::string>();

	connectionOpen = false;
}

server::server(std::string serverAddress) {
	this->serverAddress = serverAddress;

	this->port = DEFAULT_PORT;
	serverIPList = new std::vector<std::string>();
}

/*
 * Creating/maintaining connection
 */

int server::createConnection() {
	int status;
	struct addrinfo hints;

	// ------------------------------------------------------------------------------------
	// Clearing hints
	memset(&hints, 0, sizeof(hints));

	// Setting parameters
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// ------------------------------------------------------------------------------------
	// Getting server info
	status = getaddrinfo(serverAddress.c_str(), port.c_str(), &hints, &serverInfo);
	if (status != 0) {
		return -1;
	}

	// ------------------------------------------------------------------------------------
	// Storing all IP addresses
	struct addrinfo *p;
	char ipstr[INET6_ADDRSTRLEN];

	for (p = serverInfo; p != NULL; p = p->ai_next) {
		void *addr;
		int addressSize; 

		if (p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
		} else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		serverIPList->push_back(ipstr);
		memset(ipstr, 0, sizeof ipstr);
	}

	// ------------------------------------------------------------------------------------
	// Creating socket

	sockfd = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
	if (sockfd < 0) {
		return -1;
	}

	// ------------------------------------------------------------------------------------
	// Connect to server

	if (connect(sockfd, serverInfo->ai_addr, serverInfo->ai_addrlen) < 0) {
		return -1;
	}

	connectionOpen = true;
	return 0;
}

/*
 * Send stuff
 */

int server::sendMessage(std::string msg) {
	if (msg.length() > MAX_MESSAGE_LEN - 2) {
		return -1;
	}

	msg += '\r';
	msg += '\n';

	char messageBuffer[msg.length()];
	memset(messageBuffer, 0, sizeof(messageBuffer));

	strcpy(messageBuffer, msg.c_str());

	int bytesSent = send(sockfd, messageBuffer, strlen(messageBuffer), serverInfo->ai_flags);
	if (bytesSent < 0) {
		return -1;
	}
	return 0;
}

/*
 * Getters
 */

int server::getSocket() {
	return this->sockfd;
}

std::string server::getPort() {
	return this->port;
}

bool server::getConnectionOpen() {
	return this->connectionOpen;
}

std::string server::getServerAddress() {
	return this->serverAddress;
}

std::vector<std::string>* server::getServerIPList() {
	return this->serverIPList;
}





