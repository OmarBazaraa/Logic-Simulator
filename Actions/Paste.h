#pragma once
#include "..\Actions\Action.h"
#include "..\Actions\AddGate.h"
#include "..\Actions\AddConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"

class Paste : public Action
{
private:
	Component* mComp;		// Pointer to the pasted component
	Action* mAct;			// Add component action

public:
	/* Constructor */
	Paste(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~Paste();
};

