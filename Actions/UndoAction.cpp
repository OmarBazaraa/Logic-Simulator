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
	stack<Action*>* undoStack = mAppManager->GetUndoStack();
	stack<Action*>* redoStack = mAppManager->GetRedoStack();

	if (undoStack->empty()) {
		return false;
	}

	Action* lastAction = undoStack->top();
	lastAction->Undo();

	undoStack->pop();
	redoStack->push(lastAction);

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