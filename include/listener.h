#ifndef LISTENER_H
#define LISTENER_H

// Standard headers
#include <thread>
#include <string>
#include <cstring>

// Project headers
#include "server.h"
#include "responseHandler.h"
#include "user.h"
#include "interface.h"

class listener {
public:

	listener(server* serv, user* currentUser);
	~listener();

	int start(interface* mainInterface);
	int joinThread();

private:

	// Important details
	server* serv;
	user* currentUser;

	// Thread stuff
	int listen();
	std::thread *listeningThread;
	responseHandler* respHandler;

};

#endif
