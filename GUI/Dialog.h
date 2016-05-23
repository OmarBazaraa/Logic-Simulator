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
	string mMsg;                    // Message to be printed in the dialog box
	DialogBoxType mType;            // Type of dialog object
public:
	/* Constructor that initializes the user interface */
	Dialog(string s, DialogBoxType pType = Type_A);

	/* Draws dialog box */
	void DrawDialog() const;

	/* Draws OK button */
	void DrawOK() const;

	/* Draws YES button */
	void DrawYES() const;

	/* Draws NO button */
	void DrawNO() const;

	/* Draws CANCEL button */
	void DrawCANCEL() const;

	/* Get user clicked button */
	DialogBoxButton GetUserClick();

	/* Checks if the given y-coordinate is button */
	bool IsButton(int x, int y);

	/* Destructor */
	~Dialog();
};