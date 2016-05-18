#pragma once
#include "Gate.h"

class Switch : public Gate
{
private:
	Pin mOutputPin;	// The output pin of the switch

public:
	/* Constructor */
	Switch(Output* pOut, const GraphicsInfo& gfxInfo, int fanout);

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

	/* Calculates the output of the switch */
	virtual void Operate();

	/* Draws the switch */
	virtual void Draw(Output* pOut);

	/* Selects the component */
	virtual void Select();

	/* Deletes the component */
	virtual void Delete(Output* pOut);

	/* Restores the component after being deleted */
	virtual void Restore(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};