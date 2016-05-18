#include "LogicGate.h"

/* Constructor */
LogicGate::LogicGate(Output* pOut, const GraphicsInfo& gfxInfo, int inputs, int fanOut) : Gate(pOut, gfxInfo), mOutputPin(fanOut) {
	mInputsCount = inputs;
	mInputPins = new Pin[inputs];

	// Associate all input & output pins to this gate
	for (int i = 0; i < mInputsCount; i++) mInputPins[i].SetGate(this);
	mOutputPin.SetGate(this);
}

/* Returns the input pin number n (0-indexed) of the component */
Pin* LogicGate::GetInputPin(int n) {
	return &mInputPins[n];
}

/* Returns the output pin of the component */
Pin* LogicGate::GetOutputPin() {
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

/* Returns the selected input pin index */
int LogicGate::GetInputPinIndex(int x, int y) {
	int h = (mGfxInfo.y2 - mGfxInfo.y1);
	int n = (y - mGfxInfo.y1) * mInputsCount / h;

	return n;
}

/* Deletes the component */
void LogicGate::Delete(Output* pOut) {
	mSelected = false;
	mDeleted = true;
	mOutputPin.Delete(pOut);
	for (int i = 0; i < mInputsCount; i++) {
		mInputPins[i].Delete(pOut);
	}
	pOut->MarkPins(mGfxInfo, PinType::EMPTY, NULL);
}

/* Restores the component after being deleted */
void LogicGate::Restore(Output* pOut) {
	mDeleted = false;
	mOutputPin.Restore(pOut);
	for (int i = 0; i < mInputsCount; i++) {
		mInputPins[i].Restore(pOut);
	}
	pOut->MarkPins(mGfxInfo, PinType::GATE, this);
}

/* Destructor */
LogicGate::~LogicGate() {
	delete[] mInputPins;
}