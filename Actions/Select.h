#pragma once
#include "..\Actions\Action.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include <set>

class Select : public Action
{
private:
	char mHotKey;
	keytype mKeyType;
	int mStartX, mEndX;
	int mStartY, mEndY;
	set<Component*> mSelectedComps;

public:
	/* Constructor */
	Select(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~Select();
};

