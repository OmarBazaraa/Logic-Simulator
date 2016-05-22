#include "Connection.h"

/* Constructor */
Connection::Connection(Output* pOut, const GraphicsInfo& gfxInfo, const vector<GraphicsInfo>& path) {
	mLabel = "Connection";
	SetPath(pOut, gfxInfo, path);
	mSrcPin = NULL;
	mDstPin = NULL;
}

/* Sets the new path of the connection, needed in edit action */
void Connection::SetPath(Output* pOut, const GraphicsInfo& gfxInfo, const vector<GraphicsInfo>& path) {
	// Clear previous path
	pOut->ClearConnectionPins(mPath);
	
	// Update path
	mGfxInfo = gfxInfo;
	mPath = path;
	pOut->MarkConnectionPins(mPath, this);
}

/* Updates the path of the connection */
bool Connection::UpdatePath(Output* pOut) {
	// Clear previous path
	//pOut->ClearConnectionPins(mPath);

	// Update path
	mSrcPin->GetGate()->GetOutputPinCoordinates(mGfxInfo.x1, mGfxInfo.y1);
	mDstPin->GetGate()->GetInputPinCoordinates(mGfxInfo.x2, mGfxInfo.y2, mDstPinIndex);

	vector <GraphicsInfo>* Path = pOut->GetConnectionPath(mGfxInfo);
	if (Path != NULL) {
		mPath = *Path;
		pOut->MarkConnectionPins(mPath, this);
		return true;
	}
	return false;
}

/* Returns the path of the connection */
vector<GraphicsInfo> Connection::GetPath() const {
	return mPath;
}

/* Sets the source pin of the connection */
void Connection::SetSourcePin(Pin* pSrcPin) {
	if (mSrcPin != NULL) {
		mSrcPin->RemoveConnection(this);
	}

	mSrcPin = pSrcPin;
	pSrcPin->ConnectTo(this);
}

/* Returns the source pin of the connection */
Pin* Connection::GetSourcePin() const {
	return mSrcPin;
}

/* Sets the destination pin of the connection */
void Connection::SetDestinationPin(Pin* pDstPin, int index) {
	if (mDstPin != NULL) {
		mDstPin->RemoveConnection(this);
	}

	mDstPinIndex = index;
	mDstPin = pDstPin;
	pDstPin->ConnectTo(this);
}

/* Returns the destination pin of the connection */
Pin* Connection::GetDestinationPin() const {
	return mDstPin;
}

/* Returns the destination pin index of the connection */
int Connection::GetDestinationPinIndex() const {
	return mDstPinIndex;
}

/* Sets the status of the input pin number n (0-indexed) */
void Connection::SetInputPinStatus(int n, Status s) {
	mSrcPin->SetStatus(s);
}

/* Returns the status of the input pin number n (0-indexed), if Switch returns -1 */
int Connection::GetInputPinStatus(int n) const {
	return mSrcPin->GetStatus();
}

/* Returns the status of the output pin, if LED returns -1 */
int Connection::GetOutputPinStatus() const {
	return mDstPin->GetStatus();
}

/* Calculates the output according to the inputs */
void Connection::Operate() {
	mDstPin->SetStatus(mSrcPin->GetStatus());
}

/* Draws the connection */
void Connection::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawConnection(mPath, mSelected, mSrcPin->GetStatus() == Status::HIGH);
	}
}

/* Deletes the component */
void Connection::Delete(Output* pOut) {
	mSelected = false;
	mDeleted = true;
	mSrcPin->RemoveConnection(this);
	mDstPin->RemoveConnection(this);
	pOut->ClearConnectionPins(mPath);
}

/* Restores the component after being deleted */
void Connection::Restore(Output* pOut) {
	mDeleted = false;
	mSrcPin->ConnectTo(this);
	mDstPin->ConnectTo(this);
	pOut->MarkConnectionPins(mPath, this);
}

/* Saves the states of the component*/
void Connection::Save(ofstream& file) {
	file << mGfxInfo.x1 - UI.PinOffset << " " << mGfxInfo.y1 << " " << mGfxInfo.x2 + UI.PinOffset << " " << mGfxInfo.y2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType Connection::GetAddActionType() const {
	return ActionType::ADD_CONNECTION;
}