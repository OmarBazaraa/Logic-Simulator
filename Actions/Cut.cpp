#include "Cut.h"

/* Constructor */
Cut::Cut(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Cut::ReadActionParameters() {
	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();

	mAppManager->SetSelectionOfComponents(false);
	mAppManager->UpdateInterface();

	pOut->PrintMsg("Please select a component to cut");
	pIn->WaitMouseClick(mX, mY);
	pOut->ClearStatusBar();

	mComp = pOut->GetComponentAtPin(mX, mY);

	if (mComp == NULL) {
		pOut->PrintMsg("No component was selected. Operation was cancelled");
		return false;
	}
	else if (dynamic_cast<Connection*>(mComp) != NULL) {
		pOut->PrintMsg("Cannot cut a connection. Operation was cancelled");
		return false;
	}

	return true;
}

/* Executes action */
bool Cut::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}

	Output* pOut = mAppManager->GetOutput();

	// Set copied
	mAppManager->SetCopiedComp(mComp);

	// Delete
	mComp->SetSelected(true);
	mDeleteAct = new Delete(mAppManager);
	mDeleteAct->Execute();

	pOut->PrintMsg("Cut");
	return true;
}

/* Undo action */
void Cut::Undo() {
	mDeleteAct->Undo();
}

/* Redo action */
void Cut::Redo() {
	mDeleteAct->Redo();
}

/* Destructor */
Cut::~Cut() {
	delete mDeleteAct;
}