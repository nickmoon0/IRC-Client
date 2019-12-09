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



class responseHandler {
public:

	// Constructor
	responseHandler(user* currentUser, interface* mainInterface);
	void handleResponse(std::string res);

private:
	
	user* currentUser;
	interface* mainInterface;

};

#endif