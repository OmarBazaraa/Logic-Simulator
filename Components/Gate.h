#pragma once
#include "Component.h"
#include "..\Pins\Pin.h"

/*
	Base class for all types of gates, switches and LEDs
*/
class Gate : public Component
{
public:
	/* Constructor */
	Gate(Output* pOut, const GraphicsInfo& gfxInfo);

	/* Sets the bound coordinates of the component */
	void SetGraphicsInfo(Output* pOut, const GraphicsInfo& gfxInfo);

	/* Returns the input pin number n (0-indexed) of the component */
	virtual Pin* GetInputPin(int n) = 0;

	/* Returns the output pin of the component */
	virtual Pin* GetOutputPin() = 0;

	/* Returns the selected input pin index */
	virtual int GetInputPinIndex(int x, int y);

	/* Returns the input pin coordiantes of the gate according to its index */
	virtual void GetInputPinCoordinates(int& x, int& y, int n);

	/* Returns the output pin coordiantes of the gate */
	virtual void GetOutputPinCoordinates(int& x, int& y);

	/* Destructor */
	virtual ~Gate();
};