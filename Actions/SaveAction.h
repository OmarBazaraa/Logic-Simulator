#pragma once
#include "..\Actions\Action.h"
#include "..\ApplicationManager.h"
#include <fstream>

class SaveAction : public Action
{
private:
	ofstream mWrite;

public:
	/* Constructor */
	SaveAction(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */	
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~SaveAction();
};

