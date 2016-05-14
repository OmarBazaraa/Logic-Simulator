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
	bool ValidCoordinates(int x, int y, Component * Comp);
	GraphicsInfo CalculateDimensions(Component* Comp,int x, int y, int &w, int &h);
};