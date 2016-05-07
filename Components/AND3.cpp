#include "AND3.h"

/* Constructor */
AND3::AND3(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : LogicGate(pOut, gfxInfo, 3, fanOut) {
	mLabel = "AND3";
}

/* Calculates the output of the AND3 gate */
void AND3::Operate() {
	bool out = 1;

	for (int i = 0; i < mInputsCount; i++) {
		out = out && (mInputPins[i].GetStatus() == Status::HIGH ? 1 : 0);
	}

	mOutputPin.SetStatus(out ? Status::HIGH : Status::LOW);
}

/* Draws the AND3 gate */
void AND3::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawAND3(mGfxInfo, mSelected);
	}
}

/* Saves the states of the component*/
void AND3::Save(ofstream& file) {
	file << "AND3 " << mID << " " << mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType AND3::GetAddActionType() const {
	return ActionType::ADD_GATE_AND3;
}