/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include <iostream>
#include <string>

#include "CMUgraphics.h"
#include "windowinput.h"
#include "error.h"

windowinput::windowinput(const HWND hwndNew, const window* wpNewWind) {

    wiHead = NULL;
    bWaitClose = true;
    usNumWindows = 0;
    
    AddWindow(hwndNew, wpNewWind);

}

windowinput::~windowinput() {

	if(wiHead != NULL) {
		delete wiHead;
	} 

}

void windowinput::AddWindowInt(const HWND hwndNew, const window* wpNewWind, winode *&wiNode) {

    if(wiNode == NULL) {
        usNumWindows++;
		wiNode = new winode(hwndNew, wpNewWind);
		if(wiNode == NULL) {
		    throw OUT_OF_MEMORY;    
		} 
    } else if(wiNode->hwndValue == hwndNew) {
	   return;
	} else {
	   AddWindowInt(hwndNew, wpNewWind, wiNode->wiNext);
	}

}

void windowinput::RemoveWindowInt(const HWND hwndOld, winode *&wiNode) {

    winode *wiTemp;

    if(wiNode == NULL) {
	   return;
    } else if(wiNode->hwndValue == hwndOld) {
       usNumWindows--;
       wiTemp = wiNode->wiNext;
       wiNode->wiNext = NULL;
       delete wiNode;
	   wiNode = wiTemp;
	} else {
	   RemoveWindowInt(hwndOld, wiNode->wiNext);
	}

}

window* windowinput::FindWindowInt(const HWND hwndKey, const winode *wiNode) {

    if(wiNode == NULL) {
		return NULL;
    } else if(wiNode->hwndValue == hwndKey) {
	   return ((window *) wiNode->wpValue);
	} else {
	   return FindWindowInt(hwndKey, wiNode->wiNext);
	}
}

void windowinput::AddWindow(const HWND hwndNew, const window* wpNewWind) {

  AddWindowInt(hwndNew, wpNewWind, wiHead);

}

void windowinput::RemoveWindow(const HWND hwndOld) {

  RemoveWindowInt(hwndOld, wiHead);

}


window* windowinput::FindWindow(const HWND hwndKey) {

	return FindWindowInt(hwndKey, wiHead);

}

unsigned short windowinput::Count() {

	return usNumWindows;
}

void windowinput::SetMouseState(const HWND hwndKey, const button btMouse, const buttonstate bsNew, const int iX, const int iY) {

    window* windTmp = FindWindow(hwndKey);
    
	if(windTmp != NULL) {
	    if(btMouse == LEFT_BUTTON) {
  	      windTmp->bsLeft = bsNew;
  	    } else {
  	      windTmp->bsRight = bsNew;  	    
  	    }  
   	    windTmp->iMouseX = iX;
	    windTmp->iMouseY = iY;
	}

}

void windowinput::SetMouseCoord(const HWND hwndKey, const int iX, const int iY) {

    window* windTmp = FindWindow(hwndKey);

	if(windTmp != NULL) {
	    windTmp->iMouseX = iX;
	    windTmp->iMouseY = iY;
	}
}

void windowinput::SetClickInfo(const HWND hwndKey, const clicktype ctInfo, const int iX, const int iY) {

    window* windTmp = FindWindow(hwndKey);
	mqueuenode *mqueTmp;

    if(windTmp != NULL) {
        mqueTmp = new mqueuenode;
		if(mqueTmp == NULL) {
			throw OUT_OF_MEMORY;
		}
		mqueTmp->ctInfo = ctInfo;
		mqueTmp->iX = iX;
		mqueTmp->iY = iY;

		windTmp->mqueInput.Insert(mqueTmp);
	}
}

void windowinput::SetKeyInfo(const HWND hwndKey, const keytype ktInfo, const char cValue) {

	window* windTmp = FindWindow(hwndKey);
	kqueuenode *kqueTmp;

    if(windTmp != NULL) {
        kqueTmp = new kqueuenode;
		if(kqueTmp == NULL) {
			throw OUT_OF_MEMORY;
		}
		kqueTmp->ktInfo = ktInfo;
		kqueTmp->cValue = cValue;

		windTmp->kqueInput.Insert(kqueTmp);
	}
}