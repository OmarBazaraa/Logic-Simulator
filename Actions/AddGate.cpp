#include "AddGate.h"

/* Constructor */
AddGate::AddGate(ApplicationManager* pAppMan, ActionType actType, int x, int y, string label) : Action(pAppMan) {
	mActType = actType;
	mGate = NULL;
	mX = x;
	mY = y;
	mLabel = label;
}

/* Reads parameters required for action to execute */
bool AddGate::ReadActionParameters() {
	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();

	if (mX < 0 && mY < 0) {
		pOut->PrintMsg(GetActionMsg());
		pIn->GetPointClicked(mX, mY);
		pOut->ClearStatusBar();

		if (!pOut->IsDrawingArea(mX, mY)) {
			pOut->PrintMsg("Invalid position. Operation was cancelled");
			return false;
		}
	}

	CalculateDimensions();

	if (!pOut->IsEmptyArea(mGfxInfo)) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	return true;
}

/* Executes action */
bool AddGate::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}

	CreateGate();
	mGate->SetLabel(mLabel);
	mAppManager->AddComponent(mGate);

	return true;
}

/* Undo action */
void AddGate::Undo() {
	mGate->Delete(mAppManager->GetOutput());
	mAppManager->GetOutput()->ClearDrawingArea();
}

/* Redo action */
void AddGate::Redo() {
	mGate->Restore(mAppManager->GetOutput());
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