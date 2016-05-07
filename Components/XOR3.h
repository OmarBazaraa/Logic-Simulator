#pragma once
#include "LogicGate.h"

class XOR3 : public LogicGate
{
public:
	/* Constructor */
	XOR3(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut);

	/* Calculates the output of the XOR3 gate */
	virtual void Operate();

	/* Draws the XOR3 gate */
	virtual void Draw(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};