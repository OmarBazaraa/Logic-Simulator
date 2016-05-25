#include "Copy.h"

/* Constructor */
Copy::Copy(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Copy::ReadActionParameters() {
	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();

	mAppManager->DeselectComponents();
	mAppManager->UpdateInterface();

	pOut->PrintMsg("Please select a component to copy");
	pIn->WaitMouseClick(mX, mY);
	pOut->ClearStatusBar();

	if (!pOut->IsDrawingArea(mX, mY)) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	mComp = pOut->GetComponentAtPin(mX, mY);

	if (mComp == NULL) {
		pOut->PrintMsg("No component was selected. Operation was cancelled");
		return false;
	}
	else if (dynamic_cast<Connection*>(mComp) != NULL) {
		pOut->PrintMsg("Cannot copy a connection. Operation was cancelled");
		return false;
	}

	return true;
}

/* Executes action */
bool Copy::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}

	mAppManager->SetCopiedComp(mComp);
	mAppManager->GetOutput()->PrintMsg("Copied");
	return false;	// To prevent adding CopyAction to the stack
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