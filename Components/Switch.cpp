#include "Switch.h"

/* Constructor */
Switch::Switch(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : Gate(pOut, gfxInfo), mOutputPin(fanOut) {
	mLabel = "Switch";
	mOutputPin.SetGate(this);
}

/* Returns the input pin number n (0-indexed) of the component */
Pin* Switch::GetInputPin(int n) {
	return NULL;
}

/* Returns the output pin of the component */
Pin* Switch::GetOutputPin() {
	return &mOutputPin;
}

/* Sets the status of the input pin number n (0-indexed) */
void Switch::SetInputPinStatus(int n, Status s) {

}

/* Returns the status of the input pin number n (0-indexed) */
int Switch::GetInputPinStatus(int n) const {
	return -1;
}

/* Returns the status of the output pin */
int Switch::GetOutputPinStatus() const {
	return mOutputPin.GetStatus();
}

/* Calculates the output of the Switch gate */
void Switch::Operate() {
	mOutputPin.SetStatus(mOutputPin.GetStatus() == HIGH ? LOW : HIGH);
}

/* Draws the Switch gate */
void Switch::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawSwitch(mGfxInfo, mSelected, mOutputPin.GetStatus() == Status::HIGH);
	}
}

/* Selects the component */
void Switch::Select() {
	if (UI.AppMode == Mode::DESIGN) {
		mSelected = !mSelected;
	}
	else {
		Refresh();
	}
}

/* Deletes the component */
void Switch::Delete(Output* pOut) {
	mSelected = false;
	mDeleted = true;
	mOutputPin.Delete(pOut);
	pOut->MarkPins(mGfxInfo, PinType::EMPTY, NULL);
}

/* Restores the component after being deleted */
void Switch::Restore(Output* pOut) {
	mDeleted = false;
	mOutputPin.Restore(pOut);
	pOut->MarkPins(mGfxInfo, PinType::GATE, this);
}

/* Simulates due to change in pin status */
void  Switch::Refresh() {
	queue<Component*> q;
	q.push(this);
	while (!q.empty()) {
		q.front()->Operate();
		if (dynamic_cast<Connection*>(q.front()))
			q.push(((Connection*)q.front())->GetDestinationPin()->GetGate());
		else if (!dynamic_cast<LED*>(q.front()))
			for (int i = 0; i < ((Gate*)q.front())->GetOutputPin()->GetConnectionsCount(); i++)
				q.push(((Gate*)q.front())->GetOutputPin()->GetConnection(i));
		q.pop();
	}
}

/* Saves the states of the component*/
void Switch::Save(ofstream& file) {
	file << "SWITCH " << mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType Switch::GetAddActionType() const {
	return ActionType::ADD_SWITCH;
}