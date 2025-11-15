#ifndef Mal_h
#define Mal_h
#include "Engine.h"

#include <panel.h>
#include <curses.h>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class Mal:public Engine {
    private:
        int x,y;
	public:
	    Mal(int x, int y);
	    ~Mal();
		void GetMove(vector<string>& map);
};

#endif