#pragma once
#include "..\Actions\Action.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\AND.h"
#include "..\Components\OR.h"
#include "..\Components\NOT.h"
#include "..\Components\NAND.h"
#include "..\Components\NOR.h"
#include "..\Components\XOR.h"
#include "..\Components\XNOR.h"
#include "..\Components\AND3.h"
#include "..\Components\NOR3.h"
#include "..\Components\XOR3.h"
#include "..\Components\Buffer.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"
#include "..\Components\Connection.h"

class Move : public Action
{
private:
	int mX, mY;
	vector <Gate *> mPrvMovedComponents;			// list of the to be moved gates
	vector <Connection *> mPrvMovedConnections;		// list of the to be moved connections
	vector <GraphicsInfo> mPrvMovedGfxinfo;			// list of the old graphics info of the moved components
	vector <Gate *> mNewMovedComponents;			// list of the moved gates
	vector <Connection *> mNewMovedConnections;		// list of the moved connections
	vector <GraphicsInfo> mNewMovedGfxinfo;			// list of the new graphics info of the moved components

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
	/* Checks for the validity of the coordinates when adding the relative distance */
	bool ValidCoordinates(int dx, int dy, Component * Comp);

	/* Calculates the new Graphics Info that the component will be drawn in */
	GraphicsInfo CalculateDimensions(Component* Comp,int dx, int dy);

	/* Checks if the area of the graphics info is valid for a component to move into */
	bool ValidArea(GraphicsInfo& GfxInfo);

	/* Draws the component while the move is active highlighted when invalid coordinate */
	void DrawComponent(Component* pComp,GraphicsInfo& GfxInfo,bool invalid);

	/* Sets the component new Graphics Info if it goes out of borders */
	bool SetNewGateBorders(GraphicsInfo& GfxInfo);
};