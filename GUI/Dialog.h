#pragma once
#include<string>
#include "..\GUI\UserInterface.h"
#include "..\GUI\Input.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

/*
	A class responsible for performing any Dialog to the screen
	The application manager should have a pointer to this class
*/
class Dialog
{
private:
	window* pWind;					// Pointer to the graphical Window object

public:
	/* Constructor that initializes the user interface */
	Dialog(string s);

	/* Creates a new Window object */
	window* CreateWind(int w, int h, int x, int y) const;

	/* Chnages the title of the Window */
	void ChangeTitle(const string& title) const;

	/* Clears the drawing area */
	void DrawDialog() const;

	/* Checks if the given y-coordinate is button */
	bool IsButton(int y);

	/* Get user clicked button */
	DialogBoxButton GetUserClick();

	/* Destructor */
	~Dialog();
};