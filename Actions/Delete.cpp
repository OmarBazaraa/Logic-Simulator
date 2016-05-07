#include "Delete.h"

/* Constructor */
Delete::Delete(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Delete::ReadActionParameters() {
	return true;
}

/* Executes action */
bool Delete::Execute() {
	int n = mAppManager->GetComponentsCount();
	Component** list = mAppManager->GetComponentList();
	Output* pOut = mAppManager->GetOutput();

	for (int i = 0; i < n; i++) {
		if (list[i]->IsSelected()) {
			list[i]->Delete(pOut);
			mDeletedComps.push_back(list[i]);
		}
	}

	if (mDeletedComps.empty()) {
		return false;
	}

	pOut->ClearDrawingArea();
	pOut->PrintMsg("Deleted items: " + to_string(mDeletedComps.size()));
	return true;
}

/* Undo action */
void Delete::Undo() {
	for (int i = 0; i < (int)mDeletedComps.size(); i++) {
		mDeletedComps[i]->Restore(mAppManager->GetOutput());
	}
}

/* Redo action */
void Delete::Redo() {
	for (int i = 0; i < (int)mDeletedComps.size(); i++) {
		mDeletedComps[i]->Delete(mAppManager->GetOutput());
	}

	mAppManager->GetOutput()->ClearDrawingArea();
}

/* Destructor */
Delete::~Delete() {

}