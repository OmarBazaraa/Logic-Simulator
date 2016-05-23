#include "LoadAction.h"

/* Constructor */
LoadAction::LoadAction(ApplicationManager* pAppMan) : Action(pAppMan) {
	
}

/* Reads parameters required for action to execute */
bool LoadAction::ReadActionParameters() {
	Dialog dialog("Loading old file will cause current file deletion!",Type_B);

	if (dialog.GetUserClick() != DialogBoxButton::OK) {
		return false;
	}

	mRead.open("Data.txt");
	return true;
}

/* Executes action */
bool LoadAction::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}

	mAppManager->ReleaseMemory();
	mAppManager->GetOutput()->ClearDrawingArea();
	mAppManager->Load(mRead);
	mAppManager->GetOutput()->PrintMsg("Loaded");
	return false;
}


/* Undo action */
void LoadAction::Undo() {
	return;
}

/* Redo action */
void LoadAction::Redo() {
	return;
}

/* Destructor */
LoadAction::~LoadAction() {
	mRead.close();
}