
#include <iostream>
#include <curses.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <vector>

#define INDENTATION 10
using namespace std;


// GAME VARIABLES
typedef unsigned short int num;
#define PLAYER "X"
#define LIVES 5
#define FPS 60
#define PPF 50
#define SECOND 1000000

num PLAYER_SIZE;
num rows;
num cols;

struct Position {
    num x;
    num y;
};

struct Ply {
    struct Position pos;
    int lives;
};

struct Ply ply;

int in;
num u;

num i;
num x;

// A row of the chararacters in the 'rain' string contains various '#' ASCII characters
string rainRow9 = "|#   #   #    #  #  #|";
string rainRow8 = "|      #             |";
string rainRow7 = "| #          #       |";
string rainRow6 = "|           #    #  #|";
string rainRow5 = "| #      #  #       #|";
string rainRow4 = "|  #  #              |";
string rainRow3 = "|     #  ##          |";
string rainRow2 = "|              # #   |";
string rainRow1 = "|                 #  |";
string rainRow0 = "|#         ##  ## #  |";
string noStr	= "|                    |";

// The amount of characters in between the left/right boundaries
int rainWidth = 20;

// The string array contains all the rows of the rain
string strArray[10] = { rainRow0, rainRow1, rainRow2, rainRow3, rainRow4,rainRow5,rainRow6,rainRow7,rainRow8,rainRow9};
vector<string> myvector;

// Variables used to keep track of the cursor and time
int curLine = 5;
int strIndex = 1;
int curRun = 0;
clock_t endwait;

// Contains the character that occupies the position of where the player is about to move
char possibleCollision;


// Prints the current game screen using the string array onto the window 
// Noe that refresh() should be called afterwards
void printStrVector()
{
	curLine = 5;
	move(curLine, INDENTATION);

	vector<string>::iterator it;
	string row_str;
	const char *row;

	// Print every string in the array, each time skiping over to another line
	for (it=myvector.begin(); it != myvector.end(); it++)
	{
		row_str = *it;
		row = row_str.c_str();
		printw(row);
		printw("\n");
		curLine++;
		move(curLine,INDENTATION);
	}
}

// Function that resets the game if the 'q' key is pressed
void quit(const char* seq) {
    clear();
    curs_set(2);
    endwin();
    cout << seq <<  endl;
    exit(0);
}

// Draw the player character and update the players live based on a possible collision
inline void draw(struct Position obj, const char* art) {

	// Store the character that the play may collide into
	possibleCollision = mvinch(obj.y, obj.x) & A_CHARTEXT;

	// Player loses a life if there is '#' character to collide into
	if ( possibleCollision == '#' ) ply.lives--;	
	
	// Reset the game based on the players life
	if ( ply.lives < 1 ) {
		clear();
		nocbreak();
		nodelay(stdscr,FALSE);
        mvprintw(0, 0, "Game Over!:\nPRESS ENTER TO RESTART");
		getch();
		ply.lives = 5;
		move(0,0);
		clrtoeol();
		cbreak();
		nodelay(stdscr,TRUE);
		
	}
	
	// Move the character accordingly
	mvprintw(obj.y, obj.x, art);

}


// Redraws the character if outside the boundary and also updates lives counter
void draw_all() {

/* Draws counter for lives on screen */
    mvprintw(rows-1, 0, "Lives: %u", ply.lives);
    
    if (ply.pos.x < INDENTATION) ply.pos.x = INDENTATION;
    if (ply.pos.x > INDENTATION + rainWidth) ply.pos.x = INDENTATION;
    draw(ply.pos, PLAYER);

}

//Controls the Player, q- quit, p- pause
void run_ply() {
   
   in = getch();
		
    if (in == KEY_LEFT || in == 'a' || in == 'h') {
    	mvprintw(ply.pos.y, ply.pos.x, " ");
        ply.pos.x -= (ply.pos.x == 0) ? 0 : 1;
    } 
    else if (in == KEY_RIGHT || in == 'd' || in == 'k') {
    	mvprintw(ply.pos.y, ply.pos.x, " ");
        ply.pos.x += (ply.pos.x == cols-PLAYER_SIZE) ? 0 : 1;
    } else if (in == 'q' || in == KEY_EXIT) {
        quit("Exited\n");
    } else if (in == 'p') {
		
		// Force wait for keystrokes
    	nocbreak();
		nodelay(stdscr,FALSE);
		
		// Display message
        mvprintw(LINES/2, COLS/2-8, "Paused: PRESS ENTER TO RETURN TO GAME");
		
		// Wait for user input
		getch();

		move(LINES/2,COLS/2-8);
		clrtoeol();
		clear();

		nodelay(stdscr,TRUE);
		cbreak();
    }
    
    if( in != ERR ) {
		draw_all();
	}

}

// Shifts contents of the string array to the right by one position
void updateStrArray()
{
	rotate(myvector.begin(),myvector.begin()+9,myvector.end());
	myvector.erase(myvector.begin());
	myvector.insert(myvector.begin(), strArray[strIndex]);
}


int main(int argc, char* argv[]) {

	// initialize the string vector
	for (int j=0; j<10; j++)
	{
		if (j) myvector.push_back(noStr);
		else myvector.push_back(rainRow0);
	}

	/* During the first 10 runs, the string array will add new strings to the array */
	bool firstCycle = true;	
	
	// Initialize ncurses window
	initscr();
	noecho();
	cbreak();
	
	// Don't sit and wait for keyboard input
    nodelay(stdscr, TRUE);
    curs_set(0);
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, rows, cols);
    PLAYER_SIZE = strlen(PLAYER);

    ply.lives = LIVES;
	ply.pos.y = 14;
	ply.pos.x = INDENTATION + rainWidth/2;
	
	endwait = clock();

	// start of main game loop
	while (true) {
		
		run_ply();
		draw_all();
		
		if (firstCycle)
		{
			/* Print the current string vector and update the string array */
			printStrVector();
			updateStrArray();

			/* Update the current run that we are on and the current string array index */
			strIndex++;
			curRun++;
		
			refresh();
			
			usleep(100*1000);
		
			// change the way we update the string array if we're no longer on our first cycle
			if (curRun > 8)	firstCycle = false;
		}

		/* If no longer on the first cycle */
		else 
		{
			
			if( clock() > endwait ) {
				endwait = clock() + .5 * CLOCKS_PER_SEC;
				rotate(myvector.begin(),myvector.begin()+9,myvector.end());
				printStrVector();

				refresh();
		 	}
		}
}

	printw("Press any key to exit the game");
	getch();
	
	endwin();
	
	return 0;
}




