#ifndef Potter_h
#define Potter_h

#include "Engine.h"
#include <cstring>
#include <string>
#include <vector>
#include <climits>   // For INT_MAX

using namespace std;

/*
 * Class: Potter
 * ----------------------
 * Represents the character 'M' in the game.
 * Inherits from Engine, so it can access engine features if needed.
 * Handles movement towards a gem using shortest path calculation.
 */
class Potter : public Engine {
private:
    int x, y;         // Current position of Potter on the map
    int gemx, gemy;   // Position of the gem that Potter is trying to reach

public:
    /*
     * Constructor
     * -----------
     * Initializes Potter's position (x, y) and the gem's position (gemx, gemy)
     */
    Potter(int x, int y, int gemx, int gemy);

    /*
     * Destructor
     */
    ~Potter();

    /*
     * findShortestPathLength
     * ----------------------
     * Wrapper function that finds the shortest path from Potter to the gem.
     * Moves Potter one step along the path and returns the minimum distance.
     */
    int findShortestPathLength(vector<string> &map, vector<string> &mapcpy);

    /*
     * findShortestPath
     * ----------------
     * Recursive function using DFS to find the shortest path from (i,j) to (x,y).
     * Keeps track of visited cells and path usage to avoid cycles.
     */
    void findShortestPath(vector<string> &mapcpy, vector<vector<bool>> &visited,
                          int i, int j, int x, int y, int &min_dist, int dist,
                          vector<vector<int>> &Path);

    /*
     * isSafe
     * -------
     * Checks whether a cell is valid to move into:
     * - Must be within map boundaries
     * - Must not be a wall ('*')
     * - Must not have been visited in the current DFS path
     */
    bool isSafe(vector<string> &mapcpy, vector<vector<bool>> &visited, int x, int y);
};

#endif
