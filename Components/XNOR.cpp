#include "XNOR.h"

/* Constructor */
XNOR::XNOR(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : LogicGate(pOut, gfxInfo, 2, fanOut) {
	mLabel = "XNOR";
}

/* Returns the input pin coordiantes of the gate according to its index */
void XNOR::GetInputPinCoordinates(int& x, int& y, int n) {
	x = mGfxInfo.x1 - UI.PinMargin;
	y = mGfxInfo.y1 + UI.PinMargin + UI.PinOffset * (n > 0 ? 2 : n);
}

/* Calculates the output of the XNOR gate */
void XNOR::Operate() {
	bool out = 0;

	for (int i = 0; i < mInputsCount; i++) {
		out = out ^ (mInputPins[i].GetStatus() == Status::HIGH ? 1 : 0);
	}

	mOutputPin.SetStatus(out ? Status::LOW : Status::HIGH);
}

/* Draws the XNOR gate */
void XNOR::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawXNOR(mGfxInfo, mSelected);
	}
}

/* Saves the states of the component*/
void XNOR::Save(ofstream& file) {
	file << "XNOR " << mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType XNOR::GetAddActionType() const {
	return ActionType::ADD_GATE_XNOR;
}