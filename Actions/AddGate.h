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
#include <vector>

class AddGate : public Action
{
private:
	bool mIsLoaded;						// Indicates if the action is loaded from the file or not
	int mX, mY;							// Center point of the gate
	GraphicsInfo mGfxInfo;				// The parameters (coordinates) required to draw the gate
	string mLabel;						// The label of the component
	Gate* mGate;						// Pointer to the added gate
	ActionType mActType;				// The type of the action
	vector<Connection*> mConnections;	// list of all connections to be updated

public:
	/* Constructor */
	AddGate(ApplicationManager* pAppMan, ActionType actType, Data* pLoadedData = NULL);

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

	/* Adjusts gate's coordinates if it goes out of borders */
	bool AddGate::AdjustGateCoordinates(GraphicsInfo& GfxInfo);

	/* Draws the gate in its current state: faded or invalid */
	void AddGate::DrawGate(bool valid);

	/* Creates the required gate */
	void CreateGate();
};