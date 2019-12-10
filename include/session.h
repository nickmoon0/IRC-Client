#ifndef SESSION_H
#define SESSION_H

// Standard headers
#include <vector>
#include <thread>

// Project headers
#include "interface.h"
#include "server.h"

struct ServerListener {
	server* sl_server;
	std::thread* sl_listenerThread;
	bool sl_connectionActive;
};

class session {
public:

	session();
	~session();

	void start();

private:

	// Interface stuff
	interface* mainInterface;

	std::vector<ServerListener*>* serverList;

};

#endif