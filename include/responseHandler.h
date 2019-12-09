#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

// Standard headers
#include <vector>
#include <thread>
#include <string>

// Project headers
#include "user.h"
#include "interface.h"
#include "server.h"

struct ServerListener {
	server* sl_server;
	std::thread *sl_listenerThread;
	bool sl_connectionActive;
};

class responseHandler {
public:

	// Constructor
	responseHandler(user* currentUser, interface* mainInterface);

	// Adding server
	int addServer(std::string serverAddress, std::string port);

private:
	
	// Listener function
	void listenerFunc();


	user* currentUser;
	interface* mainInterface;

	std::vector<ServerListener*>* serverList;

};

#endif