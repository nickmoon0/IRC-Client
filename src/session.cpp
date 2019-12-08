#include "session.h"

/*
 * Constructors/Destructors
 */

session::session() {
	mainInterface = new interface();
}

session::~session() {
	mainInterface->destroyWin();
	delete mainInterface;
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