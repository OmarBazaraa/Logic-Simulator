#pragma once
#include "Gate.h"
#include <fstream>

class LED : public Gate
{
private:
	InputPin mInputPin;	// The input pin of the LED

public:
	/* Constructor */
	LED(Output* pOut, const GraphicsInfo& gfxInfo);

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

	/* Calculates the output of the LED */
	virtual void Operate();

	/* Draws the LED */
	virtual void Draw(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Loads the states of the component */
	virtual void Load();

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};