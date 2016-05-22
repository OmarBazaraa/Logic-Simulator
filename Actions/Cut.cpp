#include "Cut.h"

/* Constructor */
Cut::Cut(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Cut::ReadActionParameters() {
	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();

	pOut->PrintMsg("Please select a component to cut");
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
	mAppManager->SetCopiedComp(mComp);
	mComp->Delete(pOut);
	pOut->ClearDrawingArea();
	pOut->PrintMsg("Cut");
	return true;
}

/* Undo action */
void Cut::Undo() {
	mComp->Restore(mAppManager->GetOutput());
}

/* Redo action */
void Cut::Redo() {
	mComp->Delete(mAppManager->GetOutput());
	mAppManager->GetOutput()->ClearDrawingArea();
}

/* Destructor */
Cut::~Cut() {

}