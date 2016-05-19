#include "Select.h"

/* Constructor */
Select::Select(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Select::ReadActionParameters() {
	mAppManager->GetInput()->GetLastPointClicked(mX, mY);
	return true;
}

/* Executes action */
bool Select::Execute() {
	ReadActionParameters();

	int selectedCount = 0;
	int n = mAppManager->GetComponentsCount();
	Output* pOut = mAppManager->GetOutput();
	Component* pComp = pOut->GetComponentAtPin(mX, mY);
	Component** list = mAppManager->GetComponentList();

	image Window;
	pOut->StoreImage(Window, 0, 0, UI.Width, UI.Height);
	
	// Toggle the selection state of the selected component
	if (pComp != NULL) {
		pOut->WaitMouseClick(mX, mY);
		pComp->Select();
		for (int i = 0; i < n; i++) if (list[i]->IsSelected()) selectedCount++, pComp = list[i];
	}
	// Selecting empty area leads to deselecting all components
	else {
		for (int i = 0; i < n; i++) list[i]->SetSelected(false);
		int startX = mX, startY = mY, prvX = mX, prvY = mY;

		while (pOut->GetButtonState(LEFT_BUTTON, mX, mY) == BUTTON_DOWN) {
			if (mX != prvX || mY != prvY) {
				pOut->DrawImage(Window, 0, 0, UI.Width, UI.Height);
				pOut->SetPen(UI.SelectionColor, 2);
				pOut->DrawRectangle(startX, startY, mX, mY, FRAME);
				prvX = mX;
				prvY = mY;
			}
		}

		int sX = (mX < startX) ? mX : startX;
		int sY = (mY < startY) ? mY : startY;
		normalizeCoordinates(sX, sY);

		int eX = (mX > startX) ? mX : startX;
		int eY = (mY > startY) ? mY : startY;
		normalizeCoordinates(eX, eY);

		for (int x = sX; x < eX; x += UI.PinOffset) {
			for (int y = sY; y < eY; y += UI.PinOffset) {
				pComp = pOut->GetComponentAtPin(x, y);

				if (pComp != NULL) {
					pComp->SetSelected(true);
				}
			}
		}

		/*for (int i = 0; i < n; i++) {
			GraphicsInfo GfxInfo = list[i]->GetGraphicsInfo();
			if ((GfxInfo.x1 > min(mX, OldX) && GfxInfo.x1 < max(mX, OldX)) || (GfxInfo.x2 > min(mX, OldX) && GfxInfo.x2 < max(mX, OldX)) || (GfxInfo.x1 > min(mX, OldX) && GfxInfo.x2 < max(mX, OldX)) || ((GfxInfo.x2 > min(mX, OldX) && GfxInfo.x1 < max(mX, OldX)))) {
				if ((GfxInfo.y1 > min(mY, OldY) && GfxInfo.y1 < max(mY, OldY)) || (GfxInfo.y2 > min(mY, OldY) && GfxInfo.y2 < max(mY, OldY)) || (GfxInfo.y1 > min(mY, OldY) && GfxInfo.y2 < max(mY, OldY)) || (GfxInfo.y2 > min(mY, OldY) && GfxInfo.y1 < max(mY, OldY))) {
					list[i]->SetSelected(true);
					pComp = list[i];
					selectedCount++;
				}
			}
		}*/



		pOut->DrawImage(Window, 0, 0, UI.Width, UI.Height);
		//pOut->ClearDrawingArea();
		pOut->FlushMouseQueue();
	}

	// Reflect selected components to the screen
	if (selectedCount == 1) {
		pOut->PrintMsg("Component ID: " + to_string(pComp->GetID()) + ", Label: " + pComp->GetLabel());
	}
	else if (selectedCount > 1) {
		pOut->PrintMsg("Selected Components: " + to_string(selectedCount));
	}
	else {
		pOut->ClearStatusBar();
	}

	return false;	// To prevent adding this action to the stack
}

/* Undo action */
void Select::Undo() {
	return;
}

/* Redo action */
void Select::Redo() {
	return;
}

/* Destructor */
Select::~Select() {

}