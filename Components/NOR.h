#pragma once
#include "LogicGate.h"

class NOR : public LogicGate
{
public:
	/* Constructor */
	NOR(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut);

	/* Calculates the output of the NOR gate */
	virtual void Operate();

	/* Draws the NOR gate */
	virtual void Draw(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Loads the states of the component */
	virtual void Load();

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};