#ifndef HANDLER_H
#define HANDLER_H

// Project headers
#include "user.h"
#include "interface.h"

class handler {
public:

	handler(user* currentUser, interface* mainInterface);

protected:

	user* currentUser;
	interface* mainInterface;

};

#endif