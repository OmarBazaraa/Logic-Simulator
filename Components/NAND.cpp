#include "NAND.h"

/* Constructor */
NAND::NAND(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : LogicGate(pOut, gfxInfo, 2, fanOut) {
	mLabel = "NAND";
}

/* Calculates the output of the NAND gate */
void NAND::Operate() {
	bool out = 1;

	for (int i = 0; i < mInputsCount; i++) {
		out = out && (mInputPins[i].GetStatus() == Status::HIGH ? 1 : 0);
	}

	mOutputPin.SetStatus(out ? Status::LOW : Status::HIGH);
}

/* Draws the NAND gate */
void NAND::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawNAND(mGfxInfo, mSelected);
	}
}

/* Saves the states of the component*/
void NAND::Save(ofstream& file) {
	file << "NAND " << mID << " " << mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}

/* Returns the Add-ActionType of the component */
ActionType NAND::GetAddActionType() const {
	return ActionType::ADD_GATE_NAND;
}