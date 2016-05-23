#pragma once
#include "..\Actions\Action.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"
#include <vector>

class Move : public Action
{
private:
	int mStartX, mStartY;
	vector<Gate*> mSelectedGates;				// list of selected gates to be moved
	vector<Connection*> mConnections;			// list of all connections to be updated
	vector<GraphicsInfo> mPrvGatesCoordinates;	// list of previous coordinates of the moved gates
	vector<GraphicsInfo> mNewGatesCoordinates;	// list of new coordinates of the selected gates

public:
	/* Constructor */
	Move(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual bool ReadActionParameters();

	/* Executes action */
	virtual bool Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~Move();

private:
	/* Checks if the given area is valid for moving a component to it or not */
	bool IsValidArea(const GraphicsInfo& gfxInfo);

	/* Sets the component new coordinates if it goes out of borders */
	bool SetNewGateBorders(GraphicsInfo& GfxInfo);

	/* Calculates and returns the new coordinates of the gate */
	GraphicsInfo CalculateDimensions(Component* pComp, int dx, int dy);

	/* Draws the component in its current state: faded or invalid */
	void DrawComponent(Component* pComp, const GraphicsInfo& gfxInfo, bool invalid);
};