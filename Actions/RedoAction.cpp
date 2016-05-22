#include "RedoAction.h"

/* Constructor */
RedoAction::RedoAction(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool RedoAction::ReadActionParameters() {
	return true;
}

/* Executes action */
bool RedoAction::Execute() {
	mAppManager->Redo();
	mAppManager->GetOutput()->ClearStatusBar();

	return false;	// To prevent adding this action to the stack again
}

/* Undo action */
void RedoAction::Undo() {
	return;
}

/* Redo action */
void RedoAction::Redo() {
	return;
}

/* Destructor */
RedoAction::~RedoAction() {

}