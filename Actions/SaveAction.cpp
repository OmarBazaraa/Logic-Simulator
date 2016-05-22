#include "SaveAction.h"

/* Constructor */
SaveAction::SaveAction(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool SaveAction::ReadActionParameters() {
	return true;
}

/* Executes action */
bool SaveAction::Execute() {
	mWrite.open("Data.txt");
	mWrite.clear();
	mAppManager->Save(mWrite);
	mWrite << "-1\n";
	mAppManager->GetOutput()->PrintMsg("Saved");
	return false;
}

/* Undo action */
void SaveAction::Undo() {
	return;
}

/* Redo action */
void SaveAction::Redo() {
	return;
}

/* Destructor */
SaveAction::~SaveAction() {
	mWrite.close();
}