#ifndef Mal_h
#define Mal_h

#include "Engine.h"        // Access to Engine class for positions & game logic
#include <panel.h>         // ncurses panel library (optional, for GUI)
#include <curses.h>        // ncurses library for interactive input
#include <cstring>
#include <string>
#include <vector>

using namespace std;

/*
 * Class: Mal
 * -------------
 * Represents the character 'L' in the game.
 * Inherits from Engine, so it can access engine methods (like random positions).
 * Handles its own movement on the map using arrow keys.
 */
class Mal : public Engine {
private:
    int x, y;      // Current position of Mal on the map: x = row, y = column

public:
    /*
     * Constructor
     * ----------
     * Initializes the character's starting position.
     */
    Mal(int x, int y);

    /*
     * Destructor
     */
    ~Mal();

    /*
     * GetMove
     * ----------
     * Prompts the player to move the character 'L' using arrow keys.
     * Updates both the internal position (x, y) and the map vector.
     * Movement is blocked by walls '*' and constrained by map boundaries.
     */
    void GetMove(vector<string>& map);
};

#endif
