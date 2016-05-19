#pragma once
#include "..\Actions\Action.h"
#include "..\ApplicationManager.h"
#include "..\Utilities\Utility.h"
#include "..\Components\AND.h"
#include "..\Components\OR.h"
#include "..\Components\NOT.h"
#include "..\Components\NAND.h"
#include "..\Components\NOR.h"
#include "..\Components\XOR.h"
#include "..\Components\XNOR.h"
#include "..\Components\AND3.h"
#include "..\Components\NOR3.h"
#include "..\Components\XOR3.h"
#include "..\Components\Buffer.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"

class AddGate : public Action
{
private:
	int mX, mY;				// Center point of the gate
	GraphicsInfo mGfxInfo;	// The parameters (coordinates) required to draw the gate
	string mLabel;			// The label of the component
	ActionType mActType;	// The type of the action
	Gate* mGate;			// Pointer to the added gate

public:
	/* Constructor */
	AddGate(ApplicationManager* pAppMan, ActionType actType, int x = -1, int y = -1, string label = "");

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~AddGate();

private:
	/* Returns the message needed to guide the user */
	string GetActionMsg();

	/* Calculates the rectangular bound of the gate */
	void CalculateDimensions();

	/* Creates the required gate */
	void CreateGate();
};