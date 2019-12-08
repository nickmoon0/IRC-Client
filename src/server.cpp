#include "server.h"

/*
 * Constructor
 */

server::server(std::string serverAddress, std::string port) {
	this->serverAddress = serverAddress;
	this->port = port;
}

server::server(std::string serverAddress) {
	this->serverAddress = serverAddress;

	this->port = DEFAULT_PORT;
}