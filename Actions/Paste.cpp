#include "Paste.h"

/* Constructor */
Paste::Paste(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Paste::ReadActionParameters() {
	mComp = mAppManager->GetCopiedComp();
	return (mComp != NULL);
}

/* Executes action */
bool Paste::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}

	mAct = new AddGate(mAppManager, mComp->GetAddActionType());
	mAct->Execute();
	return true;
}

/* Undo action */
void Paste::Undo() {
	mAct->Undo();
}

/* Redo action */
void Paste::Redo() {
	mAct->Redo();
}

/* Destructor */
Paste::~Paste() {

}