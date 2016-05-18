#pragma once
#include "..\Actions\Action.h"
#include "..\Actions\AddConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"

class Edit : public Action
{
private:
	int mX, mY;				// The point clicked by the user
	string mNewLabel;		// The new label entered by the user
	string mPrvLabel;		// The previous label of the component
	Component* mComp;		// Pointer to the edited component
	AddConnection* mAct;	// Action to edit the source and destination pins of the connection

public:
	/* Constructor */
	Edit(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~Edit();
};

