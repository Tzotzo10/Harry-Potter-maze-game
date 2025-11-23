#include "Mal.h"
#include "Engine.h"

#include <iostream>
#include <vector>
#include <curses.h>   // ncurses library for interactive input

using namespace std;

/*
 * Constructor for Mal.
 * Initializes starting position.
 */
Mal::Mal(int x, int y) {
    this->x = x;
    this->y = y;
}

Mal::~Mal() {}

/*
 * GetMove()
 * ----------
 * Handles user movement for character 'L' on the map.
 * Arrow keys move the character. Walls '*' are impassable.
 * Updates both internal position and the map display.
 */
void Mal::GetMove(vector<string>& map) {
    int maxRow = map.size();
    int maxCol = map[0].size();

    // Initialize ncurses
    initscr();
    keypad(stdscr, TRUE);   // Enable arrow keys
    noecho();               // Do not echo keypresses
    curs_set(0);            // Hide cursor

    int ch;
    bool moved = false;

    do {
        clear();

        // Print the map
        for (int row = 0; row < maxRow; row++) {
            printw("%s\n", map[row].c_str());
        }
        printw("\nYou are 'L'. Use arrow keys to move. Press ESC to exit.\n");
        refresh();

        ch = getch();   // Wait for keypress

        int newX = x;
        int newY = y;

        // Handle arrow key movement
        switch (ch) {
            case KEY_UP:
                newX = x - 1;
                break;
            case KEY_DOWN:
                newX = x + 1;
                break;
            case KEY_LEFT:
                newY = y - 1;
                break;
            case KEY_RIGHT:
                newY = y + 1;
                break;
            case 27:  // ESC key
                endwin();
                return;
        }

        // Check boundaries
        if (newX >= 0 && newX < maxRow && newY >= 0 && newY < maxCol) {
            // Check for walls
            if (map[newX][newY] != '*') {
                // Move character: update map
                map[x][y] = '.';         // Clear old position
                x = newX;
                y = newY;
                map[x][y] = 'L';         // Set new position
                moved = true;
            }
        }

    } while (!moved);

    // End ncurses mode
    endwin();
}

/*
 * Get current X position
 */
int Mal::getxL() const {
    return x;
}

/*
 * Get current Y position
 */
int Mal::getyL() const {
    return y;
}
