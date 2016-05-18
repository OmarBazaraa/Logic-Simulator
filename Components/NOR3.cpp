#include "NOR3.h"

/* Constructor */
NOR3::NOR3(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : LogicGate(pOut, gfxInfo, 3, fanOut) {
	mLabel = "NOR3";
}

/* Calculates the output of the NOR3 gate */
void NOR3::Operate() {
	bool out = 0;

	for (int i = 0; i < mInputsCount; i++) {
		out = out || (mInputPins[i].GetStatus() == Status::HIGH ? 1 : 0);
	}

	mOutputPin.SetStatus(out ? Status::LOW : Status::HIGH);
}

/* Draws the NOR3 gate */
void NOR3::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawNOR3(mGfxInfo, mSelected, mOutputPin.GetStatus() == Status::HIGH);
	}
}

/* Saves the states of the component*/
void NOR3::Save(ofstream& file) {
	file << "NOR3 " << mID << " " << mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType NOR3::GetAddActionType() const {
	return ActionType::ADD_GATE_NOR3;
}