#include "Move.h"

/* Constructor */
Move::Move(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Move::ReadActionParameters() {
	Output* pOut = mAppManager->GetOutput();
	Input* pIn = mAppManager->GetInput();

	pIn->GetLastPointClicked(mStartX, mStartY);
	normalizeCoordinates(mStartX, mStartY);

	Component* pComp = pOut->GetComponentAtPin(mStartX, mStartY);

	if (pComp != NULL && !pComp->IsSelected()) {
		mAppManager->SetSelectionOfComponents(false);
		pComp->SetSelected(true);
	}

	mSelectedGates = mAppManager->GetSelectedGates();
	mConnections = mAppManager->GetConnections();

	for (int i = 0; i < mSelectedGates.size(); i++) {
		mPrvGatesCoordinates.push_back(mSelectedGates[i]->GetGraphicsInfo());
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

				bool outOfBorders = AdjustGateCoordinates(newCoord);

				int x2 = (newCoord.x1 + newCoord.x2) / 2;
				int y2 = (newCoord.y1 + newCoord.y2) / 2;				

				pOut->DrawMoveLine(x1, y1, x2, y2);
				DrawGate(mSelectedGates[i], newCoord, pOut->IsEmptyArea(newCoord) && !outOfBorders);
			}

			prvX = x;
			prvY = y;
		}

		pOut->UpdateScreen();
	}
	
	// Redraw the initial window
	pOut->DrawImage(wind, 0, 0, UI.Width, UI.Height);
	pOut->UpdateScreen();

	// No changes in the positions
	if (dx == 0 && dy == 0) {
		return false;	
	}

	// Check for the validity of the coordinates
	for (int i = 0; i < mSelectedGates.size(); i++) {
		GraphicsInfo newCoord = CalculateDimensions(mSelectedGates[i], dx, dy);

		if (!pOut->IsEmptyArea(newCoord)) {
			return false;
		}
	}

	// Clear all connections' path to free up space for moving the gates
	for (int i = 0; i < mConnections.size(); i++) {
		pOut->ClearConnectionPins(mConnections[i]->GetPath());
	}

	// Clear all selected gate's from the grid
	for (int i = 0; i < mSelectedGates.size(); i++) {
		pOut->MarkPins(mSelectedGates[i]->GetGraphicsInfo(), PinType::EMPTY, NULL);
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
		pOut->MarkPins(mSelectedGates[i]->GetGraphicsInfo(), PinType::EMPTY, NULL);
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
		pOut->MarkPins(mSelectedGates[i]->GetGraphicsInfo(), PinType::EMPTY, NULL);
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

/* Adjusts gate's coordinates if it goes out of borders */
bool Move::AdjustGateCoordinates(GraphicsInfo& GfxInfo) {
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

/* Draws the gate in its current state: faded or invalid */
void Move::DrawGate(Component* pComp, const GraphicsInfo& GfxInfo, bool valid) {
	Output* pOut = mAppManager->GetOutput();
	ActionType actType = pComp->GetAddActionType();
	string dir;

	switch (actType)
	{
	case ADD_GATE_AND:
		dir = (valid ? "Images\\components\\faded\\and.png" : "Images\\components\\inactive\\and.png");
		break;
	case ADD_GATE_OR:
		dir = (valid ? "Images\\components\\faded\\or.png" : "Images\\components\\inactive\\or.png");
		break;
	case ADD_GATE_NOT:
		dir = (valid ? "Images\\components\\faded\\not.png" : "Images\\components\\inactive\\not.png");
		break;
	case ADD_GATE_NAND:
		dir = (valid ? "Images\\components\\faded\\nand.png" : "Images\\components\\inactive\\nand.png");
		break;
	case ADD_GATE_NOR:
		dir = (valid ? "Images\\components\\faded\\nor.png" : "Images\\components\\inactive\\nor.png");
		break;
	case ADD_GATE_XOR:
		dir = (valid ? "Images\\components\\faded\\xor.png" : "Images\\components\\inactive\\xor.png");
		break;
	case ADD_GATE_XNOR:
		dir = (valid ? "Images\\components\\faded\\xnor.png" : "Images\\components\\inactive\\xnor.png");
		break;
	case ADD_GATE_AND3:
		dir = (valid ? "Images\\components\\faded\\and3.png" : "Images\\components\\inactive\\and3.png");
		break;
	case ADD_GATE_NOR3:
		dir = (valid ? "Images\\components\\faded\\nor3.png" : "Images\\components\\inactive\\nor3.png");
		break;
	case ADD_GATE_XOR3:
		dir = (valid ? "Images\\components\\faded\\xor3.png" : "Images\\components\\inactive\\xor3.png");
		break;
	case ADD_GATE_BUFFER:
		dir = (valid ? "Images\\components\\faded\\buffer.png" : "Images\\components\\inactive\\buffer.png");
		break;
	case ADD_SWITCH:
		dir = (valid ? "Images\\components\\faded\\switch_off.png" : "Images\\components\\inactive\\switch_off.png");
		break;
	case ADD_LED:
		dir = (valid ? "Images\\components\\faded\\led_off.png" : "Images\\components\\inactive\\led_off.png");
		break;
	}

	pOut->DrawPNG(dir, GfxInfo.x1, GfxInfo.y1);
}