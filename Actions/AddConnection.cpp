#include "AddConnection.h"

/* Constructor */
AddConnection::AddConnection(ApplicationManager* pAppMan,int x1,int y1,int x2,int y2) : Action(pAppMan) {
	mPath = NULL;
	mSrcPin = NULL;
	mDstPin = NULL;
	mConnection = NULL;
	mGfxInfo.x1 = x1;
	mGfxInfo.x2 = x2;
	mGfxInfo.y1 = y1;
	mGfxInfo.y2 = y2;
}

/* Reads parameters required for action to execute */
bool AddConnection::ReadActionParameters() {
	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();
	
	if (mGfxInfo.x1 < 0) {
		pOut->PrintMsg("Connection: select the source pin");
		pIn->GetPointClicked(mGfxInfo.x1, mGfxInfo.y1);
		pOut->ClearStatusBar();

		if (!pOut->IsDrawingArea(mGfxInfo.x1, mGfxInfo.y1)) {
			pOut->PrintMsg("Invalid position. Operation was cancelled");
			return false;
		}
		
	}

	mInitial.x1 = mGfxInfo.x1;
	mInitial.y1 = mGfxInfo.y1; 
	
	if (!DetectSourceComponent()) {
			pOut->PrintMsg("Invalid source pin. Operation was cancelled");
			return false;
		}
	
	
		if (mGfxInfo.x2 < 0) {
			pOut->PrintMsg("Connection: select the destination pin");
			pIn->GetPointClicked(mGfxInfo.x2, mGfxInfo.y2);
			pOut->ClearStatusBar();

			if (!pOut->IsDrawingArea(mGfxInfo.x2, mGfxInfo.y2)) {
				pOut->PrintMsg("Invalid position. Operation was cancelled");
				return false;
			}
		}

		mInitial.x2 = mGfxInfo.x2;
		mInitial.y2 = mGfxInfo.y2;

		if (!DetectDestinationComponent()) {
			pOut->PrintMsg("Invalid destination pin. Operation was cancelled");
			return false;
		}
	

	mPath = pOut->GetConnectionPath(mGfxInfo);

	if (mPath == NULL) {
		pOut->PrintMsg("There is no available path. Operation was cancelled");
		return false;
	}

	return true;
}

/* Executes action */
bool AddConnection::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}
	
	mConnection = new Connection(mAppManager->GetOutput(), mGfxInfo, *mPath, mInitial);
	mConnection->SetSourcePin(mSrcPin);
	mConnection->SetDestinationPin(mDstPin, mDstPinIndex);
	mConnection->SetLabel(mLabel);
	mAppManager->AddComponent(mConnection);

	delete mPath;

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
	//delete mPath;
}

/* Detects the source component of the connection */
bool AddConnection::DetectSourceComponent() {
	Component* comp = mAppManager->GetOutput()->GetComponentAtPin(mGfxInfo.x1, mGfxInfo.y1);

	if (comp == NULL) {
		return false;
	}
	else {
		Gate* gate;

		if (dynamic_cast<Gate*>(comp) != NULL)
			gate = (Gate*)comp;
		else
			gate = ((Connection*)comp)->GetSourcePin()->GetGate();

		gate->GetOutputPinCoordinates(mGfxInfo.x1, mGfxInfo.y1);
		mSrcPin = gate->GetOutputPin();

		if (mSrcPin == NULL || mSrcPin->IsFull()) {
			return false;
		}
	}

	return true;
}

/* Detects the destination component of the connection */
bool AddConnection::DetectDestinationComponent() {
	Component* comp = mAppManager->GetOutput()->GetComponentAtPin(mGfxInfo.x2, mGfxInfo.y2);

	if (comp == NULL || comp == mSrcPin->GetGate()) {
		return false;
	}
	else if (dynamic_cast<Gate*>(comp) != NULL) {
		Gate* gate = (Gate*)comp;
		mDstPinIndex = gate->GetInputPinIndex(mGfxInfo.x2, mGfxInfo.y2);
		gate->GetInputPinCoordinates(mGfxInfo.x2, mGfxInfo.y2, mDstPinIndex);
		mDstPin = gate->GetInputPin(mDstPinIndex);

		if (mDstPin == NULL || mDstPin->IsFull()) {
			return false;
		}

		return true;
	}

	return false;
}