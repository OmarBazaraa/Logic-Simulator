#include "Move.h"

/* Constructor */
Move::Move(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Move::ReadActionParameters() {
	mAppManager->GetInput()->GetLastPointClicked(mStartX, mStartY);
	normalizeCoordinates(mStartX, mStartY);
	
	Output* pOut = mAppManager->GetOutput();
	Component* pComp = pOut->GetComponentAtPin(mStartX, mStartY);

	if (pComp != NULL && !pComp->IsSelected()) {
		mAppManager->DeselectComponents();
		pComp->SetSelected(true);
	}

	int n = mAppManager->GetComponentsCount();
	Component** list = mAppManager->GetComponentList();

	for (int i = 0; i < n; i++) {
		if (list[i]->IsSelected() && list[i]->GetAddActionType() != ADD_CONNECTION) {
			mSelectedGates.push_back((Gate*)list[i]);
			mPrvGatesCoordinates.push_back(list[i]->GetGraphicsInfo());
		}
		else if (!list[i]->IsDeleted() && list[i]->GetAddActionType() == ADD_CONNECTION) {
			mConnections.push_back((Connection*)list[i]);
		}
	}

	mAppManager->UpdateInterface();
	return true;
}

/* Executes action */
bool Move::Execute() {
	ReadActionParameters();

	Output* pOut = mAppManager->GetOutput();
	Input* pIn = mAppManager->GetInput();

	int x = mStartX, prvX = x, dx = 0;
	int y = mStartY, prvY = y, dy = 0;

	int minX = 0;
	int maxX = UI.Width;
	int minY = UI.ToolBarHeight + UI.GateBarHeight;
	int maxY = UI.Height - UI.StatusBarHeight;

	// Store the previous window
	image wind;
	pOut->StoreImage(wind, 0, 0, UI.Width, UI.Height);

	// Reading the mouse input from the user
	while (pIn->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_DOWN) {
		normalizeCoordinates(x, y);

		if (x < minX || x > maxX) x = prvX;
		if (y < minY || y > maxY) y = prvY;
		
		dx = x - mStartX;
		dy = y - mStartY;

		if (x != prvX || y != prvY) {
			pOut->DrawImage(wind, 0, 0, UI.Width, UI.Height);

			for (int i = 0; i < mSelectedGates.size(); i++) {
				GraphicsInfo prvCoord = mSelectedGates[i]->GetGraphicsInfo();

				int x1 = (prvCoord.x1 + prvCoord.x2) / 2;
				int y1 = (prvCoord.y1 + prvCoord.y2) / 2;

				GraphicsInfo newCoord = CalculateDimensions(mSelectedGates[i], dx, dy);

				bool outOfBorders = SetNewGateBorders(newCoord);

				int x2 = (newCoord.x1 + newCoord.x2) / 2;
				int y2 = (newCoord.y1 + newCoord.y2) / 2;				

				pOut->DrawMoveLine(x1, y1, x2, y2);
				DrawComponent(mSelectedGates[i], newCoord, !IsValidArea(newCoord) || outOfBorders);
			}

			prvX = x;
			prvY = y;
		}

		pOut->UpdateBuffer();
	}
	
	// Redraw the initial window
	pOut->DrawImage(wind, 0, 0, UI.Width, UI.Height);
	pOut->UpdateBuffer();

	// No changes in the positions
	if (dx == 0 && dy == 0) {
		return false;	
	}

	// Check for the validity of the coordinates
	for (int i = 0; i < mSelectedGates.size(); i++) {
		GraphicsInfo newCoord = CalculateDimensions(mSelectedGates[i], dx, dy);

		if (!pOut->IsDrawingArea(newCoord.x1, newCoord.y1) || !pOut->IsDrawingArea(newCoord.x2, newCoord.y2) || !IsValidArea(newCoord)) {
			return false;
		}
	}

	// Clear all connections' path to free up space for moving the gates
	for (int i = 0; i < mConnections.size(); i++) {
		pOut->ClearConnectionPins(mConnections[i]->GetPath());
	}

	// Set the new coordinates of the gates
	for (int i = 0; i < mSelectedGates.size(); i++) {
		GraphicsInfo newCoord = CalculateDimensions(mSelectedGates[i], dx, dy);
		mSelectedGates[i]->SetGraphicsInfo(pOut, newCoord);
		mNewGatesCoordinates.push_back(newCoord);
	}

	// Update connections' path if available
	for (int i = 0; i < mConnections.size(); i++) {
		if (!mConnections[i]->UpdatePath(pOut)) {
			Undo();
			return false;
		}
	}

	pOut->ClearDrawingArea();
	pOut->ClearStatusBar();

	return true;
}

/* Undo action */
void Move::Undo() {
	Output* pOut = mAppManager->GetOutput();

	for (int i = 0; i < mConnections.size(); i++) {
		pOut->ClearConnectionPins(mConnections[i]->GetPath());
	}
		
	for (int i = 0; i < mSelectedGates.size(); i++) {
		mSelectedGates[i]->SetGraphicsInfo(pOut, mPrvGatesCoordinates[i]);
	}
		
	for (int i = 0; i < mConnections.size(); i++) {
		mConnections[i]->UpdatePath(pOut);
	}
		
	pOut->ClearDrawingArea();
}

/* Redo action */
void Move::Redo() {
	Output* pOut = mAppManager->GetOutput();

	for (int i = 0; i < mConnections.size(); i++) {
		pOut->ClearConnectionPins(mConnections[i]->GetPath());
	}

	for (int i = 0; i < mSelectedGates.size(); i++) {
		mSelectedGates[i]->SetGraphicsInfo(pOut, mNewGatesCoordinates[i]);
	}

	for (int i = 0; i < mConnections.size(); i++) {
		mConnections[i]->UpdatePath(pOut);
	}

	pOut->ClearDrawingArea();
}

/* Destructor */
Move::~Move() {

}

/* Checks if the given area is valid for moving a component to it or not */
bool Move::IsValidArea(const GraphicsInfo& gfxInfo) {
	Output* pOut = mAppManager->GetOutput();
	Component* pComp;

	for (int x = gfxInfo.x1; x < gfxInfo.x2; x += UI.PinOffset) {
		for (int y = gfxInfo.y1; y < gfxInfo.y2; y += UI.PinOffset) {
			pComp = pOut->GetComponentAtPin(x, y);

			if (pComp != NULL && !pComp->IsSelected() && pComp->GetAddActionType() != ADD_CONNECTION) {
				return false;
			}
		}
	}

	return true;
}

/* Sets the component new coordinates if it goes out of borders */
bool Move::SetNewGateBorders(GraphicsInfo& GfxInfo) {
	int dx = 0, dy = 0;

	if (GfxInfo.x1 < 0)
		dx = -GfxInfo.x1;
	if (GfxInfo.y1 < UI.GateBarHeight + UI.ToolBarHeight)
		dy = UI.GateBarHeight + UI.ToolBarHeight - GfxInfo.y1;
	if (GfxInfo.x2 >= UI.Width)
		dx = UI.Width - GfxInfo.x2;
	if (GfxInfo.y2 >= UI.Height - UI.StatusBarHeight)
		dy = UI.Height - UI.StatusBarHeight - GfxInfo.y2;

	GfxInfo.x1 += dx;
	GfxInfo.y1 += dy;
	GfxInfo.x2 += dx;
	GfxInfo.y2 += dy;

	return (dx != 0 || dy != 0);
}

/* Calculates and returns the new coordinates of the gate */
GraphicsInfo Move::CalculateDimensions(Component* pComp, int dx, int dy) {
	GraphicsInfo coord = pComp->GetGraphicsInfo();

	int x1 = coord.x1 + dx;
	int y1 = coord.y1 + dy;
	int x2 = coord.x2 + dx;
	int y2 = coord.y2 + dy;

	normalizeCoordinates(x1, y1);
	x1 -= UI.PinMargin, y1 -= UI.PinMargin;

	normalizeCoordinates(x2, y2);
	x2 -= UI.PinMargin, y2 -= UI.PinMargin;

	return GraphicsInfo(x1, y1, x2, y2);
}

/* Draws the component in its current state: faded or invalid */
void Move::DrawComponent(Component* pComp, const GraphicsInfo& GfxInfo, bool Invalid) {
	Output* pOut = mAppManager->GetOutput();
	ActionType actType = pComp->GetAddActionType();
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