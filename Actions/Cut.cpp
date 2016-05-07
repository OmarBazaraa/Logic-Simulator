#include "Cut.h"

/* Constructor */
Cut::Cut(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Cut::ReadActionParameters() {
	return true;
}

/* Executes action */
bool Cut::Execute() {
	int n = mAppManager->GetComponentsCount();
	Component** list = mAppManager->GetComponentList();
	Output* pOut = mAppManager->GetOutput();

	for (int i = 0; i < n; i++) {
		if (list[i]->IsSelected()) {
			list[i]->SetCopied(true);
			list[i]->Delete(pOut);
			mCutComps.push_back(list[i]);
		}
		else {
			list[i]->SetCopied(false);
		}
	}

	if (mCutComps.empty()) {
		return false;
	}

	pOut->ClearDrawingArea();
	pOut->PrintMsg("Cut");
	return true;
}

/* Undo action */
void Cut::Undo() {
	for (int i = 0; i < (int)mCutComps.size(); i++) {
		mCutComps[i]->Restore(mAppManager->GetOutput());
	}
}

/* Redo action */
void Cut::Redo() {
	for (int i = 0; i < (int)mCutComps.size(); i++) {
		mCutComps[i]->Delete(mAppManager->GetOutput());
	}

	mAppManager->GetOutput()->ClearDrawingArea();
}

/* Destructor */
Cut::~Cut() {

}