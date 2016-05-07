#pragma once
#include "Gate.h"

/*
	Base class for all types of gates
*/
class LogicGate : public Gate
{
protected:
	int mInputsCount;		// Number of input pins
	InputPin* mInputPins;	// Array of input pins
	OutputPin mOutputPin;	// The output pin of the gate
	
public:
	/* Constructor */
	LogicGate(Output* pOut, const GraphicsInfo& gfxInfo, int inputs, int fanout);

	/* Returns the input pin number n (0-indexed) of the component */
	virtual InputPin* GetInputPin(int n);

	/* Returns the output pin of the component */
	virtual OutputPin* GetOutputPin();

	/* Sets the status of the input pin number n (0-indexed) */
	virtual void SetInputPinStatus(int n, Status s);

	/* Returns the status of the input pin number n (0-indexed) */
	virtual int GetInputPinStatus(int n) const;

	/* Returns the status of the output pin */
	virtual int GetOutputPinStatus() const;

	/* Returns the input pin coordiantes of the gate */
	virtual void GetInputPinCoordinates(int& x, int& y, int& n);

	/* Destructor */
	~LogicGate();
};