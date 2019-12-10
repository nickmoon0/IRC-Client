#ifndef HANDLER_H
#define HANDLER_H

// Standard headers
#include <vector>
#include <string>

// Project headers
#include "user.h"
#include "interface.h"

class handler {
public:

	handler(user* currentUser, interface* mainInterface);

protected:

	user* currentUser;
	interface* mainInterface;

	std::vector<std::string> splitString(std::string str);

};

#endif