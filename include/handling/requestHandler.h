#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

// Project headers
#include "handling/handler.h"

#include "user.h"
#include "interface.h"

class requestHandler : public handler {
public:

	requestHandler(user* currentUser, interface* mainInterface);

private:

};

#endif