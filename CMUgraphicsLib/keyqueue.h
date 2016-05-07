/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#ifndef KEYQUEUE_H
#define KEYQUEUE_H

#include <cstdlib>
#include "version.h"

// Types of keys that can be pressed
enum keytype {
	NO_KEYPRESS,
	ASCII,
	ARROW,
	FUNCTION,
	ESCAPE
};


class kqueuenode {
    
  public:
	keytype ktInfo;
	char cValue;

	kqueuenode *kqueNext;
	
	kqueuenode() {
	    kqueNext = NULL;
	}
};

class kqueue {

  private:
    kqueuenode *kqueHead;
	kqueuenode *kqueTail;

  public:
	kqueue();
	~kqueue();
	
	void Insert(kqueuenode* kqueNode);
	kqueuenode* Remove();
};

#endif //KEYQUEUE_H
