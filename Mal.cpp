#include "Mal.h"
#include "Engine.h"

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

Mal::Mal(int x, int y){
    this->x=x;
    this->y=y;
}

Mal::~Mal()
{
}

void Mal::GetMove(vector<string>& map) {
	for (int i = 0; i < map.size(); i++)
    	cout << map[i] << endl;
    
	int ch;
	x = getxL();
	y = getyL();
	initscr ();
	printw ("\nYou are L. Give desired direction: ");
	refresh ();
	getch ();
	clear ();
	keypad (stdscr,TRUE);
	do
	{	
		ch = getch ();
		if (ch != ' ') {
			break;
		}
		switch (ch)
		{
		    case KEY_UP : if(map[x][y-1] == '*'){} else{ map[x][y-1]='L'; move(y-1, x); map[x][y]='.'; y--; break;}
		    case KEY_DOWN : if(map[x][y+1] == '*'){}	else{ map[x][y+1]='L'; move(y+1, x); map[x][y]='.'; y++; break;}
		    case KEY_LEFT: if(map[x-1][y] == '*'){} else{ map[x-1][y]='L'; move(y, x-1); map[x][y]='.'; x--; break;}
		    case KEY_RIGHT: if(map[x+1][y] == '*'){} else{ map[x+1][y]='L'; move(y, x+1); map[x][y]='.'; x++; break;}
		}
	}
	while (ch != 27);
	endwin ();
}