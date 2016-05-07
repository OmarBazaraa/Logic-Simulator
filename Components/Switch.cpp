#include "Switch.h"

/* Constructor */
Switch::Switch(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : Gate(pOut, gfxInfo), mOutputPin(fanOut) {
	mLabel = "Switch";
}

/* Returns the input pin number n (0-indexed) of the component */
InputPin* Switch::GetInputPin(int n) {
	return NULL;
}

/* Returns the output pin of the component */
OutputPin* Switch::GetOutputPin() {
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
	return;
}

/* Draws the Switch gate */
void Switch::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawSwitch(mGfxInfo, mSelected);
	}
}

/* Selects the component */
void Switch::Select() {
	if (UI.AppMode == Mode::DESIGN) {
		mSelected = !mSelected;
	}
	else {
		bool out = (mOutputPin.GetStatus() == Status::HIGH);
		mOutputPin.SetStatus(out ? Status::LOW : Status::HIGH);
	}
}

/* Saves the states of the component*/
void Switch::Save(ofstream& file) {

}

/* Loads the states of the component */
void Switch::Load() {

}

/* Returns the Add-ActionType of the component */
ActionType Switch::GetAddActionType() const {
	return ActionType::ADD_SWITCH;
}