#ifndef SESSION_H
#define SESSION_H

// Project headers
#include "interface.h"

class session {
public:

	session();
	~session();

	void start();

private:

	// Interface stuff
	interface* mainInterface;

};

#endif