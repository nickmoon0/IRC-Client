#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <mutex>

class interface {
public:

	interface();

	void initInterface();
	void destroyWin();

	std::string getInput();
	void outputMessage(std::string message);

private:
	// Functions
	void drawInputBox();
	void drawOutputBox();
	void refreshPad();

	// Input Box variables

	const int inputCoordY = 1;
	const int inputCoordX = 1;

	int inputWindowHeight;
	int inputWindowWidth;
	int inputWinStartY;
	int inputWinStartX;

	// Output box variables

	int outputWindowHeight;
	int outputWindowWidth;

	const int outputWindowLength = 500;

	int outputWinStartY;
	int outputWinStartX;

	int outputCursorPos = 0;
	int scrollCursorPos = 0;
	std::vector<std::string> messageLog;

	// Windows
	WINDOW* inputWin;
	WINDOW* outputPad;

	// Mutex
	std::mutex *outputMutex;

};

#endif