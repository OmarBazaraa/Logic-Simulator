#include "LogicGate.h"

/* Constructor */
LogicGate::LogicGate(Output* pOut, const GraphicsInfo& gfxInfo, int inputs, int fanOut) : Gate(pOut, gfxInfo), mOutputPin(fanOut) {
	mInputsCount = inputs;
	mInputPins = new InputPin[inputs];

	// Associate all input pins to this gate
	for (int i = 0; i < mInputsCount; i++) mInputPins[i].SetComponent(this);
}

/* Returns the input pin number n (0-indexed) of the component */
InputPin* LogicGate::GetInputPin(int n) {
	return &mInputPins[n];
}

/* Returns the output pin of the component */
OutputPin* LogicGate::GetOutputPin() {
	return &mOutputPin;
}

/* Sets the status of the input pin number n (0-indexed) */
void LogicGate::SetInputPinStatus(int n, Status s) {
	mInputPins[n].SetStatus(s);
}

/* Returns the status of the input pin number n (0-indexed) */
int LogicGate::GetInputPinStatus(int n) const {
	return mInputPins[n].GetStatus();
}

/* Returns the status of the output pin */
int LogicGate::GetOutputPinStatus() const {
	return mOutputPin.GetStatus();
}

/* Returns the input pin coordiantes of the gate */
void LogicGate::GetInputPinCoordinates(int& x, int& y, int& n) {
	n = (y - mGfxInfo.y1) / UI.PinOffset;
	x = mGfxInfo.x1 - UI.PinMargin;
	y = mGfxInfo.y1 + (n * UI.PinOffset) + UI.PinMargin;
}

/* Destructor */
LogicGate::~LogicGate() {
	delete[] mInputPins;
}