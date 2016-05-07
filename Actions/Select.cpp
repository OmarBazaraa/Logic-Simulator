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
	
	// Toggle the selection state of the selected component
	if (pComp != NULL) {
		pComp->Select();
		for (int i = 0; i < n; i++) if (list[i]->IsSelected()) selectedCount++, pComp = list[i];
	}
	// Selecting empty area leads to deselecting all components
	else {
		for (int i = 0; i < n; i++) list[i]->SetSelected(false);
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