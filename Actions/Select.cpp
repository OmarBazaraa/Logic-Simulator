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

		// Store the previous window
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

			pOut->UpdateBuffer();
		}

		mEndX = x, mEndY = y;
		if (mStartX > mEndX) swap(mStartX, mEndX);
		if (mStartY > mEndY) swap(mStartY, mEndY);

		// Redraw the initial window
		pOut->DrawImage(wind, minX, minY, maxX, maxY - minY);
		pOut->UpdateBuffer();
	}

	// Added the selected components to the set
	for (int x = mStartX; x <= mEndX; x += UI.PinOffset) {
		for (int y = mStartY; y <= mEndY; y += UI.PinOffset) {
			Component* pComp = pOut->GetComponentAtPin(x, y);

			if (pComp != NULL) {
				mSelectedComps.insert(pComp);
			}
		}
	}

	return true;
}

/* Executes action */
bool Select::Execute() {
	ReadActionParameters();

	Output* pOut = mAppManager->GetOutput();
	Input* pIn = mAppManager->GetInput();

	//char key = 0;
	//pIn->GetKeyPress(key);
	//if (key != 'z') {
	//	// Clear previous selection
	//	mAppManager->DeselectComponents();
	//}

	// Clear previous selection
	mAppManager->DeselectComponents();

	// Highlight selected components
	for (auto it = mSelectedComps.begin(); it != mSelectedComps.end(); it++) {
		(*it)->Select();
	}

	// Reflect some information about selected components to the screen
	int selectedCount = mAppManager->CountSelectedComponents();
	
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