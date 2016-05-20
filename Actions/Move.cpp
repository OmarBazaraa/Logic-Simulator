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
	Component* pComp = pOut->GetComponentAtPin(mX, mY);
	Component** list = mAppManager->GetComponentList();

	if (pComp != NULL && !pComp->IsSelected()) {
		for (int i = 0; i < n; i++)	list[i]->SetSelected(false);
		pComp->SetSelected(true);
	}

	mAppManager->UpdateInterface();
	image DrawingArea;
	pOut->StoreImage(DrawingArea, 0, 0, UI.Width, UI.Height);

	if (pComp != NULL && pComp->IsSelected()) {
		int prvX = mX, prvY = mY;
		while (pOut->GetButtonState(LEFT_BUTTON, mX, mY) == BUTTON_DOWN) {
			dx = mX - oldX, dy = mY - oldY;
			if (prvX != mX || prvY != mY) {
				pOut->DrawImage(DrawingArea, 0, 0, UI.Width, UI.Height);
				for (int i = 0; i < n; i++) {
					if (list[i]->IsSelected()) {
						GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
						int x = (mGfx.x1 + mGfx.x2) / 2;
						int y = (mGfx.y1 + mGfx.y2) / 2;
						pOut->SetPen(WHITE, 1);
						pOut->DrawLine(x, y, x + dx, y + dy);
					}
				}
				prvX = mX;
				prvY = mY;
			}
		}
		pOut->DrawImage(DrawingArea, 0, 0, UI.Width, UI.Height);
		for (int i = 0; i < n; i++) {
			if (list[i]->IsSelected()) {
				GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
				if (!ValidCoordinates(dx, dy,list[i])) {
					StopMoveAction = true;
				}
			}
		}
		if (!StopMoveAction) {
			for (int i = 0; i < n; i++) {
				if (list[i]->IsSelected()) {
					GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
					GraphicsInfo NewGfx = CalculateDimensions(list[i], dx, dy);
					if (list[i]->GetAddActionType() != ActionType::ADD_CONNECTION) {
						dynamic_cast <Gate *> (list[i])->SetGraphicsInfo(pOut, NewGfx);
					}
				}
			}
			for (int i = 0; i < n; i++) {
				if (list[i]->IsSelected() && list[i]->GetAddActionType() == ActionType::ADD_CONNECTION) {
					Connection* ptr = dynamic_cast <Connection *> (list[i]);
					GraphicsInfo mGfx = list[i]->GetGraphicsInfo();
					GraphicsInfo NewGfx = CalculateDimensions(list[i], dx, dy);
					vector <GraphicsInfo>* Path = pOut->GetConnectionPath(NewGfx);
					if (Path != NULL)
						ptr->SetPath(pOut, NewGfx, *Path);
				}
			}
		}
	}
	else {
		int x, y;
		pOut->WaitMouseClick(x, y);
	}
	pOut->ClearDrawingArea();
	pOut->ClearStatusBar();
	pOut->FlushMouseQueue();
	return false;	// To prevent adding this action to the stack
}

bool Move::ValidCoordinates(int dx, int dy,Component* Comp) {
	ActionType actType = Comp->GetAddActionType();
	Output* pOut = mAppManager->GetOutput();
	GraphicsInfo mGfx = Comp->GetGraphicsInfo();
	GraphicsInfo NewGfx = CalculateDimensions(Comp, dx, dy);
	if (Comp->GetAddActionType() == ActionType::ADD_CONNECTION) {
		if (pOut->GetConnectionPath(NewGfx) != NULL)
			return true;
		return false;
	}
	if (min(NewGfx.y1,NewGfx.y2) > UI.GateBarHeight + UI.ToolBarHeight  && max(NewGfx.y1,NewGfx.y2) < UI.Height - UI.StatusBarHeight && min(NewGfx.x1,NewGfx.x2) > 0 && max(NewGfx.x1, NewGfx.x2) < UI.Width && ValidArea(NewGfx))
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
	if (Comp->GetAddActionType() != ActionType::ADD_CONNECTION) {
		normalizeCoordinates(NewX1, NewY1);
		normalizeCoordinates(NewX2, NewY2);
		NewX1 -= UI.PinMargin;	NewY1 -= UI.PinMargin;
		NewX2 -= UI.PinMargin;	NewY2 -= UI.PinMargin;
	}
	GraphicsInfo NewGfx(NewX1, NewY1, NewX2, NewY2);
	return NewGfx;
}

bool Move::ValidArea(GraphicsInfo & GfxInfo) {
	Output* pOut = mAppManager->GetOutput();
	for (int x = GfxInfo.x1; x < GfxInfo.x2; x++) {
		for (int y = GfxInfo.y1; y < GfxInfo.y2; y++) {
			Component* pComp = pOut->GetComponentAtPin(x, y);
			if (pComp != NULL && !pComp->IsSelected())
				return false;
		}
	}
	return true;
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