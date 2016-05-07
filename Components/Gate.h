#pragma once
#include "Component.h"
#include "..\Pins\InputPin.h"
#include "..\Pins\OutputPin.h"

/*
	Base class for all types of gates
*/
class Gate : public Component
{
public:
	/* Constructor */
	Gate(Output* pOut, const GraphicsInfo& gfxInfo);

	/* Sets the bound coordinates of the component */
	void SetGraphicsInfo(Output* pOut, const GraphicsInfo& gfxInfo);

	/* Returns the input pin number n (0-indexed) of the component */
	virtual InputPin* GetInputPin(int n) = 0;

	/* Returns the output pin of the component */
	virtual OutputPin* GetOutputPin() = 0;

	/* Returns the input pin coordiantes of the gate */
	virtual void GetInputPinCoordinates(int& x, int& y, int& n);

	/* Returns the output pin coordiantes of the gate */
	virtual void GetOutputPinCoordinates(int& x, int& y);

	/* Deletes the component */
	virtual void Delete(Output* pOut);

	/* Restores the component after being deleted */
	virtual void Restore(Output* pOut);

	/* Destructor */
	virtual ~Gate();
};