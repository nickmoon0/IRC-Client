#ifndef LISTENER_H
#define LISTENER_H

// Standard headers
#include <vector>
#include <thread>
#include <string>

// Project headers
#include "server.h"
#include "listener.h"
#include "user.h"
#include "interface.h"

#include "responseHandler.h"

struct ServerListener {
	server* sl_server;
	std::thread *sl_listenerThread;
	bool sl_connectionActive;
};

class listener {
public:

	listener(user* currentUser, interface* mainInterface);
	int addServer(std::string serverAddress, std::string port);

private:

	// Message data
	const int MAX_MSG_LENGTH = 512;

	// Listener function
	void listenerFunc(int socket, bool* connectionOpen);

	std::vector<ServerListener*>* serverList;

	// Message handling
	responseHandler* resHandler;
};

#endif