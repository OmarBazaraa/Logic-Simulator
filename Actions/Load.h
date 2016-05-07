#pragma once
#include<fstream>
#include "Action.h"
#include"..\Actions\AddGate.h"
#include "..\ApplicationManager.h"
#include "..\Utilities\Utility.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include <string>
class Load : public Action
{
	ifstream read;
public:
	/* Constructor */
	Load(ApplicationManager* pAppMan);

	/* Executes action */
	virtual bool Execute();

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters() { return true; }

	/* Undo action */
	virtual void Undo() {}

	///* Redo action */
	virtual void Redo() {}

	/* Destructor */
	virtual ~Load();
};

