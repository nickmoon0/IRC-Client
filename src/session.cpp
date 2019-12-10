#include "session.h"

/*
 * Constructors/Destructors
 */

session::session() {
	mainInterface = new interface();
	serverList = new std::vector<ServerListener*>();
}

session::~session() {
	mainInterface->destroyWin();
	delete mainInterface;

	delete serverList;
}

/*
 * Starting functions
 */

void session::start() {
	mainInterface->initInterface();

	while (true) {
		mainInterface->getInput();
	}

}