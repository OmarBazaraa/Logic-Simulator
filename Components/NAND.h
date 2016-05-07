#pragma once
#include "LogicGate.h"

class NAND : public LogicGate
{
public:
	/* Constructor */
	NAND(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut);

	/* Calculates the output of the NAND gate */
	virtual void Operate();

	/* Draws the NAND gate */
	virtual void Draw(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};