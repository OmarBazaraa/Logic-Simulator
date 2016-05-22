#include "Move.h"

/* Constructor */
Move::Move(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Move::ReadActionParameters() {
	mAppManager->GetInput()->GetLastPointClicked(mX, mY);
	int n = mAppManager->GetComponentsCount();
	Output* pOut = mAppManager->GetOutput();
	Component* pComp = pOut->GetComponentAtPin(mX, mY);
	Component** list = mAppManager->GetComponentList();

	if (pComp != NULL && !pComp->IsSelected()) {
		mAppManager->DeselectComponents();
		pComp->SetSelected(true);
	}

	for (int i = 0; i < n; i++) {
		if (list[i]->IsSelected() && list[i]->GetAddActionType() != ADD_CONNECTION) {
			mMovedGates.push_back((Gate*)list[i]);
			mPrvGatesCoordinates.push_back(list[i]->GetGraphicsInfo());
		}
		else if (!list[i]->IsDeleted() && list[i]->GetAddActionType() == ADD_CONNECTION) {
			mConnections.push_back((Connection*)list[i]);
		}
	}
	
	return true;
}

/* Executes action */
bool Move::Execute() {
	ReadActionParameters();

	int n = mAppManager->GetComponentsCount();
	Output* pOut = mAppManager->GetOutput();
	Input* pIn = mAppManager->GetInput();
	Component* pComp = pOut->GetComponentAtPin(mX, mY);
	Component** list = mAppManager->GetComponentList();

	mAppManager->UpdateInterface();

	image wind;
	pOut->StoreImage(wind, 0, 0, UI.Width, UI.Height);

	int startX = mX, startY = mY, dx = 0, dy = 0;
	bool StopMoveAction = false, UndoMoveAction = false, OutOfBorders = false;
	normalizeCoordinates(startX, startY);
	int prvX = startX, prvY = startY;

	// Reading the mouse input from the user
	while (pIn->GetButtonState(LEFT_BUTTON, mX, mY) == BUTTON_DOWN) {
		normalizeCoordinates(mX, mY);
		
		dx = mX - startX, dy = mY - startY;

		if (prvX != mX || prvY != mY) {
			pOut->DrawImage(wind, 0, 0, UI.Width, UI.Height);

			for (int i = 0; i < mMovedGates.size(); i++) {
				GraphicsInfo mGfx = mMovedGates[i]->GetGraphicsInfo();
				int x = (mGfx.x1 + mGfx.x2) / 2;
				int y = (mGfx.y1 + mGfx.y2) / 2;

				GraphicsInfo NewGfx = CalculateDimensions(mMovedGates[i], dx, dy);
				
				OutOfBorders = SetNewGateBorders(NewGfx);

				pOut->SetPen(WHITE, 2);
				pOut->DrawLine(x, y, (NewGfx.x1 + NewGfx.x2) / 2, (NewGfx.y1 + NewGfx.y2) / 2);
				DrawComponent(mMovedGates[i], NewGfx, !ValidArea(NewGfx) || OutOfBorders);
			}

			prvX = mX;
			prvY = mY;
		}

		pOut->UpdateBuffer();
	}
	
	pOut->DrawImage(wind, 0, 0, UI.Width, UI.Height);

	// Checking for the validity of the coordinates
	for (int i = 0; i < mMovedGates.size(); i++) {
		StopMoveAction = !ValidCoordinates(dx, dy, mMovedGates[i]);
	}

	// checking if there is an invalid position
	if (StopMoveAction)
		return false;		// To prevent adding this action to the stack

	for (int i = 0; i < mConnections.size(); i++) {
		pOut->ClearConnectionPins(mConnections[i]->GetPath());
	}

	// start moving the gates to the new position and checking if it's in the same place
	for (int i = 0; i < mMovedGates.size(); i++) {
		GraphicsInfo mGfx = mMovedGates[i]->GetGraphicsInfo();
		GraphicsInfo NewGfx = CalculateDimensions(mMovedGates[i], dx, dy);

		UndoMoveAction = (mGfx == NewGfx);

		mMovedGates[i]->SetGraphicsInfo(pOut, NewGfx);
		mNewGatesCoordinates.push_back(NewGfx);
	}

	// start moving the connection to the new position and checking for the validity of the paths
	for (int i = 0; i < mConnections.size(); i++) {
		UndoMoveAction = !mConnections[i]->UpdatePath(pOut);
	}

	pOut->ClearDrawingArea();
	pOut->ClearStatusBar();
	pOut->FlushMouseQueue();

	// checking if there is a path that didn't manage to be drawn
	if (UndoMoveAction) {
		Undo();
		return false;	// To prevent adding this action to the stack
	}

	return true;
}

/* Undo action */
void Move::Undo() {
	Output* pOut = mAppManager->GetOutput();

	for (int i = 0; i < mConnections.size(); i++)
		pOut->ClearConnectionPins(mConnections[i]->GetPath());

	for (int i = 0; i < mMovedGates.size(); i++)
		mMovedGates[i]->SetGraphicsInfo(pOut, mPrvGatesCoordinates[i]);

	for (int i = 0; i < mConnections.size(); i++)
		mConnections[i]->UpdatePath(pOut);

	pOut->ClearDrawingArea();
}

/* Redo action */
void Move::Redo() {
	Output* pOut = mAppManager->GetOutput();

	for (int i = 0; i < mConnections.size(); i++)
		pOut->ClearConnectionPins(mConnections[i]->GetPath());

	for (int i = 0; i < mMovedGates.size(); i++)
		mMovedGates[i]->SetGraphicsInfo(pOut, mNewGatesCoordinates[i]);

	for (int i = 0; i < mConnections.size(); i++)
		mConnections[i]->UpdatePath(pOut);

	pOut->ClearDrawingArea();
}

/* Destructor */
Move::~Move() {

}

bool Move::ValidCoordinates(int dx, int dy, Component* Comp) {
	GraphicsInfo NewGfx = CalculateDimensions(Comp, dx, dy);

	if (!SetNewGateBorders(NewGfx) && ValidArea(NewGfx))
		return true;

	return false;
}

GraphicsInfo Move::CalculateDimensions(Component* Comp, int dx, int dy) {
	GraphicsInfo mGfx = Comp->GetGraphicsInfo();
	int NewX1, NewY1, NewX2, NewY2;
	NewX1 = dx + mGfx.x1;
	NewY1 = dy + mGfx.y1;
	NewX2 = dx + mGfx.x2;
	NewY2 = dy + mGfx.y2;

	if (NewX1 > NewX2) swap(NewX1, NewX2);
	if (NewY1 > NewY2) swap(NewY1, NewY2);

	normalizeCoordinates(NewX1, NewY1);
	normalizeCoordinates(NewX2, NewY2);
	NewX1 -= UI.PinMargin, NewY1 -= UI.PinMargin;
	NewX2 -= UI.PinMargin, NewY2 -= UI.PinMargin;

	return GraphicsInfo(NewX1, NewY1, NewX2, NewY2);
}

bool Move::ValidArea(GraphicsInfo & GfxInfo) {
	Output* pOut = mAppManager->GetOutput();

	for (int x = GfxInfo.x1; x < GfxInfo.x2; x++) {
		for (int y = GfxInfo.y1; y < GfxInfo.y2; y++) {
			Component* pComp = pOut->GetComponentAtPin(x, y);
			if (pComp != NULL && !pComp->IsSelected() && pComp->GetAddActionType() != ADD_CONNECTION)
				return false;
		}
	}

	return true;
}

void Move::DrawComponent(Component* pComp, GraphicsInfo& GfxInfo, bool Invalid) {
	ActionType actType = pComp->GetAddActionType();
	Output* pOut = mAppManager->GetOutput();
	string dir;

	switch (actType)
	{
	case ADD_GATE_AND:
		dir = (Invalid ? "Images\\components\\inactive\\and.png" : "Images\\components\\faded\\and.png");
		break;
	case ADD_GATE_OR:
		dir = (Invalid ? "Images\\components\\inactive\\or.png" : "Images\\components\\faded\\or.png");
		break;
	case ADD_GATE_NOT:
		dir = (Invalid ? "Images\\components\\inactive\\not.png" : "Images\\components\\faded\\not.png");
		break;
	case ADD_GATE_NAND:
		dir = (Invalid ? "Images\\components\\inactive\\nand.png" : "Images\\components\\faded\\nand.png");
		break;
	case ADD_GATE_NOR:
		dir = (Invalid ? "Images\\components\\inactive\\nor.png" : "Images\\components\\faded\\nor.png");
		break;
	case ADD_GATE_XOR:
		dir = (Invalid ? "Images\\components\\inactive\\xor.png" : "Images\\components\\faded\\xor.png");
		break;
	case ADD_GATE_XNOR:
		dir = (Invalid ? "Images\\components\\inactive\\xnor.png" : "Images\\components\\faded\\xnor.png");
		break;
	case ADD_GATE_AND3:
		dir = (Invalid ? "Images\\components\\inactive\\and3.png" : "Images\\components\\faded\\and3.png");
		break;
	case ADD_GATE_NOR3:
		dir = (Invalid ? "Images\\components\\inactive\\nor3.png" : "Images\\components\\faded\\nor3.png");
		break;
	case ADD_GATE_XOR3:
		dir = (Invalid ? "Images\\components\\inactive\\xor3.png" : "Images\\components\\faded\\xor3.png");
		break;
	case ADD_GATE_BUFFER:
		dir = (Invalid ? "Images\\components\\inactive\\buffer.png" : "Images\\components\\faded\\buffer.png");
		break;
	case ADD_SWITCH:
		dir = (Invalid ? "Images\\components\\inactive\\switch_off.png" : "Images\\components\\faded\\switch_off.png");
		break;
	case ADD_LED:
		dir = (Invalid ? "Images\\components\\inactive\\led_off.png" : "Images\\components\\faded\\led_off.png");
		break;
	}

	pOut->DrawPNG(dir, GfxInfo.x1, GfxInfo.y1);
}

bool Move::SetNewGateBorders(GraphicsInfo& GfxInfo) {
	int dx = 0, dy = 0;

	if (GfxInfo.x1 < 0)
		dx = -GfxInfo.x1;
	if (GfxInfo.y1 < UI.GateBarHeight + UI.ToolBarHeight)
		dy = UI.GateBarHeight + UI.ToolBarHeight - GfxInfo.y1;
	if (GfxInfo.x2 > UI.Width)
		dx = UI.Width - GfxInfo.x2;
	if (GfxInfo.y2 > UI.Height - UI.StatusBarHeight)
		dy = UI.Height - UI.StatusBarHeight - GfxInfo.y2;

	GfxInfo.x1 += dx;
	GfxInfo.y1 += dy;
	GfxInfo.x2 += dx;
	GfxInfo.y2 += dy;

	return (dx != 0 || dy != 0);
}