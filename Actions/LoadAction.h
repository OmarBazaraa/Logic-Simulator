#pragma once
#include "..\Actions\Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Dialog.h"
#include <fstream>

class LoadAction : public Action
{
private:
	ifstream mRead;

public:
	/* Constructor */
	LoadAction(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~LoadAction();
};

