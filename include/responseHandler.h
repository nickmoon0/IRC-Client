#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

// Project headers
#include "user.h"
#include "interface.h"
#include "server.h"

class responseHandler {
public:

	responseHandler(user* currentUser, interface* mainInterface);

private:
	
	user* currentUser;
	interface* mainInterface;

};

#endif