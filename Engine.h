#ifndef Engine_h
#define Engine_h

#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Engine {
	private:
		int xM,yM,xL,yL;
		int gemx,gemy;
	public:
		Engine();
		~Engine();
		int getxM() const;
		int getyM() const;
		int getxL() const;
		int getyL() const;
		int getgemx() const;
		int getgemy() const;
		void RandStartPositions(vector<string>& map);
		void RandGemPosition(vector<string>& map);
};

#endif