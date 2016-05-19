#pragma once
#include "LogicGate.h"

class NAND : public LogicGate
{
public:
	/* Constructor */
	NAND(Output* pOut, const GraphicsInfo& gfxInfo, int fanOut);

	/* Returns the input pin coordiantes of the gate */
	virtual void GetInputPinCoordinates(int& x, int& y, int n);

	/* Calculates the output of the NAND gate */
	virtual void Operate();

	/* Draws the NAND gate */
	virtual void Draw(Output* pOut);

	/* Saves the states of the component*/
	virtual void Save(ofstream& file);

	/* Returns the Add-ActionType of the component */
	virtual ActionType GetAddActionType() const;
};