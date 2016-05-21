#pragma once
#include "Gate.h"

class LED : public Gate
{
private:
	Pin mInputPin;	// The input pin of the LED

public:
	/* Constructor */
	LED(Output* pOut, const GraphicsInfo& gfxInfo);

	/* Returns the input pin number n (0-indexed) of the component */
	virtual Pin* GetInputPin(int n);

	/* Returns the output pin of the component */
	virtual Pin* GetOutputPin();

	/* Sets the status of the input pin number n (0-indexed) */
	virtual void SetInputPinStatus(int n, Status s);

	/* Returns the status of the input pin number n (0-indexed) */
	virtual int GetInputPinStatus(int n) const;

	/* Returns the status of the output pin */
	virtual int GetOutputPinStatus() const;

	/* Returns the input pin coordiantes of the gate */
	virtual void GetInputPinCoordinates(int& x, int& y, int n);

	/* Calculates the output of the LED */
	virtual void Operate();

	/* Draws the LED */
	virtual void Draw(Output* pOut);

	/* Deletes the component */
	virtual void Delete(Output* pOut);

	/* Restores the component after being deleted */
	virtual void Restore(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};