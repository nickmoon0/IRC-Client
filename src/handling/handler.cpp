#include "handling/handler.h"

/*
 * Constructor
 */

handler::handler(user* currentUser, interface* mainInterface) {
	this->currentUser = currentUser;
	this->mainInterface = mainInterface;
}