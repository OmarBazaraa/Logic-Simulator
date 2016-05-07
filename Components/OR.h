#pragma once
#include "LogicGate.h"

class OR : public LogicGate
{
public:
	/* Constructor */
	OR(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut);

	/* Calculates the output of the OR gate */
	virtual void Operate();

	/* Draws the OR gate */
	virtual void Draw(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Loads the states of the component */
	virtual void Load();

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};