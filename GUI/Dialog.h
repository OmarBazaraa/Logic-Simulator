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
	image WindowImage;				// Image to the current look of the window

public:
	/* Constructor that initializes the user interface */
	Dialog(string s);

	/* Creates an Input object and assigns it to the same Window */
	Input* CreateInput() const;

	/* Creates a new Window object */
	window* CreateWind(int w, int h, int x, int y) const;

	/* Chnages the title of the Window */
	void ChangeTitle(const string& title) const;

	/* Clears the drawing area */
	void ClearDrawingArea() const;

	/* Prints a message on the status bar */
	void PrintMsg(const string& msg) const;

	/* Checks if the given y-coordinate is within the drawing area */
	bool IsDrawingArea(int y);

	/* Stores and returns an image with certain coordinates */
	void StoreImage(image &imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight);

	/* Get information on the current state of the mouse buttons and it's position */
	buttonstate GetButtonState(const button btMouse, int &iX, int &iY);

	/* Draws a given Image to the window */
	void DrawImage(const image &imgThis, const int iX, const int iY, const int iWidth, const int iHeight);

	/* Sets the Brush with a certain color */
	color SetBrush(const color &colBrush);

	/* Sets the Pen with a certain color */
	color SetPen(const color c,int width);

	/* Draws a line from a ceratin to a certain coordinates */
	void DrawLine(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle = FRAME);

	/* Waits for click from the mouse */
	clicktype WaitMouseClick(int &iX, int &iY);

	/* Draws a Rectangle From given Coordinates */
	void DrawRectangle(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle = FRAME, const int iWidth = 0, const int iHeight = 0);

	/* Flushes all the press to the mouse queue */
	void FlushMouseQueue();

	/* Stores the current window looking and puts it in the window variable */
	void StoreWindowImage();

	/* Returns the window Image */
	image GetWindowImage();

	/* Destructor */
	~Dialog();
};