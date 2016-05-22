#include "LoadAction.h"

/* Constructor */
LoadAction::LoadAction(ApplicationManager* pAppMan) : Action(pAppMan) {
	mRead.open("Data.txt");
}

/* Reads parameters required for action to execute */
bool LoadAction::ReadActionParameters() {
	return true;
}

/* Executes action */
bool LoadAction::Execute() {
	Dialog *d = new Dialog("Loading old file will cause current file deletion!");

	if (d->GetUserClick() != YES) {
		delete d;
		return false;
	}

	mAppManager->FreeMemory();
	mAppManager->GetOutput()->ClearDrawingArea();
	mAppManager->Load(mRead);
	
	delete d;
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

}