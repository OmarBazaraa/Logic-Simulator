#pragma once
#include "LogicGate.h"

class XNOR : public LogicGate
{
public:
	/* Constructor */
	XNOR(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut);

	/* Calculates the output of the XNOR gate */
	virtual void Operate();

	/* Draws the XNOR gate */
	virtual void Draw(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Loads the states of the component */
	virtual void Load();

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};