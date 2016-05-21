#include "NOT.h"

/* Constructor */
NOT::NOT(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : LogicGate(pOut, gfxInfo, 1, fanOut) {
	mLabel = "NOT";
}

/* Returns the input pin coordiantes of the gate according to its index */
void NOT::GetInputPinCoordinates(int& x, int& y, int n) {
	x = mGfxInfo.x1 - UI.PinMargin;
	y = mGfxInfo.y1 + UI.PinMargin + UI.PinOffset;
}

/* Calculates the output of the NOT gate */
void NOT::Operate() {
	mOutputPin.SetStatus(mInputPins[0].GetStatus() == Status::LOW ? Status::HIGH : Status::LOW);
}

/* Draws the NOT gate */
void NOT::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawNOT(mGfxInfo, mSelected);
	}
}

/* Saves the states of the component*/
void NOT::Save(ofstream& file) {
	file << "NOT "<< mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType NOT::GetAddActionType() const {
	return ActionType::ADD_GATE_NOT;
}