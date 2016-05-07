#pragma once
#include "Gate.h"

class Switch : public Gate
{
private:
	OutputPin mOutputPin;	// The output pin of the switch

public:
	/* Constructor */
	Switch(Output* pOut, const GraphicsInfo& gfxInfo, int fanout);

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

	/* Calculates the output of the switch */
	virtual void Operate();

	/* Draws the switch */
	virtual void Draw(Output* pOut);

	/* Selects the component */
	virtual void Select();

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};