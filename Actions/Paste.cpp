#include "Paste.h"

/* Constructor */
Paste::Paste(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Paste::ReadActionParameters() {
	return true;
}

bool Paste::Execute() {
	int n = mAppManager->GetComponentsCount();
	Component** list = mAppManager->GetComponentList();
	Action* pAct = NULL;

	for (int i = 0; i < n; i++) {
		if (list[i]->IsCopied()) {
			
			if (dynamic_cast<Gate*>(list[i])) {
				pAct = new AddGate(mAppManager, list[i]->GetAddActionType());
			}
			else {
				pAct = new AddConnection(mAppManager);
			}

			pAct->Execute();
			mPastedActions.push_back(pAct);
			mAppManager->UpdateInterface();
		}
	}

	if (mPastedActions.empty()) {
		return false;
	}

	return true;
}

/* Undo action */
void Paste::Undo() {
	for (int i = 0; i < (int)mPastedActions.size(); i++) {
		mPastedActions[i]->Undo();
	}
}

/* Redo action */
void Paste::Redo() {
	for (int i = 0; i < (int)mPastedActions.size(); i++) {
		mPastedActions[i]->Redo();
	}
}

/* Destructor */
Paste::~Paste() {
	for (int i = 0; i < (int)mPastedActions.size(); i++) {
		delete mPastedActions[i];
	}
}