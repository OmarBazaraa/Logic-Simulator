#include "NOR.h"

/* Constructor */
NOR::NOR(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : LogicGate(pOut, gfxInfo, 2, fanOut) {
	mLabel = "NOR";
}

/* Calculates the output of the NOR gate */
void NOR::Operate() {
	bool out = 0;

	for (int i = 0; i < mInputsCount; i++) {
		out = out || (mInputPins[i].GetStatus() == Status::HIGH ? 1 : 0);
	}

	mOutputPin.SetStatus(out ? Status::LOW : Status::HIGH);
}

/* Draws the NOR gate */
void NOR::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawNOR(mGfxInfo, mSelected, mOutputPin.GetStatus() == Status::HIGH);
	}
}

/* Saves the states of the component*/
void NOR::Save(ofstream& file) {
	file << "NOR " << mID << " " << mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType NOR::GetAddActionType() const {
	return ActionType::ADD_GATE_NOR;
}