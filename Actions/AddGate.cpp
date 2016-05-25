#include "AddGate.h"

/* Constructor */
AddGate::AddGate(ApplicationManager* pAppMan, ActionType actType, Data* pLoadedData) : Action(pAppMan) {
	mActType = actType;
	mGate = NULL;
	mIsLoaded = false;

	if (pLoadedData != NULL) {
		mIsLoaded = true;
		mX = pLoadedData->GfxInfo.x1;
		mY = pLoadedData->GfxInfo.y1;
		mLabel = pLoadedData->Label;
	}
}

/* Reads parameters required for action to execute */
bool AddGate::ReadActionParameters() {
	Output* pOut = mAppManager->GetOutput();
	Input* pIn = mAppManager->GetInput();

	if (!mIsLoaded) {
		mAppManager->SetSelectionOfComponents(false);
		mAppManager->UpdateInterface();

		pOut->PrintMsg(GetActionMsg());

		int prvX = mX;
		int prvY = mY;

		int minX = 0;
		int maxX = UI.Width;
		int minY = UI.ToolBarHeight + UI.GateBarHeight;
		int maxY = UI.Height - UI.StatusBarHeight;

		// Store the previous window
		image wind;
		pOut->StoreImage(wind, 0, 0, UI.Width, UI.Height);

		// Reading the mouse input from the user
		while (pIn->GetButtonState(LEFT_BUTTON, mX, mY) == BUTTON_UP) {
			normalizeCoordinates(mX, mY);

			if (mX < minX || mX > maxX) mX = prvX;
			if (mY < minY || mY > maxY) mY = prvY;

			if (mX != prvX || mY != prvY) {
				pOut->DrawImage(wind, 0, 0, UI.Width, UI.Height);

				CalculateDimensions();

				bool outOfBorders = AdjustGateCoordinates(mGfxInfo);

				DrawGate(pOut->IsEmptyArea(mGfxInfo) && !outOfBorders);

				prvX = mX;
				prvY = mY;
			}

			pOut->UpdateScreen();
		}

		// Wait until the user release the mouse click
		pIn->WaitMouseClick(prvX, prvY);

		// Redraw the initial window
		pOut->DrawImage(wind, 0, 0, UI.Width, UI.Height);
		pOut->UpdateScreen();
	}
	
	CalculateDimensions();

	if (!pOut->IsEmptyArea(mGfxInfo)) {
		if (!mIsLoaded) pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	return true;
}

/* Executes action */
bool AddGate::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}

	Output* pOut = mAppManager->GetOutput();

	if (!mIsLoaded) {
		mConnections = mAppManager->GetConnections();
	}

	// Clear all connections' path to free up space for the added gate
	for (int i = 0; i < (int)mConnections.size(); i++) {
		pOut->ClearConnectionPins(mConnections[i]->GetPath());
	}

	CreateGate();
	mGate->SetLabel(mLabel);

	// Update connections' path if available
	for (int i = 0; i < (int)mConnections.size(); i++) {
		if (!mConnections[i]->UpdatePath(pOut)) {
			Undo();
			delete mGate;
			if (!mIsLoaded) pOut->PrintMsg("Invalid position. Operation was cancelled");
			return false;
		}
	}

	mAppManager->AddComponent(mGate);

	pOut->ClearDrawingArea();
	pOut->ClearStatusBar();

	return true;
}

/* Undo action */
void AddGate::Undo() {
	Output* pOut = mAppManager->GetOutput();

	mGate->Delete(pOut);

	// Update the path of all connections
	for (int i = 0; i < (int)mConnections.size(); i++) pOut->ClearConnectionPins(mConnections[i]->GetPath());
	for (int i = 0; i < (int)mConnections.size(); i++) mConnections[i]->UpdatePath(pOut);

	pOut->ClearDrawingArea();
}

