#pragma once
#include "..\Actions\Action.h"
#include "..\Components\Component.h"
#include "..\ApplicationManager.h"
#include "..\Utilities\Utility.h"
#include "..\Components\Connection.h"
#include <fstream>

class Save : public Action
{
private:
	ofstream write;

public:
	/* Constructor */
	Save(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~Save();
};

