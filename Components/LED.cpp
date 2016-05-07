#include "LED.h"

/* Constructor */
LED::LED(Output* pOut, const GraphicsInfo& gfxInfo) : Gate(pOut, gfxInfo) {
	mLabel = "LED";
}

/* Returns the input pin number n (0-indexed) of the component */
InputPin* LED::GetInputPin(int n) {
	return &mInputPin;
}

/* Returns the output pin of the component */
OutputPin* LED::GetOutputPin() {
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

/* Saves the states of the component*/
void LED::Save(ofstream& file) {
	file << "LED " << mID << " " << mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType LED::GetAddActionType() const {
	return ActionType::ADD_LED;
}