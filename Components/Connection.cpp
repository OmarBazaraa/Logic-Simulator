#include "Connection.h"

/* Constructor */
Connection::Connection(Output* pOut, const GraphicsInfo& gfxInfo, const vector<GraphicsInfo>& path) {
	SetPath(pOut, gfxInfo, path);
	mLabel = "Connection";
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

/* Returns the path of the connection */
vector<GraphicsInfo> Connection::GetPath() const {
	return mPath;
}

/* Sets the source pin of the connection */
void Connection::SetSourcePin(Pin* pSrcPin) {
	mSrcPin = pSrcPin;
	pSrcPin->ConnectTo(this);
}

/* Returns the source pin of the connection */
Pin* Connection::GetSourcePin() const {
	return mSrcPin;
}

/* Sets the destination pin of the connection */
void Connection::SetDestinationPin(Pin* pDstPin) {
	mDstPin = pDstPin;
	pDstPin->ConnectTo(this);
}

/* Returns the destination pin of the connection */
Pin* Connection::GetDestinationPin() const {
	return mDstPin;
}

/* Calculates the output according to the inputs */
void Connection::Operate() {
	mDstPin->SetStatus(mSrcPin->GetStatus());
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

/* Draws the connection */
void Connection::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawConnection(mPath, mSelected); //mSrcPin->GetStatus() == Status::HIGH
	}
}

/* Deletes the component */
void Connection::Delete(Output* pOut) {
	mSelected = false;
	mDeleted = true;
	pOut->ClearConnectionPins(mPath);
}

/* Restores the component after being deleted */
void Connection::Restore(Output* pOut) {
	mDeleted = false;
	pOut->MarkConnectionPins(mPath, this);
}

/* Saves the states of the component*/
void Connection::Save(ofstream& file) {

}

/* Returns the Add-ActionType of the component */
ActionType Connection::GetAddActionType() const {
	return ActionType::ADD_CONNECTION;
}