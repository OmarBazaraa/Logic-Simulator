#include "Select.h"

/* Constructor */
Select::Select(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Select::ReadActionParameters() {
	Output* pOut = mAppManager->GetOutput();
	Input* pIn = mAppManager->GetInput();

	pIn->GetLastPointClicked(mStartX, mStartY);
	mEndX = mStartX;
	mEndY = mStartY;

	// Multi-selection
	if (pOut->GetComponentAtPin(mStartX, mStartY) == NULL) {
		int x = mStartX, prvX = x;
		int y = mStartY, prvY = y;

		int minX = 0;
		int maxX = UI.Width;
		int minY = UI.ToolBarHeight + UI.GateBarHeight;
		int maxY = UI.Height - UI.StatusBarHeight;

		image wind;
		pOut->StoreImage(wind, minX, minY, maxX, maxY - minY);

		while (pIn->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_DOWN) {
			if (x < minX || x > maxX) x = prvX;
			if (y < minY || y > maxY) y = prvY;

			if (x != prvX || y != prvY) {
				pOut->DrawImage(wind, minX, minY, maxX, maxY - minY);
				pOut->DrawSelectionRectangle(mStartX, mStartY, x, y);
				prvX = x;
				prvY = y;
			}
		}

		mEndX = x, mEndY = y;
		if (mStartX > mEndX) swap(mStartX, mEndX);
		if (mStartY > mEndY) swap(mStartY, mEndY);

		pOut->DrawImage(wind, minX, minY, maxX, maxY - minY);
	}

	return true;
}

/* Executes action */
bool Select::Execute() {
	ReadActionParameters();

	Output* pOut = mAppManager->GetOutput();
	Component** list = mAppManager->GetComponentList();

	int n = mAppManager->GetComponentsCount();
	int selectedCount = 0;

	// Clear previous selection
	for (int i = 0; i < n; i++) list[i]->SetSelected(false);

	// Highlight selected components
	for (int x = mStartX; x <= mEndX; x += UI.PinOffset) {
		for (int y = mStartY; y <= mEndY; y += UI.PinOffset) {
			Component* pComp = pOut->GetComponentAtPin(x, y);

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