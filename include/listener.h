#ifndef LISTENER_H
#define LISTENER_H

// Standard headers
#include <thread>
#include <string>

// Project headers
#include "server.h"
#include "responseHandler.h"
#include "user.h"

class listener {
public:

	listener(server* serv, user* currentUser);
	~listener();

	int start();
	int joinThread();

private:

	// Important details
	server* serv;
	user* currentUser;

	// Thread stuff
	std::thread *listeningThread;
};

#endif