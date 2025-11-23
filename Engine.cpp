#include "Engine.h"

#include <iostream>
#include <fstream>

using namespace std;

Engine::Engine()
{
    // Constructor — currently does nothing.
}

Engine::~Engine()
{
    // Destructor — currently does nothing.
}

// ------- GETTERS FOR POSITION VARIABLES -------

int Engine::getxM() const {
    return xM;   // X-position of M (player / monster?)
}

int Engine::getyM() const {
    return yM;   // Y-position of M
}

int Engine::getxL() const {
    return xL;   // X-position of L (likely second player / entity)
}

int Engine::getyL() const {
    return yL;   // Y-position of L
}

int Engine::getgemx() const {
    return gemx; // X-position of the gem "P"
}

int Engine::getgemy() const {
    return gemy; // Y-position of the gem "P"
}

/*
 Randomly places:
   M — first character
   L — second character
   P — gem

 in the map, ensuring:
   - They do not land on '*' tiles
   - They do not overlap each other
*/
void Engine::RandStartPositions(vector<string>& map) {

    srand(time(0));  // Initialize RNG with current time

    int countlines = 0, countcolumns = 0;
    int i = 0, p1, p2;

    // Count number of rows and columns in the map
    vector<string>::iterator it = map.begin();

    while (it != map.end()) {
        if (countlines == 0) {
            // For first line, count the columns
            for (string::iterator its = map[i].begin(); its != map[i].end(); ++its) {
                countcolumns++;
            }
        }
        countlines++;
        it++;
    }

    // ---------------- PLACE M ----------------
    p1 = rand() % countlines + 1;
    p2 = rand() % countcolumns + 1;

    // Avoid walls '*'
    while (map[p1][p2] == '*') {
        p1 = rand() % countlines + 1;
        p2 = rand() % countcolumns + 1;
    }

    map[p1][p2] = 'M';
    xM = p1;
    yM = p2;

    // ---------------- PLACE L ----------------
    p1 = rand() % countlines + 1;
    p2 = rand() % countcolumns + 1;

    // Avoid walls, and avoid M
    while (map[p1][p2] == '*' || map[p1][p2] == 'M') {
        p1 = rand() % countlines + 1;
        p2 = rand() % countcolumns + 1;
    }

    map[p1][p2] = 'L';
    xL = p1;
    yL = p2;

    // ---------------- PLACE GEM (P) ---------
    p1 = rand() % countlines + 1;
    p2 = rand() % countcolumns + 1;

    // Avoid walls and both characters
    while (map[p1][p2] == '*' || map[p1][p2] == 'M' || map[p1][p2] == 'L') {
        p1 = rand() % countlines + 1;
        p2 = rand() % countcolumns + 1;
    }

    map[p1][p2] = 'P';  // Place gem
    gemx = p1;
    gemy = p2;
}


/*
   Randomizes only the gem ('P') position.
   Used when gem must respawn after being collected.
*/
void Engine::RandGemPosition(vector<string>& map) {

    srand(time(0)); // Seed RNG

    int countlines = 0, countcolumns = 0;
    int i = 0, p1, p2;

    // Count rows and columns
    vector<string>::iterator it = map.begin();
    while (it != map.end()) {
        if (countlines == 0) {
            for (string::iterator its = map[i].begin(); its != map[i].end(); ++its) {
                countcolumns++;
            }
        }
        countlines++;
        it++;
    }

    // --- New gem placement ---
    p1 = rand() % countlines + 1;
    p2 = rand() % countcolumns + 1;

    while (map[p1][p2] == '*') {
        p1 = rand() % countlines + 1;
        p2 = rand() % countcolumns + 1;
    }

    map[p1][p2] = 'P'; // Set new gem location
    gemx = p1;
    gemy = p2;
}
