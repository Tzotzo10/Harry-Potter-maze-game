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

void CreateMap(string Map, vector<string>& map);

int main (int argc, char** argv) {
    srand(time(0));
	string Map=argv[1];
	int rn1, rn2;
	vector<string> map;
	vector<string> mapcpy;
	
    CreateMap(Map,map);
    
	Engine en;
	Mal L(en.getxL(), en.getyL());
	Potter M(en.getxM(), en.getyM(), en.getgemx(), en.getgemy());
	
	en.RandStartPositions(map);
	while((en.getxL()!=en.getgemx() || en.getyL()!=en.getgemy()) || (en.getxM()!=en.getgemx() || en.getyM()!=en.getgemy())){
	    L.GetMove(map);
	    for (int i=0; i<map.size(); i++) 
	        mapcpy.push_back(map[i]);
	    M.findShortestPathLength(map, mapcpy);
	    
	    rn1 = rand() % 10;
	    rn2 = rand() % 10;
	    if(rn1==rn2)
	        en.RandGemPosition(map);
	}
	return 0;
}

void CreateMap(string Map, vector<string>& map){
	string line;
	ifstream fin;
	
	fin.open(Map.c_str(), ios_base::in);
	while (getline(fin, line)) {
        map.insert(map.begin(), line);
    }
}