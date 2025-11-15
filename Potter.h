#ifndef Potter_h
#define Potter_h
#include "Engine.h"

#include <cstring>
#include <string>
#include <vector>
#include <climits> 

//using the standard space library of cpp
using namespace std;

class Potter:public Engine {
    private:
        int x,y,gemx,gemy;
	public:
	    Potter(int x, int y,int gemx, int gemy);
	    ~Potter();
		int findShortestPathLength(vector<string> &map, vector<string> &mapcpy);
		void findShortestPath(vector<string> &mapcpy, vector<vector<bool>> &visited, int i, int j, int x, int y, int &min_dist, int dist, vector<vector<int>> &Path);
		bool isSafe(vector<string> &mapcpy, vector<vector<bool>> &visited, int x, int y);
};

#endif