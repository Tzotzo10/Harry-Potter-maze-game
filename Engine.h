#ifndef Engine_h
#define Engine_h

#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h>   // For rand(), srand()
#include <time.h>     // For time() used in srand()

using namespace std;

/*
 * Engine class
 * ------------
 * This class manages the positions of:
 *   - M : first character (player or monster)
 *   - L : second character
 *   - P : gem
 *
 * It also provides functions to:
 *   - Randomly place all three at the start
 *   - Respawn the gem at a random valid position
 *
 * The map is given as a vector<string>, where:
 *   - Each string is a row
 *   - '*' represents a wall (cannot place objects there)
 */
class Engine {

    private:
        // Current position of character M
        int xM, yM;

        // Current position of character L
        int xL, yL;

        // Current position of gem P
        int gemx, gemy;

    public:
        // Constructor / Destructor
        Engine();
        ~Engine();

        // ----- Getters for positions -----
        int getxM() const;   // Return M's row
        int getyM() const;   // Return M's column
        int getxL() const;   // Return L's row
        int getyL() const;   // Return L's column
        int getgemx() const; // Return gem's row
        int getgemy() const; // Return gem's column

        /*
         * Randomly place M, L, and P on the map.
         * Ensures:
         *   - They do NOT spawn on '*'
         *   - They do NOT spawn on top of each other
         */
        void RandStartPositions(vector<string>& map);

        /*
         * Randomly reposition only the gem P.
         * Ensures:
         *   - It does NOT spawn on a wall '*'
         */
        void RandGemPosition(vector<string>& map);
};

#endif
