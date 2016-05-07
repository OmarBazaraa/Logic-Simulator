#pragma once
#include "..\Actions\Action.h"
#include "..\ApplicationManager.h"
#include "..\Utilities\Utility.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"
#include "..\Actions\AddConnection.h"

class Edit : public Action
{
private:
	int mX, mY;				// The point clicked by the user
	string mNewLabel;		// The new label entered by the user
	string mPrvLabel;		// The previous label of the component
	Component* mComp;		// Pointer to the edited component

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

private:
	/* Detects the source component of the connection */
	bool DetectSourceComponent(GraphicsInfo &GfxInfo);

	/* Detects the destination component of the connection */
	bool DetectDestinationComponent(GraphicsInfo &GfxInfo);

	/*returns the name of the component needed to tell the user the name and the id of the component*/
	string GetComponentName(Component* comp);
};

