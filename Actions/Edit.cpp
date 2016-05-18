#include "Edit.h"

/* Constructor */
Edit::Edit(ApplicationManager* pAppMan) : Action(pAppMan) {
	mComp = NULL;
	mAct = NULL;
}

/* Reads parameters required for action to execute */
bool Edit::ReadActionParameters() {
	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();

	pOut->PrintMsg("Please select a component to edit");
	pIn->GetPointClicked(mX, mY);
	pOut->ClearStatusBar();

	if (!pOut->IsDrawingArea(mY)) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	mComp = pOut->GetComponentAtPin(mX, mY);

	if (mComp == NULL) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	return true;
}

/* Executes action */
bool Edit::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}

	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();

	bool ret = false;

	mPrvLabel = mComp->GetLabel();
	mNewLabel = pIn->GetSrting(pOut, "Please enter a new label:", mPrvLabel);
	pOut->ClearStatusBar();

	mComp->SetLabel(mNewLabel);

	if (!mNewLabel.empty() && mNewLabel != mPrvLabel) {
		ret = true;
	}

	if (dynamic_cast<Connection*>(mComp) != NULL) {
		mAct = new AddConnection(mAppManager);

		if (mAct->Execute()) {
			mComp->Delete(pOut);
			pOut->ClearDrawingArea();
			ret = true;
		}
	}

	return ret;
}

/* Undo action */
void Edit::Undo() {
	mComp->SetLabel(mPrvLabel);

	if (mAct != NULL) {
		mAct->Undo();
		mComp->Restore(mAppManager->GetOutput());
	}
}

/* Redo action */
void Edit::Redo() {
	mComp->SetLabel(mNewLabel);

	if (mAct != NULL) {
		mAct->Redo();
		mComp->Delete(mAppManager->GetOutput());
		mAppManager->GetOutput()->ClearDrawingArea();
	}
}

/*Destructor*/
Edit::~Edit() {

}