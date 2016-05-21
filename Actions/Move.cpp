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
		for (int i = 0; i < n; i++)	list[i]->SetSelected(false);
		pComp->SetSelected(true);
	}

	for (int i = 0; i < n; i++)
		if (list[i]->IsSelected() && list[i]->GetAddActionType() != ADD_CONNECTION) {
			Gate* ptr = dynamic_cast <Gate *>(list[i]);
			mPrvMovedComponents.push_back(ptr);
			mPrvMovedGfxinfo.push_back(ptr->GetGraphicsInfo());
		}
	for (int i = 0; i < n; i++)
		if (list[i]->GetAddActionType() == ADD_CONNECTION)
			mPrvMovedConnections.push_back(dynamic_cast <Connection *> (list[i]));

	return true;
}

/* Executes action */
bool Move::Execute() {
	ReadActionParameters();

	bool StopMoveAction = false, UndoMoveAction = false, OutOfBorders = false;
	int n = mAppManager->GetComponentsCount();
	int oldX = mX, oldY = mY, dx = 0, dy = 0;
	Output* pOut = mAppManager->GetOutput();
	Component* pComp = pOut->GetComponentAtPin(mX, mY);
	Component** list = mAppManager->GetComponentList();

	mAppManager->UpdateInterface();
	image DrawingArea;
	pOut->StoreImage(DrawingArea, 0, 0, UI.Width, UI.Height);

	// Reading the mouse input from the user
	int prvX = mX, prvY = mY;
	while (pOut->GetButtonState(LEFT_BUTTON, mX, mY) == BUTTON_DOWN) {
		dx = mX - oldX, dy = mY - oldY;

		normalizeCoordinates(mX, mY);

		if (prvX != mX || prvY != mY) {
			pOut->DrawImage(DrawingArea, 0, 0, UI.Width, UI.Height);
			for (int i = 0; i < n; i++) {
				if (list[i]->IsSelected()) {
					GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
					int x = (mGfx.x1 + mGfx.x2) / 2;
					int y = (mGfx.y1 + mGfx.y2) / 2;
					if (list[i]->GetAddActionType() != ADD_CONNECTION) {
						OutOfBorders = false;
						GraphicsInfo NewGfx = CalculateDimensions(list[i], dx, dy);
						if (SetNewGateBorders(NewGfx))
							OutOfBorders = true;

						pOut->SetPen(WHITE, 1);
						pOut->DrawLine(x, y, (NewGfx.x1 + NewGfx.x2) / 2, (NewGfx.y1 + NewGfx.y2) / 2);
						DrawComponent(list[i], NewGfx, !ValidArea(NewGfx) || OutOfBorders);
					}
				}
			}
			prvX = mX;
			prvY = mY;
		}
	}
	
	pOut->DrawImage(DrawingArea, 0, 0, UI.Width, UI.Height);

	// Checking for the validity of the coordinates
	for (int i = 0; i < n; i++) {
		if (list[i]->IsSelected()) {
			GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
			if (list[i]->GetAddActionType() != ADD_CONNECTION && !ValidCoordinates(dx, dy, list[i]))
					StopMoveAction = true;
		}
	}

	// checking if there is an invalid position
	if (StopMoveAction)
		return false;		// To prevent adding this action to the stack


	int count = mPrvMovedConnections.size();
	for (int i = 0; i < count; i++) {
		vector <GraphicsInfo> Path = mPrvMovedConnections[i]->GetPath();
		pOut->ClearConnectionPins(Path);
	}

	// start moving the gates to the new position and checking if it's in the same place
	for (int i = 0; i < n; i++) {
		if (list[i]->IsSelected() && list[i]->GetAddActionType() != ActionType::ADD_CONNECTION) {
			GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
			GraphicsInfo NewGfx = CalculateDimensions(list[i], dx, dy);

			if (mGfx.x1 == NewGfx.x1 && mGfx.x2 == NewGfx.x2 && mGfx.y1 == NewGfx.y1 && mGfx.y2 == NewGfx.y2)
				UndoMoveAction = true;

			Gate* ptr = dynamic_cast <Gate *> (list[i]);
			ptr->SetGraphicsInfo(pOut, NewGfx);

			mNewMovedComponents.push_back(ptr);
			mNewMovedGfxinfo.push_back(NewGfx);
		}
	}

	// start moving the connection to the new position and checking for the validity of the pathes
	for (int i = 0; i < n; i++) {
		if (list[i]->GetAddActionType() == ADD_CONNECTION) {
			Connection* ptr = dynamic_cast <Connection *> (list[i]);
			if (!ptr->UpdatePath(pOut))
				UndoMoveAction = true;
			else
				mNewMovedConnections.push_back(ptr);
		}
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

bool Move::ValidCoordinates(int dx, int dy,Component* Comp) {
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
	if (NewX1 > NewX2)
		swap(NewX1, NewX2);
	if (NewY1 > NewY2)
		swap(NewY1, NewY2);

	normalizeCoordinates(NewX1, NewY1);
	normalizeCoordinates(NewX2, NewY2);
	NewX1 -= UI.PinMargin;	NewY1 -= UI.PinMargin;
	NewX2 -= UI.PinMargin;	NewY2 -= UI.PinMargin;
	GraphicsInfo NewGfx(NewX1, NewY1, NewX2, NewY2);
	return NewGfx;
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

void Move::DrawComponent(Component * pComp, GraphicsInfo& GfxInfo, bool Invalid) {
	ActionType actType = pComp->GetAddActionType();
	Output* pOut = mAppManager->GetOutput();
	string dir;
	switch (actType)
	{
	case ADD_GATE_AND:
		dir = (Invalid ? "Images\\components\\inactive\\and.png" : "Images\\components\\active\\and.jpg");
		break;
	case ADD_GATE_OR:
		dir = (Invalid ? "Images\\components\\inactive\\or.png" : "Images\\components\\active\\or.jpg");
		break;
	case ADD_GATE_NOT:
		dir = (Invalid ? "Images\\components\\inactive\\not.png" : "Images\\components\\active\\not.jpg");
		break;
	case ADD_GATE_NAND:
		dir = (Invalid ? "Images\\components\\inactive\\nand.png" : "Images\\components\\active\\nand.jpg");
		break;
	case ADD_GATE_NOR:
		dir = (Invalid ? "Images\\components\\inactive\\nor.png" : "Images\\components\\active\\nor.jpg");
		break;
	case ADD_GATE_XOR:
		dir = (Invalid ? "Images\\components\\inactive\\xor.png" : "Images\\components\\active\\xor.jpg");
		break;
	case ADD_GATE_XNOR:
		dir = (Invalid ? "Images\\components\\inactive\\xnor.png" : "Images\\components\\active\\xnor.jpg");
		break;
	case ADD_GATE_AND3:
		dir = (Invalid ? "Images\\components\\inactive\\and3.png" : "Images\\components\\active\\and3.jpg");
		break;
	case ADD_GATE_NOR3:
		dir = (Invalid ? "Images\\components\\inactive\\nor3.png" : "Images\\components\\active\\nor3.jpg");
		break;
	case ADD_GATE_XOR3:
		dir = (Invalid ? "Images\\components\\inactive\\xor3.png" : "Images\\components\\active\\xor3.jpg");
		break;
	case ADD_GATE_BUFFER:
		dir = (Invalid ? "Images\\components\\inactive\\buffer.png" : "Images\\components\\active\\buffer.jpg");
		break;
	case ADD_SWITCH:
		dir = (Invalid ? "Images\\components\\inactive\\switch_off.png" : "Images\\components\\active\\switch_off.jpg");
		break;
	case ADD_LED:
		dir = (Invalid ? "Images\\components\\inactive\\led_off.png" : "Images\\components\\active\\led_off.jpg");
		break;
	default:
		break;
	}
	Invalid ? pOut->DrawPNG(dir, GfxInfo.x1, GfxInfo.y1) : pOut->DrawImage(dir, GfxInfo.x1, GfxInfo.y1, GfxInfo.x2 - GfxInfo.x1, GfxInfo.y2 - GfxInfo.y1);
}

bool Move::SetNewGateBorders(GraphicsInfo & GfxInfo) {
	int dx = 0, dy = 0;
	if (GfxInfo.x1 < 0)
		dx = 1 - GfxInfo.x1;
	if (GfxInfo.y1 < UI.GateBarHeight + UI.ToolBarHeight)
		dy = 1 + UI.GateBarHeight + UI.ToolBarHeight - GfxInfo.y1;
	if (GfxInfo.y2 > UI.Height - UI.StatusBarHeight)
		dy = UI.Height - UI.StatusBarHeight - GfxInfo.y2;
	if (GfxInfo.x2 > UI.Width)
		dx = UI.Width -  GfxInfo.x2;
	GfxInfo.x1 += dx;
	GfxInfo.x2 += dx;
	GfxInfo.y1 += dy;
	GfxInfo.y2 += dy;

	return (dx != 0 || dy != 0);
}

/* Undo action */
void Move::Undo() {
	int n = mPrvMovedComponents.size();
	Output* pOut = mAppManager->GetOutput();

	for (int i = 0; i < mPrvMovedConnections.size(); i++)
		pOut->ClearConnectionPins(mPrvMovedConnections[i]->GetPath());

	for (int i = 0; i < n; i++)
		mPrvMovedComponents[i]->SetGraphicsInfo(pOut, mPrvMovedGfxinfo[i]);

	n = mPrvMovedConnections.size();
	for (int i = 0; i < n; i++)
		mPrvMovedConnections[i]->UpdatePath(pOut);

	pOut->ClearDrawingArea();
}

/* Redo action */
void Move::Redo() {
	int n = mNewMovedComponents.size();
	Output* pOut = mAppManager->GetOutput();

	for (int i = 0; i < mNewMovedConnections.size(); i++)
		pOut->ClearConnectionPins(mNewMovedConnections[i]->GetPath());

	for (int i = 0; i < n; i++)
		mNewMovedComponents[i]->SetGraphicsInfo(pOut, mNewMovedGfxinfo[i]);

	n = mNewMovedConnections.size();
	for (int i = 0; i < n; i++)
		mNewMovedConnections[i]->UpdatePath(pOut);
	pOut->ClearDrawingArea();
}

/* Destructor */
Move::~Move() {

}