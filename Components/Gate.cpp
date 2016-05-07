#include "Gate.h"

/* Constructor */
Gate::Gate(Output* pOut, const GraphicsInfo& gfxInfo) {
	SetGraphicsInfo(pOut, gfxInfo);
}

/* Sets the bound coordinates of the component */
void Gate::SetGraphicsInfo(Output* pOut, const GraphicsInfo& gfxInfo) {
	// Clear previous gate
	pOut->MarkPins(mGfxInfo, PinType::EMPTY, NULL);

	// Update gate
	mGfxInfo = gfxInfo;
	pOut->MarkPins(mGfxInfo, PinType::GATE, this);
}

/* Returns the input pin coordiantes of the gate */
void Gate::GetInputPinCoordinates(int& x, int& y, int& n) {
	n = 0;
	x = mGfxInfo.x1 - UI.PinMargin;
	y = mGfxInfo.y1 + (mGfxInfo.y2 - mGfxInfo.y1) / 2;
}

/* Returns the output pin coordiantes of the gate */
void Gate::GetOutputPinCoordinates(int& x, int& y) {
	x = mGfxInfo.x2 + UI.PinMargin;
	y = mGfxInfo.y1 + (mGfxInfo.y2 - mGfxInfo.y1) / 2;
}

/* Deletes the component */
void Gate::Delete(Output* pOut) {
	mSelected = false;
	mDeleted = true;
	pOut->MarkPins(mGfxInfo, PinType::EMPTY, NULL);
}

/* Restores the component after being deleted */
void Gate::Restore(Output* pOut) {
	mDeleted = false;
	pOut->MarkPins(mGfxInfo, PinType::GATE, this);
}

/* Destructor */
Gate::~Gate() {
	
}