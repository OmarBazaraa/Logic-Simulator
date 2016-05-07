/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#ifndef WINDOWINPUT_H
#define WINDOWINPUT_H

#ifndef WINDOWS_H
  #define WINDOWS_H
  #include <windows.h>
#endif //WINDOWS_H

#include "mousequeue.h"
#include "keyqueue.h"

class winode {

  public:

    winode* wiNext;

    const HWND hwndValue;
	const window* wpValue;
	
	winode(const HWND hwndNew, const window* wpNewWind) : hwndValue(hwndNew), wpValue(wpNewWind) { wiNext = NULL; }

	~winode () { if(wiNext != NULL) { delete wiNext; } } 
	
};

class windowinput {

  private:
    winode *wiHead;

    // Allow the window class to read the state of bWaitClose
    friend class window;
		
	// True if we want to wait for a mouseclick before closing the last window
	bool bWaitClose;
	
	// Number of windows
	unsigned short usNumWindows;

	void AddWindowInt(const HWND hwndNew, const window* wpNewWind, winode *&wiNode);
	void RemoveWindowInt(const HWND hwndOld, winode *&wiNode);
	window* FindWindowInt(const HWND hwndKey, const winode *wiNode);
	
  public:
	windowinput(const HWND hwndNew, const window* wpNewWind);
	~windowinput();

	void AddWindow(const HWND hwndNew, const window* wpNewWind);
	void RemoveWindow(const HWND hwndOld);

	window* FindWindow(const HWND hwndKey);
	
	unsigned short Count();

    void SetMouseState(const HWND hwndKey, const button btMouse, const buttonstate bsNew, const int iX, const int iY);
	void SetMouseCoord(const HWND hwndKey, const int iX, const int iY);
	void SetClickInfo(const HWND hwndKey, const clicktype ctInfo, const int iX, const int iY);
	void SetKeyInfo(const HWND hwndKey, const keytype ktInfo, const char cValue);

};

#endif //WINDOWINPUT_H