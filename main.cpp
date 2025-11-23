#include "Mal.h"
#include "Potter.h"
#include "Engine.h"
#include <panel.h>
#include <curses.h>

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
 * Reads a map file into a vector<string>.
 * Each line of the file becomes a row of the map.
 */
void CreateMap(string Map, vector<string>& map);

int main (int argc, char** argv) {
    srand(time(0));  // Seed RNG for random positions

    // Map filename passed as argument
    string Map = argv[1];

    int rn1, rn2;               // Random numbers used for gem respawn logic
    vector<string> map;         // The actual game map (grid)
    vector<string> mapcpy;      // A copy used by Potter for pathfinding

    // Load the map from file
    CreateMap(Map, map);

    // Engine handles random placement of characters/gem
    Engine en;

    // Initialize characters with temporary positions (actual ones set later)
    Mal L(en.getxL(), en.getyL());
    Potter M(en.getxM(), en.getyM(), en.getgemx(), en.getgemy());

    // Randomly place M, L, and P on valid map cells
    en.RandStartPositions(map);

    /*
     * Main loop:
     * Continues until *either* Mal OR Potter reaches the gem P.
     * Loop condition:
     *   continue while:
     *     L not at gem  OR   M not at gem
     *
     * Only stops when at least one of them reaches it.
     */
    while ((en.getxL() != en.getgemx() || en.getyL() != en.getgemy()) ||
           (en.getxM() != en.getgemx() || en.getyM() != en.getgemy())) {

        // Let Mal make their move (human? AI?)
        L.GetMove(map);

        // Build a fresh map copy for Potter's pathfinding
        mapcpy.clear();
        for (int i = 0; i < map.size(); i++)
            mapcpy.push_back(map[i]);

        // Potter calculates the shortest path to the gem
        M.findShortestPathLength(map, mapcpy);

        /*
         * Random event:
         * With probability 1/10 (rn1 == rn2 out of 100 combinations),
         * the gem is moved to a new random valid position.
         */
        rn1 = rand() % 10;
        rn2 = rand() % 10;

        if (rn1 == rn2)
            en.RandGemPosition(map);
    }

    return 0;
}

/*
 * Reads a map file line by line into a vector<string>.
 * NOTE: Lines are inserted at the BEGINNING (reverse order).
 *       If not intended, use push_back() instead.
 */
void CreateMap(string Map, vector<string>& map) {
    string line;
    ifstream fin;

    fin.open(Map.c_str(), ios_base::in);

    while (getline(fin, line)) {
        map.insert(map.begin(), line);  // Inserts at front → reverses map
    }
}
