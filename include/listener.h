#ifndef LISTENER_H
#define LISTENER_H

// Standard headers
#include <vector>
#include <thread>

// Project headers
#include "server.h"

struct ServerListener {
	server* sl_server;
	std::thread *sl_listenerThread;
	bool sl_connectionActive;
};

class listener {
public:

	int addServer(std::string serverAddress, std::string port);

private:

	// Listener function
	void listenerFunc();

	std::vector<ServerListener*>* serverList;

};

#endif