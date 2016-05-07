#pragma once

class ApplicationManager; // Forward class declaration

/*
	Base abstract class for all possible user actions
*/
class Action
{
protected:
	ApplicationManager* mAppManager;	// Actions needs AppManager to do their job

public:
	/* Constructor */
	Action(ApplicationManager* pAppMan) { mAppManager = pAppMan; }
	
	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters() = 0;
	
	/* Executes action */
	virtual bool Execute() = 0;

	/* Undo action */
	virtual void Undo() = 0;

	/* Redo action */
	virtual void Redo() = 0;

	/* Destructor */
	virtual ~Action() {  }
};