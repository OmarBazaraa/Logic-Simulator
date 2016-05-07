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
	stack<Action*>* redoStack = mAppManager->GetRedoStack();
	stack<Action*>* undoStack = mAppManager->GetUndoStack();
	
	if (redoStack->empty()) {
		return false;
	}

	Action* lastAction = redoStack->top();
	lastAction->Redo();

	redoStack->pop();
	undoStack->push(lastAction);

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