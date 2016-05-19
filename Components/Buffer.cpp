#include "Buffer.h"

/* Constructor */
Buffer::Buffer(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut) : LogicGate(pOut, gfxInfo, 1, fanOut) {
	mLabel = "Buffer";
}

/* Calculates the output of the Buffer gate */
void Buffer::Operate() {
	//the output is as is, what you see is what you get :P xD
	//if this make you smile pray for me :) ^_^

	mOutputPin.SetStatus(mInputPins[0].GetStatus());
}

/* Draws the Buffer gate */
void Buffer::Draw(Output* pOut) {
	if (!mDeleted) {
		pOut->DrawBuffer(mGfxInfo, mSelected);
	}
}

/* Saves the states of the component*/
void Buffer::Save(ofstream& file) {
	file << "BUFFER " << mID << " " << mLabel << " " << (mGfxInfo.x1 + mGfxInfo.x2) / 2 << " " << (mGfxInfo.y1 + mGfxInfo.y2) / 2 << endl;
}


/* Returns the Add-ActionType of the component */
ActionType Buffer::GetAddActionType() const {
	return ActionType::ADD_GATE_BUFFER;
}