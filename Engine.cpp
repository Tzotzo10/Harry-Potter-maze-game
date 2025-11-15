#include "Engine.h"

#include <iostream>
#include <fstream>

using namespace std;

Engine::Engine()
{
}

Engine::~Engine()
{
}

int Engine::getxM() const {
	return xM;
}

int Engine::getyM() const {
	return yM;
}

int Engine::getxL() const {
	return xL;
}

int Engine::getyL() const {
	return yL;
}

int Engine::getgemx() const {
	return gemx;
}

int Engine::getgemy() const {
	return gemy;
}

void Engine::RandStartPositions(vector<string>& map) {
    srand(time(0));
	int countlines=0, countcolumns=0, i=0, p1, p2;
	vector<string>::iterator it = map.begin();
	while (it != map.end()) {
	 	if(countlines==0) {
	 		for(string::iterator its = map[i].begin(); its != map[i].end(); ++its) {
	 			countcolumns++;
			 }
		 }
		countlines++;
		it++;
	}
	 
	p1 = rand() % countlines + 1;
	p2 = rand() % countcolumns + 1;
	while(map[p1][p2]=='*'){
		p1 = rand() % countlines + 1;
		p2 = rand() % countcolumns + 1;
	}
	map[p1][p2]='M';
	xM=p1;
	yM=p2;
	
	p1 = rand() % countlines + 1;
	p2 = rand() % countcolumns + 1;
	while(map[p1][p2]=='*' or map[p1][p2]=='M'){
		p1 = rand() % countlines + 1;
		p2 = rand() % countcolumns + 1;
	}
	map[p1][p2]='L';
	xL=p1;
    yL=p2;
	
	p1 = rand() % countlines + 1;
	p2 = rand() % countcolumns + 1;
	while(map[p1][p2]=='*' or map[p1][p2]=='M' or map[p1][p2]=='L'){
		p1 = rand() % countlines + 1;
		p2 = rand() % countcolumns + 1;
	}
	map[p1][p2]='P';
	gemx=p1;
	gemy=p2;
}

void Engine::RandGemPosition(vector<string>& map) {
    srand(time(0));
	int countlines=0, countcolumns=0, i=0, p1, p2;
	vector<string>::iterator it = map.begin();
	
	while (it != map.end()) {
	 	if(countlines==0) {
	 		for(string::iterator its = map[i].begin(); its != map[i].end(); ++its) {
	 			countcolumns++;
			 }
		 }
		countlines++;
		it++;
	}
	
	p1 = rand() % countlines + 1;
	p2 = rand() % countcolumns + 1;
	while(map[p1][p2]=='*'){
		p1 = rand() % countlines + 1;
		p2 = rand() % countcolumns + 1;
	}
	map[p1][p2]='P';
	gemx=p1;
	gemy=p2;
}
