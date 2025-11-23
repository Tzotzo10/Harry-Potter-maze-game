#include "Potter.h"
#include "Engine.h"

#include <iostream>
#include <algorithm>    // For std::min
#include <climits>      // For INT_MAX

using namespace std;

/*
 * Constructor for Potter
 * ----------------------
 * Initializes the character's starting position (x, y)
 * and the position of the gem (gemx, gemy)
 */
Potter::Potter(int x, int y, int gemx, int gemy) {
    this->x = x;
    this->y = y;
    this->gemx = gemx;
    this->gemy = gemy;
}

/*
 * Destructor
 */
Potter::~Potter() {}

/*
 * isSafe()
 * ----------
 * Checks if a given cell (x, y) is safe to move to:
 * - Must be inside map boundaries
 * - Must not be a wall ('*')
 * - Must not have been visited in the current path
 */
bool Potter::isSafe(vector<string> &mapcpy, vector<vector<bool>> &visited, int x, int y) {
    return (x >= 0 && x < mapcpy.size() && 
            y >= 0 && y < mapcpy[0].size() &&
            mapcpy[x][y] != '*' && !visited[x][y]);
}

/*
 * findShortestPath()
 * ------------------
 * Recursive DFS-based function to find the shortest path from (i,j) to (x,y)
 * - mapcpy: current map state
 * - visited: tracks visited cells
 * - Path: keeps track of path usage counts (optional for movement)
 * - min_dist: reference to minimum distance found so far
 * - dist: current distance from source
 */
void Potter::findShortestPath(vector<string> &mapcpy, vector<vector<bool>> &visited, int i, int j, int x, int y, int &min_dist, int dist, vector<vector<int>> &Path) {

    // Destination reached: update min_dist
    if (i == x && j == y) {
        min_dist = min(dist, min_dist);
        return;
    }

    // Mark current cell as visited
    visited[i][j] = true;
    Path[i][j] += 1; // Increment path usage for current cell

    // Explore all 4 directions recursively if safe
    if (isSafe(mapcpy, visited, i + 1, j))     findShortestPath(mapcpy, visited, i + 1, j, x, y, min_dist, dist + 1, Path);
    if (isSafe(mapcpy, visited, i, j + 1))     findShortestPath(mapcpy, visited, i, j + 1, x, y, min_dist, dist + 1, Path);
    if (isSafe(mapcpy, visited, i - 1, j))     findShortestPath(mapcpy, visited, i - 1, j, x, y, min_dist, dist + 1, Path);
    if (isSafe(mapcpy, visited, i, j - 1))     findShortestPath(mapcpy, visited, i, j - 1, x, y, min_dist, dist + 1, Path);

    // Backtrack: unmark the cell as visited
    visited[i][j] = false;
}

/*
 * findShortestPathLength()
 * ------------------------
 * Wrapper function for findShortestPath().
 * - Sets up visited and Path matrices
 * - Calls DFS to calculate shortest distance to gem
 * - Moves Potter one step along the shortest path
 * - Returns the minimum distance found
 */
int Potter::findShortestPathLength(vector<string> &map, vector<string> &mapcpy) {

    pair<int, int> src = make_pair(x, y);           // Potter's current position
    pair<int, int> dest = make_pair(gemx, gemy);    // Gem's position

    // Safety check: map must be valid
    if (mapcpy.size() == 0 || mapcpy[src.first][src.second] == 0 ||
        mapcpy[dest.first][dest.second] == 0)
        return -1;

    int row = mapcpy.size();
    int col = mapcpy[0].size();

    // Visited matrix to avoid cycles
    vector<vector<bool>> visited(row, vector<bool>(col, false));

    // Path matrix to track path usage (for determining next move)
    vector<vector<int>> Path(row, vector<int>(col, 0));

    int dist = INT_MAX;

    // Find shortest path from current position to gem
    findShortestPath(mapcpy, visited, src.first, src.second, dest.first, dest.second,
                     dist, 0, Path);

    // Move Potter one step along the shortest path
    if (Path[x + 1][y] == 1) {
        map[x + 1][y] = 'M'; map[x][y] = '.'; x++;
    } else if (Path[x - 1][y] == 1) {
        map[x - 1][y] = 'M'; map[x][y] = '.'; x--;
    } else if (Path[x][y + 1] == 1) {
        map[x][y + 1] = 'M'; map[x][y] = '.'; y++;
    } else if (Path[x][y - 1] == 1) {
        map[x][y - 1] = 'M'; map[x][y] = '.'; y--;
    }

    return dist;
}
