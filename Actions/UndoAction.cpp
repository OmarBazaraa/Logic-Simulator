#include "UndoAction.h"

/* Constructor */
UndoAction::UndoAction(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool UndoAction::ReadActionParameters() {
	return true;
}

/* Executes action */
bool UndoAction::Execute() {
	mAppManager->Undo();
	mAppManager->GetOutput()->ClearStatusBar();

	return false; 	// To prevent adding this action to the stack again
}

/* Undo action */
void UndoAction::Undo() {
	return;
}

/* Redo action */
void UndoAction::Redo() {
	return;
}

/* Destructor */
UndoAction::~UndoAction() {

}