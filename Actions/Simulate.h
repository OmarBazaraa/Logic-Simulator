#pragma once
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
class Simulate : public Action
{
public:
	/* Constructor */
	Simulate(ApplicationManager* pAppMan);

	/* Executes action */
	virtual bool Execute();

	/*Test input*/
	void Test();

	/*Tests the output on a led*/
	int TestGate(Component*);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters() { return true; }

	/* Undo action */
	virtual void Undo() {}

	///* Redo action */
	virtual void Redo() {}

	/* Destructor */
	virtual ~Simulate();
};

