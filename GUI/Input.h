#pragma once
#include "..\Utilities\Defs.h"
#include "..\GUI\UserInterface.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;	// Forward class declaration

/*
	A class responsible for getting any inputs from the user
	The application manager should have a pointer to this class
*/
class Input
{
private:
	int mLastX, mLastY;		// Last point clicked
	window* pWind;			// Pointer to the graphical Window object

public:
	/* Constructor */
	Input(window* pW);

	/* Returns the user's mouse click coordinate */
	void GetPointClicked(int& x, int& y) const;

	/* Returns the last point clicked by the user */
	void GetLastPointClicked(int& x, int& y) const;

	/* Returns the string entered by the user and reflect it on the status bar */
	string GetSrting(Output* pOut, string msg, string str) const;

	/* Reads the user's selection and determine the desired action */
	ActionType GetUserAction();

	/* Destructor */
	~Input();
};