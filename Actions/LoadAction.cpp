#include "LoadAction.h"

/* Constructor */
LoadAction::LoadAction(ApplicationManager* pAppMan) : Action(pAppMan) {
	
}

/* Reads parameters required for action to execute */
bool LoadAction::ReadActionParameters() {
	mRead.open("Data.txt");

	if (!mRead.is_open()) {
		return false;
	}

	Dialog dialog("Any unsaved data will be deleted. Continue?",Type_B);

	if (dialog.GetUserClick() != DialogBoxButton::OK) {
		return false;
	}

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