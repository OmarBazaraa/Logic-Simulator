#pragma once
#include "Action.h"
#include "..\GUI\UserInterface.h"
#include "..\ApplicationManager.h"
#include "..\Utilities\Utility.h"
#include "..\Components\Component.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Components\LED.h"
#include "..\Components\Switch.h"
#include "..\Components\LogicGate.h"
#include "..\Components\Connection.h"
#include <fstream>
#include <string>
using namespace std;

class TruthTable : public Action
{
	LED** mLeds;			// List of existing leds
	Switch** mSwitches;		// List of existing switches
	int* mSwitchesDefault;	
	int mRows;				// Number of rows in truth table
	int mColumns;            // Number of columns in truth table
	int mSwitchesCount;      // Number of switches in design
	int mLedsCount;          // Number of leds in design
	window* pWind;			// Pointer to the graphical Window object
	bool mCanDraw;           // If you can write on window or not
	ofstream mWrite;         // txt file to write truth table

public:
	/* Constructor */
	TruthTable(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	//* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~TruthTable();

private:
	/* Populates */
	void Populate();

	/* Draws truth table window */
	void DrawWindow();
	
	/* Clears the drawing area */
	void ClearDrawingArea() const;

	/* Draws truth table */
	void DrawTruthTable() const;

	/* Hovers */
	void Hover(bool stopHovering);

	/* Draws exit button */
	void DrawExit() const;
	
	/* Draws headers */
	void DrawHeaders();

	/* Normalizes message to fit */
	void Normalizetxt(string& msg);

	/* Creates all possible compinations of inputs on switches */
	void CreateCompinations(string compination);

	/* Tests input */
	void Test(string k);

	/* Cascades */
	void Cascade(queue<Component*>qComp);

	/* changes string to int */
	int ToInt(string k);

	/* Returns switches status to default */
	void ReturnToDefault();

	/* Exits Truth Table */
	void Exits();

	/* Checks if the value of coordinates is on exit button */
	bool TruthTable::IsButton(int x, int y);
};

