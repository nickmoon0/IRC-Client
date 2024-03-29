#include "interface.h"

#include <ncurses.h>
#include <string>
/*
 * Constructor
 */

interface::interface() {

}

/*
 * Initialisation and destruction
 */

void interface::initInterface() {
	/*
	 * Calling initialisation functions
	 */

	initscr();
	noecho();
	cbreak();
	keypad(stdscr, true);
	//curs_set(0);

	/*
	 * Getting screen data
	 */

	int screenWidth;
	int screenHeight;

	getmaxyx(stdscr, screenHeight, screenWidth);

	/*
	 * Configuring input window
	 */

	this->inputWindowHeight = 3;
	this->inputWindowWidth = screenWidth;
	this->inputWinStartY = screenHeight - inputWindowHeight;
	this->inputWinStartX = 0;


	/*
	 * Configuring output window
	 */

	// Add -1 to hight and width to keep it within terminal and also look better
	this->outputWindowHeight = screenHeight - inputWindowHeight - 1;
	this->outputWindowWidth = screenWidth - 1;
	this->outputWinStartY = 0;
	this->outputWinStartX = 0;

	/*
	 * Creating both windows and the borders/boxes (Must refresh window after creating)
	 */

	this->drawOutputBox();
	this->drawInputBox();

	//scrollok(this->outputPad, true);
	//idlok(this->outputPad, true);

	/*
	 * Create mutex
	 */

	this->outputMutex = new std::mutex();

}
// ---------------------------------------------------------------------
// Drawing

void interface::drawInputBox() {
	// Freeing current pointer if it is not already freed
	if (!inputWin) {
		delwin(inputWin);
	}

	// Creating new window and refreshing the screen
	this->inputWin = newwin(inputWindowHeight, inputWindowWidth, inputWinStartY, inputWinStartX); 
	refresh();

	// Creating border for window
	box(this->inputWin, 0, 0);

	// Moving the cursor to the middle of the text box and then refreshing the window
	wmove(this->inputWin, 1, 1);
	wrefresh(this->inputWin);
}

void interface::drawOutputBox() {
	// Freeing current pointer if it is not already freed
	if (!outputPad) {
		delwin(outputPad);
	}

	// Creating new window and refreshing the screen
	this->outputPad = newpad(this->outputWindowLength, this->outputWindowWidth);
	
	nodelay(outputPad, true);
	refresh();

	// Refreshing the pad
	refreshPad();

}

void interface::refreshPad() {
	refresh();
	prefresh(this->outputPad, outputCursorPos, 0, 0, 0, outputWindowHeight, outputWindowWidth);
}

// ---------------------------------------------------------------------

void interface::destroyWin() {
	delete outputMutex;

	outputMessage("Press any key to continue...");
	getch();
	endwin();
}

/*
 * Input functions
 */

std::string interface::getInput() {

	// String which will be returned
	std::string returnString;
	
	// This variable is used to progress the position of the cursor
	int cursorPos = this->inputCoordX;
	
	// Continue until enter is pressed
	while (true) {
		int c = getch();

		/*
		 * ENTER KEY
		 */

		// Checking if enter is pressed
		if (c == (char)'\r' || c == (char)'\n') {
			
			if (returnString.empty()) {
				continue;
			}

			// Erase and redraw the input window
			werase(this->inputWin);
			this->drawInputBox();

			break;
		}

		/*
		 * SCROLLING
		 */

		if (c == KEY_UP) {			
			if (outputCursorPos <= 0) {
				continue;
			}

			outputCursorPos--;
			refreshPad();
			
			continue;
		} else if (c == KEY_DOWN) {
			outputCursorPos++;
			refreshPad();
			
			continue;
		} 

		/*
		 * BACKSPACE
		 */

		if (c == 127) {
			if (!returnString.empty()) {
				mvwdelch(this->inputWin, this->inputCoordY, cursorPos - 1);
				returnString = returnString.substr(0, returnString.size()-1);
				cursorPos--;

				wrefresh(this->inputWin);
				continue;
			}
			continue;
		}

		/*
		 * PRINTING
		 */

		// Add the character pressed to the end of the string to return
		returnString += (char)c;

		// Move cursor forwards in inputBox and print new char
		mvwaddch(this->inputWin, this->inputCoordY, cursorPos, c);
		//mvwprintw(this->inputWin, this->inputCoordY, cursorPos, std::string(1, (char)c).c_str());
		
		// Move cursor up for next character and refresh window
		cursorPos++;
		wrefresh(this->inputWin);
	}

	return returnString;
}

/*
 * Output Functions
 */

void interface::outputMessage(std::string message) {
	// Lock up mutex
	outputMutex->lock();
	
	// Print the message with a newline character in order to scroll
	wprintw(this->outputPad, "%s\n", message.c_str());

	// Refresh the window to display changes
	refreshPad();

	// Move the cursor back to the input box and refresh the inputWin
	wmove(this->inputWin, this->inputCoordY, this->inputCoordX);
	wrefresh(this->inputWin);

	// Unlock mutex
	outputMutex->unlock();
}




