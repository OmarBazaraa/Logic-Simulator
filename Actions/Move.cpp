#include "Move.h"

/* Constructor */
Move::Move(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Move::ReadActionParameters() {
	mAppManager->GetInput()->GetLastPointClicked(mX, mY);
	return true;
}

/* Executes action */
bool Move::Execute() {
	ReadActionParameters();

	bool StopMoveAction = false;
	int n = mAppManager->GetComponentsCount();
	int oldX = mX, oldY = mY, dx = 0, dy = 0;
	Output* pOut = mAppManager->GetOutput();
	window * pWind = pOut->getWindow();
	Component* pComp = pOut->GetComponentAtPin(mX, mY);
	Component** list = mAppManager->GetComponentList();

	image DrawingArea;
	pWind->StoreImage(DrawingArea, 0, 0, UI.Width, UI.Height);

	if (pComp != NULL && pComp->IsSelected()) {
		while (pWind->GetButtonState(RIGHT_BUTTON, mX, mY) == BUTTON_DOWN) {
			dx = mX - oldX, dy = mY - oldY;
			pWind->DrawImage(DrawingArea, 0, 0, UI.Width, UI.Height);
			for (int i = 0; i < n; i++) {
				if (list[i]->IsSelected()) {
					GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
					int x = (mGfx.x1 + mGfx.x2) / 2;
					int y = (mGfx.y1 + mGfx.y2) / 2;
					pWind->SetBrush(WHITE);
					pWind->DrawLine(x, y, x + dx, y + dy);
				}
			}
		}
		pWind->DrawImage(DrawingArea, 0, 0, UI.Width, UI.Height);
		for (int i = 0; i < n; i++) {
			if (list[i]->IsSelected()) {
				GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
				if (!ValidCoordinates((mGfx.x1 + mGfx.x2) / 2 + dx, (mGfx.y1 + mGfx.y2) / 2 + dy,list[i])) {
					StopMoveAction = true;
				}
			}
		}
		if (!StopMoveAction) {
			for (int i = 0; i < n; i++) {
				Connection* ptr = dynamic_cast <Connection *> (list[i]);
				if (list[i]->IsSelected() && ptr != NULL) {
					int w, h;
					GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
					GraphicsInfo NewGfx = CalculateDimensions(list[i], (mGfx.x1 + mGfx.x2) / 2 + dx, (mGfx.y1 + mGfx.y2) / 2 + dy, w, h);
					vector <GraphicsInfo>* Path = pOut->GetConnectionPath(NewGfx);
					if (Path != NULL)
						ptr->SetPath(pOut, NewGfx, *Path);
				}
			}
			for (int i = 0; i < n; i++) {
				if (list[i]->IsSelected()) {
					int w, h;
					GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
					GraphicsInfo NewGfx = CalculateDimensions(list[i], (mGfx.x1 + mGfx.x2) / 2 + dx, (mGfx.y1 + mGfx.y2) / 2 + dy, w, h);
					if (dynamic_cast <Connection *> (list[i])) {
						continue;
					}
					else {
						dynamic_cast <Gate *> (list[i])->SetGraphicsInfo(pOut, NewGfx);
					}
				}
			}
		}
	}
	else {
		int x, y;
		pWind->WaitMouseClick(x, y);
	}
	pOut->ClearDrawingArea();
	return false;	// To prevent adding this action to the stack
}


bool Move::ValidCoordinates(int x, int y,Component* Comp) {
	ActionType actType = Comp->GetAddActionType();
	Output* pOut = mAppManager->GetOutput();
	GraphicsInfo mGfx = Comp->GetGraphicsInfo();
	int w, h;
	GraphicsInfo NewGfx = CalculateDimensions(Comp, x, y, w, h);
	if (w == h && w == -1) {
		if (pOut->GetConnectionPath(NewGfx) != NULL)
			return true;
		return false;
	}
	if (min(NewGfx.y1,NewGfx.y2) > UI.GateBarHeight + UI.ToolBarHeight  && max(NewGfx.y1,NewGfx.y2) < UI.Height - UI.StatusBarHeight && min(NewGfx.x1,NewGfx.x2) > 0 && max(NewGfx.x1, NewGfx.x2) < UI.Width && pOut->IsEmptyArea(NewGfx))
		return true;
	return false;
}

GraphicsInfo Move::CalculateDimensions(Component* Comp, int x, int y, int & w, int & h) {
	GraphicsInfo mGfx = Comp->GetGraphicsInfo();
	ActionType actType = Comp->GetAddActionType();
	Output* pOut = mAppManager->GetOutput();

	switch (actType)
	{
	case ActionType::ADD_GATE_AND:
		w = UI.PinOffset * 3; //UI.AndGateWidth;
		h = UI.PinOffset * 3; //UI.AndGateHeight;
		break;
	case ActionType::ADD_GATE_OR:
		w = UI.OrGateWidth;
		h = UI.OrGateHeight;
		break;
	case ActionType::ADD_GATE_NOT:
		w = UI.NotGateWidth;
		h = UI.NotGateHeight;
		break;
	case ActionType::ADD_GATE_NAND:
		w = UI.NandGateWidth;
		h = UI.NandGateHeight;
		break;
	case ActionType::ADD_GATE_NOR:
		w = UI.NorGateWidth;
		h = UI.NorGateHeight;
		break;
	case ActionType::ADD_GATE_XOR:
		w = UI.XorGateWidth;
		h = UI.XorGateHeight;
		break;
	case ActionType::ADD_GATE_XNOR:
		w = UI.XnorGateWidth;
		h = UI.XnorGateHeight;
		break;
	case ActionType::ADD_GATE_AND3:
		w = UI.And3GateWidth;
		h = UI.And3GateHeight;
		break;
	case ActionType::ADD_GATE_NOR3:
		w = UI.Nor3GateWidth;
		h = UI.Nor3GateHeight;
		break;
	case ActionType::ADD_GATE_XOR3:
		w = UI.Xor3GateWidth;
		h = UI.Xor3GateHeight;
		break;
	case ActionType::ADD_GATE_BUFFER:
		w = UI.BufferGateWidth;
		h = UI.BufferGateHeight;
		break;
	case ActionType::ADD_SWITCH:
		w = UI.SwitchWidth;
		h = UI.SwitchHeight;
		break;
	case ActionType::ADD_LED:
		w = UI.LedWidth;
		h = UI.LedHeight;
		break;
	case ActionType::ADD_CONNECTION:
		w = -1;
		h = -1;
		break;
	default:
		break;
	}
	if (w == h && w == -1) {
		int Oldx = (mGfx.x1 + mGfx.x2) / 2;
		int Oldy = (mGfx.y1 + mGfx.y2) / 2;
		int dx = x - Oldx, dy = y - Oldy;
		GraphicsInfo NewGfx(mGfx.x1 + dx, mGfx.y1 + dy, mGfx.x2 + dx, mGfx.y2 + dy);
		return NewGfx;
	}
	int x1 = x - w / 2, y1 = y - h / 2;
	int x2 = x + w / 2, y2 = y + h / 2;
	GraphicsInfo NewGfx(x1, y1, x2, y2);
	return NewGfx;
}


/* Undo action */
void Move::Undo() {
	return;
}

/* Redo action */
void Move::Redo() {
	return;
}

/* Destructor */
Move::~Move() {

}