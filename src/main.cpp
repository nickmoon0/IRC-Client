#include "session.h"

int main() {
	session* s = new session();

	s->start();

	delete s;
	return 0;
}