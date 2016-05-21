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
	LED**leds;              // List of existing leds
	Switch**switches;       // List of existing switches
	int*switchesDefault;
	int rows;               // Number of rows in truth table
	int columns;            // Number of columns in truth table
	int switchesCount;      // Number of switches in design
	int ledsCount;          // Number of leds in design
	window* pWind;			// Pointer to the graphical Window object
	bool canDraw;           // If you can write on window or not
	ofstream write;         // txt file to write truth table
public:
	/* Constructor */
	TruthTable(ApplicationManager* pAppMan);

	/* Executes action */
	virtual bool Execute();

	/* Creates a new Window object */
	window* CreateWind(int w, int h, int x, int y) const;

	/* Chnages the title of the Window */
	void ChangeTitle(const string& title) const;

	/*Clears the drawing area */
	void ClearDrawingArea() const;

	/*Draws truth table*/
	void DrawTruthTable() const;

	/*Create Compinations*/
	void CreateCompinations(string k);

	/*Test input*/
	void Test(string k);

	/*changes string to int*/
	int ToInt(string k);

	/*Tests the output on a led*/
	int TestGate(Component*);

	/*Draw headers*/
	void DrawHeaders();

	/* Normalize message position */
	void Normalizetxt(string&);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters() { return true; }

	/* Undo action */
	virtual void Undo() {}

	///* Redo action */
	virtual void Redo() {}

	/* Destructor */
	virtual ~TruthTable();
};

