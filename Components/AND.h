#pragma once
#include "LogicGate.h"

class AND : public LogicGate
{
public:
	/* Constructor */
	AND(Output* pOut, const GraphicsInfo& gfxInfo, int fanout);

	/* Calculates the output of the AND gate */
	virtual void Operate();

	/* Draws the AND gate */
	virtual void Draw(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};