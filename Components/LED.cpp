#include "LED.h"

/* Constructor */
LED::LED(Output* pOut, const GraphicsInfo& gfxInfo) : Gate(pOut, gfxInfo) {
	mLabel = "LED";
	mInputPin.SetGate(this);
}

/* Returns the input pin number n (0-indexed) of the component */
Pin* LED::GetInputPin(int n) {
	return &mInputPin;
}

/* Returns the output pin of the component */
Pin* LED::GetOutputPin() {
	return NULL;
}

/* Sets the status of the input pin number n (0-indexed) */
void LED::SetInputPinStatus(int n, Status s) {
	mInputPin.SetStatus(s);
}

/* Returns the status of the input pin number n (0-indexed) */
int LED::GetInputPinStatus(int n) const {
	return mInputPin.GetStatus();
}

/* Returns the status of the output pin */
int LED::GetOutputPinStatus() const {
	return -1;
}

/* Returns the input pin coordiantes of the gate according to its index */
void LED::GetInputPinCoordinates(int& x, int& y, int n) {
	x = mGfxInfo.x1 - UI.PinMargin;
	y = mGfxInfo.y2 - UI.PinMargin;
}

/* Calculates the output of the LED */
void LED::Operate() {
	return;
}

/* Draws the LED */
void LED::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawLED(mGfxInfo, mSelected, mInputPin.GetStatus() == Status::HIGH);
	}
}

/* Deletes the component */
void LED::Delete(Output* pOut) {
	mSelected = false;
	mDeleted = true;
	mInputPin.Delete(pOut);
	pOut->MarkPins(mGfxInfo, PinType::EMPTY, NULL);
}

/* Restores the component after being deleted */
void LED::Restore(Output* pOut) {
	mDeleted = false;
	mInputPin.Restore(pOut);
	pOut->MarkPins(mGfxInfo, PinType::GATE, this);
}

/* Saves the states of the component*/
void LED::Save(ofstream& file) {
	file << "LED " << mID << " " << mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType LED::GetAddActionType() const {
	return ActionType::ADD_LED;
}