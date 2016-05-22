#pragma once
#include "..\Utilities\Defs.h"
#include "..\Utilities\Utility.h"
#include "..\GUI\UserInterface.h"
#include "..\GUI\Input.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <vector>
#include <queue>

/*
	A class responsible for performing any output to the screen
	The application manager should have a pointer to this class
*/
class Output
{
private:
	window* pWind;					// Pointer to the graphical Window object
	PinInfo** mPinGrid;				// Grid containing the information of each pin

public:
	/* Constructor that initializes the user interface */
	Output();

	/* Creates an Input object and assigns it to the same Window */
	Input* CreateInput() const;

	/* Creates a new Window object */
	window* CreateWind(int w, int h, int x, int y) const;

	/* Chnages the title of the Window */
	void ChangeTitle(const string& title) const;

	/* Draws the tool bar */
	void CreateToolBar(int hoverdItem = -1) const;

	/* Draws the the gate bar */
	void CreateGateBar(int hoverdItem = -1) const;

	/* Draws the status bar */
	void CreateStatusBar() const;

	/* Updates the window with double buffering */
	void UpdateBuffer();

	/* Clears the drawing area */
	void ClearDrawingArea() const;

	/* Clears the status bar */
	void ClearStatusBar() const;

	/* Prints a message on the status bar */
	void PrintMsg(const string& msg) const;

	/* Draws label */
	void DrawLabel(int x, int y, const string& label) const;

	/* Draws the selection rectangle from the given coordinates */
	void DrawSelectionRectangle(int x1, int y1, int x2, int y2);

	/* Draws components */
	void DrawAND(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawOR(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawNOT(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawNAND(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawNOR(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawXOR(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawXNOR(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawAND3(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawNOR3(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawXOR3(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawBuffer(const GraphicsInfo& gfxInfo, bool selected = false) const;
	void DrawSwitch(const GraphicsInfo& gfxInfo, bool selected = false, bool on = false) const;
	void DrawLED(const GraphicsInfo& gfxInfo, bool selected = false, bool on = false) const;

	/* Draws connection */
	void DrawConnection(const vector<GraphicsInfo>& path, bool selected = false, bool on = false);

	/* Checks if the given y-coordinate is within the drawing area */
	bool IsDrawingArea(int x, int y);

	/* Checks if the given area of pins is empty */
	bool IsEmptyArea(const GraphicsInfo& gfxInfo) const;

	/* Marks the given area of pins */
	void MarkPins(const GraphicsInfo& gfxInfo, PinType mark, Component* comp);

	/* Marks the pins of the connection as used */
	void MarkConnectionPins(const vector<GraphicsInfo>& path, Component* comp);

	/* Clears the pins of the connection */
	void ClearConnectionPins(const vector<GraphicsInfo>& path);

	/* Returns the grid of pins */
	Component* GetComponentAtPin(int x, int y) const;

	/* Returns the shortest available path for the connection, null if no path found */
	vector<GraphicsInfo>* GetConnectionPath(const GraphicsInfo& gfxInfo);

	/* Stores and returns an image with certain coordinates */
	void StoreImage(image &imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight);

	/* Draws a given Image to the window */
	void DrawImage(const image &imgThis, const int iX, const int iY, const int iWidth, const int iHeight);

	/* Draws a given Image to the window */
	void DrawPNG(string dir, int x, int y);

	/* Sets the Pen with a certain color */
	color SetPen(const color c,int width);

	/* Draws a line from a ceratin to a certain coordinates */
	void DrawLine(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle = FRAME);

	/* Flushes all the press to the mouse queue */
	void FlushMouseQueue();

	/* Destructor */
	~Output();

private:
	/* Generate the connection path */
	vector<GraphicsInfo>* GenerateConnectionPath(Node& src, Node& dst, Node parents[UI.HorPinsCount][UI.VerPinsCount]);

	/* Checks if the given pin is valid or not */
	bool IsValidNode(const Node& cur, const Node& par);
};