/* Redo action */
void AddGate::Redo() {
	Output* pOut = mAppManager->GetOutput();

	// Clear all connections' path to free up space for the added gate
	for (int i = 0; i < (int)mConnections.size(); i++) {
		pOut->ClearConnectionPins(mConnections[i]->GetPath());
	}

	mGate->Restore(pOut);

	// Update connections' path if available
	for (int i = 0; i < (int)mConnections.size(); i++) {
		mConnections[i]->UpdatePath(pOut);
	}

	pOut->ClearDrawingArea();
}

/* Destructor */
AddGate::~AddGate() {

}

/* Returns the message needed to guide the user */
string AddGate::GetActionMsg() {
	switch (mActType)
	{
	case ActionType::ADD_GATE_AND:
		return "2-Input AND Gate: Click to add the gate";
	case ActionType::ADD_GATE_OR:
		return "2-Input OR Gate: Click to add the gate";
	case ActionType::ADD_GATE_NOT:
		return "NOT Gate: Click to add the gate";
	case ActionType::ADD_GATE_NAND:
		return "2-Input NAND Gate: Click to add the gate";
	case ActionType::ADD_GATE_NOR:
		return "2-Input NOR Gate: Click to add the gate";
	case ActionType::ADD_GATE_XOR:
		return "2-Input XOR Gate: Click to add the gate";
	case ActionType::ADD_GATE_XNOR:
		return "2-Input XNOR Gate: Click to add the gate";
	case ActionType::ADD_GATE_AND3:
		return "3-Input AND Gate: Click to add the gate";
	case ActionType::ADD_GATE_NOR3:
		return "3-Input NOR Gate: Click to add the gate";
	case ActionType::ADD_GATE_XOR3:
		return "3-Input XOR Gate: Click to add the gate";
	case ActionType::ADD_GATE_BUFFER:
		return "Buffer Gate: Click to add the gate";
	case ActionType::ADD_SWITCH:
		return "Switch: Click to add";
	case ActionType::ADD_LED:
		return "LED: Click to add";
	default:
		return "";
	}
}

/* Calculates the rectangular bound of the gate */
void AddGate::CalculateDimensions() {
	int w, h;

	switch (mActType)
	{
	case ActionType::ADD_SWITCH:
		w = UI.SwitchWidth;
		h = UI.SwitchHeight;
		break;
	case ActionType::ADD_LED:
		w = UI.LedWidth;
		h = UI.LedHeight;
		break;
	default:
		w = UI.LogicGateWidth;
		h = UI.LogicGateHeight;
		break;
	}

	normalizeCoordinates(mX, mY);

	mGfxInfo.x1 = mX - w / 2;
	mGfxInfo.y1 = mY - h / 2;
	mGfxInfo.x2 = mX + w / 2;
	mGfxInfo.y2 = mY + h / 2;
}

/* Adjusts gate's coordinates if it goes out of borders */
bool AddGate::AdjustGateCoordinates(GraphicsInfo& GfxInfo) {
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

/* Draws the gate in its current state: faded or invalid */
void AddGate::DrawGate(bool valid) {
	Output* pOut = mAppManager->GetOutput();
	string dir;

	switch (mActType)
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

	pOut->DrawPNG(dir, mGfxInfo.x1, mGfxInfo.y1);
}

/* Creates the required gate */
void AddGate::CreateGate() {
	Output* pOut = mAppManager->GetOutput();

	switch (mActType)
	{
	case ActionType::ADD_GATE_AND:
		mGate = new AND(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_OR:
		mGate = new OR(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_NOT:
		mGate = new NOT(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_NAND:
		mGate = new NAND(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_NOR:
		mGate = new NOR(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_XOR:
		mGate = new XOR(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_XNOR:
		mGate = new XNOR(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_AND3:
		mGate = new AND3(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_NOR3:
		mGate = new NOR3(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_XOR3:
		mGate = new XOR3(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_GATE_BUFFER:
		mGate = new Buffer(pOut, mGfxInfo, GATES_FANOUT);
		break;
	case ActionType::ADD_SWITCH:
		mGate = new Switch(pOut, mGfxInfo, SWITCH_FANOUT);
		break;
	case ActionType::ADD_LED:
		mGate = new LED(pOut, mGfxInfo);
		break;
	}
}