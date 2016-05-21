#include "Edit.h"

/* Constructor */
Edit::Edit(ApplicationManager* pAppMan) : Action(pAppMan) {
	mNewDstPinIndex = 0;
	mPrvDstPinIndex = 0;
	mNewSrcPin = NULL;
	mPrvSrcPin = NULL;
	mNewDstPin = NULL;
	mPrvDstPin = NULL;
	mNewPath = NULL;
	mComp = NULL;
}

/* Reads parameters required for action to execute */
bool Edit::ReadActionParameters() {
	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();

	bool ret = false;

	pOut->PrintMsg("Please select a component to edit");
	pIn->GetPointClicked(mX, mY);
	pOut->ClearStatusBar();

	if (!pOut->IsDrawingArea(mX, mY)) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	mComp = pOut->GetComponentAtPin(mX, mY);

	if (mComp == NULL) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	// Edit label
	mPrvLabel = mComp->GetLabel();
	mNewLabel = pIn->GetSrting(pOut, "Please enter a new label:", mPrvLabel);
	pOut->ClearStatusBar();

	if (!mNewLabel.empty() && mNewLabel != mPrvLabel) {
		ret = true;
	}

	// Edit path if Connection
	Connection* connection = dynamic_cast<Connection*>(mComp);

	if (connection == NULL) {
		return ret;
	}

	mPrvSrcPin = connection->GetSourcePin();
	mPrvDstPin = connection->GetDestinationPin();
	mPrvDstPinIndex = connection->GetDestinationPinIndex();
	mPrvGfxInfo = connection->GetGraphicsInfo();
	mPrvPath = connection->GetPath();

	mPrvSrcPin->RemoveConnection(connection);
	mPrvDstPin->RemoveConnection(connection);

	pOut->PrintMsg("Select the new source pin");
	pIn->GetPointClicked(mNewGfxInfo.x1, mNewGfxInfo.y1);
	pOut->ClearStatusBar();

	if (!pOut->IsDrawingArea(mNewGfxInfo.x1, mNewGfxInfo.y1)) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		mPrvSrcPin->ConnectTo(connection);
		mPrvDstPin->ConnectTo(connection);
		return ret;
	}

	if (!DetectSourceComponent()) {
		pOut->PrintMsg("Invalid source pin. Operation was cancelled");
		mPrvSrcPin->ConnectTo(connection);
		mPrvDstPin->ConnectTo(connection);
		return ret;
	}

	pOut->PrintMsg("Select the new destination pin");
	pIn->GetPointClicked(mNewGfxInfo.x2, mNewGfxInfo.y2);
	pOut->ClearStatusBar();

	if (!pOut->IsDrawingArea(mNewGfxInfo.x2, mNewGfxInfo.y2)) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		mPrvSrcPin->ConnectTo(connection);
		mPrvDstPin->ConnectTo(connection);
		return ret;
	}

	if (!DetectDestinationComponent()) {
		pOut->PrintMsg("Invalid destination pin. Operation was cancelled");
		mPrvSrcPin->ConnectTo(connection);
		mPrvDstPin->ConnectTo(connection);
		return ret;
	}

	if (mNewSrcPin == mPrvSrcPin && mNewDstPin == mPrvDstPin && mNewDstPinIndex == mPrvDstPinIndex) {
		mPrvSrcPin->ConnectTo(connection);
		mPrvDstPin->ConnectTo(connection);
		return ret;
	}

	mNewPath = pOut->GetConnectionPath(mNewGfxInfo);

	if (mNewPath == NULL) {
		pOut->PrintMsg("There is no available path. Operation was cancelled");
		mPrvSrcPin->ConnectTo(connection);
		mPrvDstPin->ConnectTo(connection);
		return ret;
	}

	return true;
}

/* Executes action */
bool Edit::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}

	mComp->SetLabel(mNewLabel);

	if (mNewPath != NULL) {
		Connection* connection = (Connection*)mComp;
		connection->SetSourcePin(mNewSrcPin);
		connection->SetDestinationPin(mNewDstPin, mNewDstPinIndex);
		connection->SetPath(mAppManager->GetOutput(), mNewGfxInfo, *mNewPath);
		mAppManager->GetOutput()->ClearDrawingArea();
	}

	return true;
}

/* Undo action */
void Edit::Undo() {
	mComp->SetLabel(mPrvLabel);

	if (mNewPath != NULL) {
		Connection* connection = (Connection*)mComp;
		connection->SetSourcePin(mPrvSrcPin);
		connection->SetDestinationPin(mPrvDstPin, mPrvDstPinIndex);
		connection->SetPath(mAppManager->GetOutput(), mPrvGfxInfo, mPrvPath);
		mAppManager->GetOutput()->ClearDrawingArea();
	}
}

/* Redo action */
void Edit::Redo() {
	mComp->SetLabel(mNewLabel);

	if (mNewPath != NULL) {
		Connection* connection = (Connection*)mComp;
		connection->SetSourcePin(mNewSrcPin);
		connection->SetDestinationPin(mNewDstPin, mNewDstPinIndex);
		connection->SetPath(mAppManager->GetOutput(), mNewGfxInfo, *mNewPath);
		mAppManager->GetOutput()->ClearDrawingArea();
	}
}

/*Destructor*/
Edit::~Edit() {
	delete mNewPath;
}

/* Detects the source component of the connection */
bool Edit::DetectSourceComponent() {
	Component* comp = mAppManager->GetOutput()->GetComponentAtPin(mNewGfxInfo.x1, mNewGfxInfo.y1);

	if (comp == NULL) {
		return false;
	}
	else {
		Gate* gate;

		if (dynamic_cast<Gate*>(comp) != NULL)
			gate = (Gate*)comp;
		else
			gate = ((Connection*)comp)->GetSourcePin()->GetGate();

		gate->GetOutputPinCoordinates(mNewGfxInfo.x1, mNewGfxInfo.y1);
		mNewSrcPin = gate->GetOutputPin();

		if (mNewSrcPin == NULL || mNewSrcPin->IsFull()) {
			return false;
		}
	}

	return true;
}

/* Detects the destination component of the connection */
bool Edit::DetectDestinationComponent() {
	Component* comp = mAppManager->GetOutput()->GetComponentAtPin(mNewGfxInfo.x2, mNewGfxInfo.y2);

	if (comp == NULL || comp == mNewSrcPin->GetGate()) {
		return false;
	}
	else if (dynamic_cast<Gate*>(comp) != NULL) {
		Gate* gate = (Gate*)comp;
		mNewDstPinIndex = gate->GetInputPinIndex(mNewGfxInfo.x2, mNewGfxInfo.y2);
		gate->GetInputPinCoordinates(mNewGfxInfo.x2, mNewGfxInfo.y2, mNewDstPinIndex);
		mNewDstPin = gate->GetInputPin(mNewDstPinIndex);

		if (mNewDstPin == NULL || mNewDstPin->IsFull()) {
			return false;
		}

		return true;
	}

	return false;
}