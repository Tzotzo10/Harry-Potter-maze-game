#include "Potter.h"
#include "Engine.h"

#include <iostream>
#include <algorithm>

using namespace std;

Potter::Potter(int x, int y,int gemx, int gemy){
    this->x=x;
    this->y=y;
    this->gemx=gemx;
    this->gemy=gemy;
}

Potter::~Potter()
{
}

bool Potter::isSafe(vector<string> &mapcpy, vector<vector<bool>> &visited, int x, int y)
{
    return (x != '*' && x < mapcpy.size() && y !='*' && y < mapcpy[0].size()) &&
            mapcpy[x][y] != '*' && !visited[x][y];
}
  
  
void Potter::findShortestPath(vector<string> &mapcpy, vector<vector<bool>> &visited, int i, int j, int x, int y, int &min_dist, int dist, vector<vector<int>> &Path){

    if (i == x && j == y){
        min_dist = min(dist, min_dist);
        return;
    }
    // set (i, j) cell as visited
    visited[i][j] = true;
    // set (i, j) cell as visited
    Path[i][j] = Path[i][j] +1;
    // go to the bottom cell
    if (isSafe(mapcpy, visited, i + 1, j)) {
        findShortestPath(mapcpy, visited, i + 1, j, x, y, min_dist, dist + 1, Path);
    }
    // go to the right cell
    if (isSafe(mapcpy, visited, i, j + 1)) {
        findShortestPath(mapcpy, visited, i, j + 1, x, y, min_dist, dist + 1, Path);
    }
    // go to the top cell
    if (isSafe(mapcpy, visited, i - 1, j)) {
        findShortestPath(mapcpy, visited, i - 1, j, x, y, min_dist, dist + 1, Path);
    }
    // go to the left cell
    if (isSafe(mapcpy, visited, i, j - 1)) {
        findShortestPath(mapcpy, visited, i, j - 1, x, y, min_dist, dist + 1, Path);
    }
    
    // backtrack: remove (i, j) from the visited matrix
    visited[i][j] = false;
}
  
// Wrapper over findShortestPath() function
int Potter::findShortestPathLength(vector<string> &map, vector<string> &mapcpy){
    
    pair<int, int> src = make_pair(x, y);
    pair<int, int> dest = make_pair(gemx, gemy);
    
    if (mapcpy.size() == 0 || mapcpy[src.first][src.second] == 0 ||
            mapcpy[dest.first][dest.second] == 0)
        return -1;
     
    int row = mapcpy.size();
    int col = mapcpy[0].size();
    // construct an `M × N` matrix to keep track of visited cells
    vector<vector<bool>> visited;
    visited.resize(row, vector<bool>(col));
    
    vector<vector<int>> Path;
    Path.resize(row, vector<int>(col));
  
    int dist = INT_MAX;
    findShortestPath(mapcpy, visited, src.first, src.second, dest.first, dest.second,
            dist, 0, Path);
    
    if(Path[x+1][y]==1){
        map[x+1][y]='M';
        map[x][y]='.';
        x++;
    } else if(Path[x-1][y]==1){
        map[x-1][y]='M';
        map[x][y]='.';
        x--;
    } else if(Path[x][y+1]==1){
        map[x][y+1]='M';
        map[x][y]='.';
        y++;
    } else if(Path[x][y-1]==1){
        map[x][y-1]='M';
        map[x][y]='.';
        y--;
    }
       
    return dist;
}