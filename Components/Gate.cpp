#include "Gate.h"

/* Constructor */
Gate::Gate(Output* pOut, const GraphicsInfo& gfxInfo) {
	SetGraphicsInfo(pOut, gfxInfo);
}

/* Sets the bound coordinates of the component */
void Gate::SetGraphicsInfo(Output* pOut, const GraphicsInfo& gfxInfo) {
	// Clear previous gate
	//pOut->MarkPins(mGfxInfo, PinType::EMPTY, NULL);

	// Update gate
	mGfxInfo = gfxInfo;
	pOut->MarkPins(mGfxInfo, PinType::GATE, this);
}

/* Returns the selected input pin index */
int Gate::GetInputPinIndex(int x, int y) {
	return 0;
}

/* Returns the input pin coordiantes of the gate according to its index */
void Gate::GetInputPinCoordinates(int& x, int& y, int n) {
	x = mGfxInfo.x1 - UI.PinMargin;
	y = mGfxInfo.y1 + UI.PinMargin + UI.PinOffset * n;
}

/* Returns the output pin coordiantes of the gate */
void Gate::GetOutputPinCoordinates(int& x, int& y) {
	x = mGfxInfo.x2 + UI.PinMargin;
	y = mGfxInfo.y1 + (mGfxInfo.y2 - mGfxInfo.y1) / 2;
}

/* Destructor */
Gate::~Gate() {
	
}