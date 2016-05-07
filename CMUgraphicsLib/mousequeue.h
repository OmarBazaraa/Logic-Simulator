/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#ifndef MOUSEQUEUE_H
#define MOUSEQUEUE_H

#include <cstdlib>
#include "version.h"

// Which button -- no middle button for now
enum button {
    LEFT_BUTTON,
    RIGHT_BUTTON
};

// Is the mouse button up or down?
enum buttonstate {
    BUTTON_UP,
    BUTTON_DOWN
};

// Type of click that an be made
enum clicktype {
	NO_CLICK,
    LEFT_CLICK,
	RIGHT_CLICK,
};

class mqueuenode {

  public:
	clicktype ctInfo;
	int iX, iY;

	mqueuenode *mqueNext;

	mqueuenode() {
	    mqueNext = NULL;
	}
};

class mqueue {

  private:
    mqueuenode *mqueHead;
	mqueuenode *mqueTail;

  public:
	mqueue();
	~mqueue();
	
	void Insert(mqueuenode* mqueNode);
	mqueuenode* Remove();
};

#endif //MOUSEQUEUE_H
