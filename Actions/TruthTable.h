#pragma once
#include<fstream>
#include<string>
#include "Action.h"
#include "..\GUI\UserInterface.h"
#include "..\ApplicationManager.h"
#include "..\Utilities\Utility.h"
#include "..\Components\Component.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Components\LED.h"
#include "..\Components\Switch.h"
#include"..\Components\LogicGate.h"
#include "..\Components\Connection.h"
using namespace std;
class TruthTable : public Action
{
	LED** mLeds;              // List of existing leds
	Switch** mSwitches;       // List of existing switches
	int* mSwitchesDefault;
	int mRows;               // Number of rows in truth table
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

	/* Creates a new Window object */
	window* CreateWind(int w, int h, int x, int y) const;

	/* Changes the title of the Window */
	void ChangeTitle(const string& title) const;

	/*Clears the drawing area */
	void ClearDrawingArea() const;

	/*Draws truth table*/
	void DrawTruthTable() const;

	/* Draws exit button */
	void DrawExit() const;
	
	/* Draws headers */
	void DrawHeaders();

	/* Normalize message position */
	void Normalizetxt(string& msg);

	/*Create Compinations*/
	void CreateCompinations(string compination);

	/*Test input*/
	void Test(string k);

	/*changes string to int*/
	int ToInt(string k);

	/*Tests the output on a led*/
	int TestGate(Component*);

	/* Returns switches status to default */
	void ReturnToDefault();

	/* Exits Truth Table */
	void Exits();

	/* detects if the value of those coordinates */
	bool TruthTable::IsButton(int x, int y);

	/* Hovers */
	void Hover(bool stopHovering);
};

