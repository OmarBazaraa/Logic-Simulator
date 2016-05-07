#include "XOR3.h"

/* Constructor */
XOR3::XOR3(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : LogicGate(pOut, gfxInfo, 3, fanOut) {
	mLabel = "XOR3";
}

/* Calculates the output of the XOR3 gate */
void XOR3::Operate() {
	bool out = 0;

	for (int i = 0; i < mInputsCount; i++) {
		out = out ^ (mInputPins[i].GetStatus() == Status::HIGH ? 1 : 0);
	}

	mOutputPin.SetStatus(out ? Status::HIGH : Status::LOW);
}

/* Draws the XOR3 gate */
void XOR3::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawXOR3(mGfxInfo, mSelected);
	}
}

/* Saves the states of the component*/
void XOR3::Save(ofstream& file) {

}

/* Loads the states of the component */
void XOR3::Load() {

}

/* Returns the Add-ActionType of the component */
ActionType XOR3::GetAddActionType() const {
	return ActionType::ADD_GATE_XOR3;
}