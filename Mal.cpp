#include "Mal.h"
#include "Engine.h"

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

/*
 * Constructor for Mal.
 * Stores the starting position (x, y) given by Engine.
 */
Mal::Mal(int x, int y){
    this->x = x;
    this->y = y;
}

Mal::~Mal()
{
}

/*
 * GetMove()
 * ----------
 * Handles movement of character L based on user input using ncurses.
 * The function:
 *   - Prints the map
 *   - Initializes ncurses for input
 *   - Reads arrow keys to move L
 *   - Ensures that L cannot walk into '*'
 *   - Updates the map with new L position
 *
 * WARNING:
 *   - Your use of coordinates map[x][y] is reversed — normally it should be map[row][col] = map[y][x].
 *   - move(y, x) is the opposite of normal coordinates.
 *   - This is not changed here but it is a major logic bug in your game.
 */
void Mal::GetMove(vector<string>& map) {

    // Print map to console before enabling ncurses
	for (int i = 0; i < map.size(); i++)
    	cout << map[i] << endl;

    int ch;

    // Get current stored position of L
    x = getxL();
    y = getyL();

    // Initialize ncurses
	initscr();
	printw("\nYou are L. Give desired direction: ");
	refresh();

	getch();   // Wait for first key press
	clear();   // Clear ncurses screen

	keypad(stdscr, TRUE);  // Enable arrow keys

	do
	{
		ch = getch();   // Read a key press

        // If user presses any non-space key, start movement
		if (ch != ' ') {
			break;
		}

		switch (ch)
		{
		    /*
		     * Each case checks if the next tile is NOT '*'
		     * If movement is allowed, L:
		     *   - Is drawn in the new position
		     *   - The old position is replaced with '.'
		     *
		     * WARNING: You are accessing map[x][y-1] but x = row or column?
		     *          It is likely reversed. Keeping unchanged as requested.
		     */
		    case KEY_UP:
		        if (map[x][y-1] == '*') {}             // Wall -> no movement
		        else {
		            map[x][y-1] = 'L';                  // Place L in new tile
		            move(y-1, x);                       // Move cursor (but reversed coords!)
		            map[x][y] = '.';                    // Clear old tile
		            y--;                                // Update internal position
		            break;
		        }

		    case KEY_DOWN:
		        if (map[x][y+1] == '*') {}
		        else {
		            map[x][y+1] = 'L';
		            move(y+1, x);
		            map[x][y] = '.';
		            y++;
		            break;
		        }

		    case KEY_LEFT:
		        if (map[x-1][y] == '*') {}
		        else {
		            map[x-1][y] = 'L';
		            move(y, x-1);
		            map[x][y] = '.';
		            x--;
		            break;
		        }

		    case KEY_RIGHT:
		        if (map[x+1][y] == '*') {}
		        else {
		            map[x+1][y] = 'L';
		            move(y, x+1);
		            map[x][y] = '.';
		            x++;
		            break;
		        }
		}

	}
	while (ch != 27);   // Loop until ESC (ASCII 27) is pressed

	// End ncurses mode
    endwin();
}
