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

	Output* pOut = mAppManager->GetOutput();
	Component* pComp = pOut->GetComponentAtPin(mX, mY);
	Component** list = mAppManager->GetComponentList();

	int n = mAppManager->GetComponentsCount();
	int selectedCount = 0;
	int startX = mX, endX = mX;
	int startY = mY, endY = mY;

	// Multi-selection
	if (pComp == NULL) {
		image wind;
		pOut->StoreImage(wind, 0, 0, UI.Width, UI.Height);
		pOut->SetPen(UI.SelectionColor, 2);

		int minX = 0;
		int maxX = UI.Width;
		int minY = UI.ToolBarHeight + UI.GateBarHeight;
		int maxY = UI.Height - UI.StatusBarHeight;

		int x = startX, y = startY, prvX = x, prvY = y;

		while (pOut->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_DOWN) {
			if (x < minX || x > maxX) x = prvX;
			if (y < minY || y > maxY) y = prvY;

			if (x != prvX || y != prvY) {
				pOut->DrawImage(wind, 0, 0, UI.Width, UI.Height);
				pOut->DrawRectangle(startX, startY, x, y, FRAME);
				prvX = x;
				prvY = y;
			}
		}

		startX = (x < mX) ? x : mX, endX = (x > mX) ? x : mX;
		startY = (y < mY) ? y : mY, endY = (y > mY) ? y : mY;

		pOut->DrawImage(wind, 0, 0, UI.Width, UI.Height);
		pOut->FlushMouseQueue();
	}

	// Clear previous selection
	for (int i = 0; i < n; i++) list[i]->SetSelected(false);

	// Highlight selected components
	for (int x = startX; x <= endX; x += UI.PinOffset) {
		for (int y = startY; y <= endY; y += UI.PinOffset) {
			pComp = pOut->GetComponentAtPin(x, y);

			if (pComp != NULL) {
				pComp->Select();
			}
		}
	}

	// Count selected components
	for (int i = 0; i < n; i++) if (list[i]->IsSelected()) selectedCount++;

	// Reflect some information about selected components to the screen
	if (selectedCount > 0)
		pOut->PrintMsg(to_string(selectedCount) + " Selected Component(s)");
	else
		pOut->ClearStatusBar();

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