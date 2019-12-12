#ifndef SESSION_H
#define SESSION_H

// Project headers
#include "interface.h"
#include "server.h"
#include "user.h"
#include "responseHandler.h"

class session {
public:

	session();
	~session();

	void start();

private:

	// User stuff
	user* currentUser;

	// Interface stuff
	interface* mainInterface;

	// Listener stuff
	int listenerFunc(server* serv);
	responseHandler *respHandler;
};

#endif