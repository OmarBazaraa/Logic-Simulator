#pragma once
#include "LogicGate.h"

class XOR : public LogicGate
{
public:
	/* Constructor */
	XOR(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut);

	/* Calculates the output of the XOR gate */
	virtual void Operate();

	/* Draws the XOR gate */
	virtual void Draw(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};