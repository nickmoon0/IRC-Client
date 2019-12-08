#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

// Standard headers
#include <string>
#include <vector>
#include <thread>

// Project headers
#include "interface.h"
#include "server.h"

struct ServerReceiver {

	server* ss_server;
	std::thread* ss_receiveThread;

};

class responseHandler {
public:

	responseHandler(interface* mainInterface);
	
	int addServer(server* s);

	void handleResponse(int socket);

private:

	// Server stuff
	std::vector<ServerReceiver*>* serverList;


	// Misc
	interface* mainInterface;

};

#endif