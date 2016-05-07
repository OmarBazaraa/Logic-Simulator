#include "AddConnection.h"

/* Constructor */
AddConnection::AddConnection(ApplicationManager* pAppMan) : Action(pAppMan) {
	mPath = NULL;
	mSrcPin = NULL;
	mDstPin = NULL;
	mConnection = NULL;
}

/* Reads parameters required for action to execute */
bool AddConnection::ReadActionParameters() {
	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();

	pOut->PrintMsg("Connection: select the source pin");
	pIn->GetPointClicked(mGfxInfo.x1, mGfxInfo.y1);
	pOut->ClearStatusBar();

	if (!pOut->IsDrawingArea(mGfxInfo.y1)) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	if (!DetectSourceComponent()) {
		pOut->PrintMsg("Invalid source pin. Operation was cancelled");
		return false;
	}

	pOut->PrintMsg("Connection: select the destination pin");
	pIn->GetPointClicked(mGfxInfo.x2, mGfxInfo.y2);
	pOut->ClearStatusBar();

	if (!pOut->IsDrawingArea(mGfxInfo.y2)) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	if (!DetectDestinationComponent()) {
		pOut->PrintMsg("Invalid destination pin. Operation was cancelled");
		return false;
	}

	mPath = pOut->GetConnectionPath(mGfxInfo);

	if (mPath == NULL) {
		pOut->PrintMsg("There is no available path. Operation was cancelled");
		return false;
	}

	//mLabel = pIn->GetSrting(pOut, "Please enter a label for the connection:");
	//pOut->ClearStatusBar();

	return true;
}

/* Executes action */
bool AddConnection::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}
		
	mConnection = new Connection(mAppManager->GetOutput(), mGfxInfo, *mPath);
	mConnection->SetSourcePin(mSrcPin);
	mConnection->SetDestinationPin(mDstPin);
	mConnection->SetLabel(mLabel);
	mAppManager->AddComponent(mConnection);

	return true;
}

/* Undo action */
void AddConnection::Undo() {
	mConnection->Delete(mAppManager->GetOutput());
	mAppManager->GetOutput()->ClearDrawingArea();
}

/* Redo action */
void AddConnection::Redo() {
	mConnection->Restore(mAppManager->GetOutput());
}

/* Destructor */
AddConnection::~AddConnection() {
	delete mPath;
}

/* Detects the source component of the connection */
bool AddConnection::DetectSourceComponent() {
	Component* comp = mAppManager->GetOutput()->GetComponentAtPin(mGfxInfo.x1, mGfxInfo.y1);

	if (comp == NULL) {
		return false;
	}
	else if (dynamic_cast<Gate*>(comp) != NULL) {
		Gate* gate = (Gate*)comp;
		gate->GetOutputPinCoordinates(mGfxInfo.x1, mGfxInfo.y1);
		mSrcPin = gate->GetOutputPin();

		if (mSrcPin == NULL || mSrcPin->IsFull()) {
			return false;
		}
	}
	else if (dynamic_cast<Connection*>(comp) != NULL) {
		Connection* connection = (Connection*)comp;
		mSrcPin = connection->GetSourcePin();

		if (mSrcPin == NULL || mSrcPin->IsFull()) {
			return false;
		}
	}

	return true;
}

/* Detects the destination component of the connection */
bool AddConnection::DetectDestinationComponent() {
	Component* comp = mAppManager->GetOutput()->GetComponentAtPin(mGfxInfo.x2, mGfxInfo.y2);
	Component* srcComp = mAppManager->GetOutput()->GetComponentAtPin(mGfxInfo.x1, mGfxInfo.y1);

	if (comp == NULL || comp == srcComp) {
		return false;
	}
	else if (dynamic_cast<Gate*>(comp) != NULL) {
		Gate* gate = (Gate*)comp;
		gate->GetInputPinCoordinates(mGfxInfo.x2, mGfxInfo.y2, mDstPinIndex);
		mDstPin = gate->GetInputPin(mDstPinIndex);

		if (mDstPin == NULL && mDstPin->IsFull()) {
			return false;
		}
	}

	return true;
}