#include "Copy.h"

/* Constructor */
Copy::Copy(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Copy::ReadActionParameters() {
	return true;
}

/* Executes action */
bool Copy::Execute() {
	int n = mAppManager->GetComponentsCount();
	Component** list = mAppManager->GetComponentList();

	for (int i = 0; i < n; i++) {
		list[i]->SetCopied(list[i]->IsSelected());
	}

	mAppManager->GetOutput()->PrintMsg("Copied");
	return false;	// To prevent adding this action to the stack
}

/* Undo action */
void Copy::Undo() {
	return;
}

/* Redo action */
void Copy::Redo() {
	return;
}

/* Destructor */
Copy::~Copy() {

}