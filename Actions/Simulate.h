#pragma once
#include "..\Actions\Action.h"
#include "..\GUI\UserInterface.h"
#include "..\ApplicationManager.h"
#include "..\Utilities\Utility.h"
#include "..\Components\Component.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\Dialog.h"
#include "..\Components\LED.h"
#include "..\Components\Switch.h"
#include "..\Components\LogicGate.h"
#include "..\Components\Connection.h"
#include <string>
#include <set>
using namespace std;

class Simulate : public Action
{
private:
	set<Component*> mVisited,mCircuit;
	bool mStopSimulation;

public:
	/* Constructor */
	Simulate(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Tests the output on a led */
	int Cascade(Component*);

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~Simulate();
};
