/*

Text based game that needs to:


* Take a file input - it gets characters from that file, puts them into arrays
* Rain letters over a player (which is an ASCII character)
* Know where our player is at all times, know if a letter exists at that position

*/

#include <iostream>
#include <curses.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define INDENTATION 10
using namespace std;


// GAME VARIABLES

// A row of the chararacters in the 'rain' contains the letters in between the newline chars
string rainRow9 = "|######  ############|";
string rainRow8 = "|########  ##########|";
string rainRow7 = "|##########  ########|";
string rainRow6 = "|############   #####|";
string rainRow5 = "|#########  #########|";
string rainRow4 = "|######  ############|";
string rainRow3 = "|######  ############|";
string rainRow2 = "|######  ############|";
string rainRow1 = "|#######  ###########|";
string rainRow0 = "|########  ##########|";
string noStr	= "|                    |";

string strArray[10] = { rainRow0, rainRow1, rainRow2, rainRow3, rainRow4,rainRow5,rainRow6,rainRow7,rainRow8,rainRow9};
unsigned int index1 = 0;
vector<string> myvector;
int curLine = 5;
int strIndex = 1;
int curRun = 0;





int main(int argc, char* argv[]) {

	
	

	
	initscr();
	noecho();
	char myChar;
	// Screen dimensions
	int y;
	int x;

	while (true) {
		move(0,0);
		getmaxyx(stdscr,y,x);
		clear();

		printw("SIZE %i x %i",x,y);
		myChar = mvinch(0,1) & A_CHARTEXT;

		move(5,5);
		printw("myChar: %c", myChar);


		getch();
	}
	
	endwin();
	

	return 0;

}
