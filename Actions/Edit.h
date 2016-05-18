#pragma once
#include "..\Actions\Action.h"
#include "..\Actions\AddConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"

class Edit : public Action
{
private:
	int mX, mY;							// The point clicked by the user
	int mNewDstPinIndex;				// The new index of the destination pin
	int mPrvDstPinIndex;				// The previous index of the destination pin
	string mNewLabel;					// The new label entered by the user
	string mPrvLabel;					// The previous label of the component
	Pin* mNewSrcPin;					// The new source pin for the connection
	Pin* mPrvSrcPin;					// The previous source pin of the connection
	Pin* mNewDstPin;					// The new destination pin for the connection
	Pin* mPrvDstPin;					// The previous destination pin of the connection
	GraphicsInfo mNewGfxInfo;			// The parameters (coordinates) required to draw the connection
	GraphicsInfo mPrvGfxInfo;			// The parameters (coordinates) required to draw the connection
	vector<GraphicsInfo>* mNewPath;		// The path of the connection
	vector<GraphicsInfo> mPrvPath;		// The path of the connection
	Component* mComp;					// Pointer to the edited component

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
	bool DetectSourceComponent();

	/* Detects the destination component of the connection */
	bool DetectDestinationComponent();
};

