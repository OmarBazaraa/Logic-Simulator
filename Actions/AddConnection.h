#pragma once
#include "..\Actions\Action.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"

class AddConnection : public Action
{
private:
	int mDstPinIndex;				// The index of the destination pin
	GraphicsInfo mGfxInfo;			// The parameters (coordinates) required to draw the connection
	vector<GraphicsInfo>* mPath;	// The path of the connection
	string mLabel;					// The label of the component
	Pin* mSrcPin;					// Pointer to the source pin
	Pin* mDstPin;					// Pointer to the destination pin
	Connection* mConnection;		// Pointer to the added connection

public:
	/* Constructor */
	AddConnection(ApplicationManager* pAppMan, int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~AddConnection();

private:
	/* Detects the source component of the connection */
	bool DetectSourceComponent();

	/* Detects the destination component of the connection */
	bool DetectDestinationComponent();
};