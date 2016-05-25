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

	/* Returns the selected input pin index */
	virtual int GetInputPinIndex(int x, int y);

	/* Returns the input pin coordiantes of the gate according to its index */
	virtual void GetInputPinCoordinates(int& x, int& y, int n);

	/* Returns the output pin coordiantes of the gate */
	virtual void GetOutputPinCoordinates(int& x, int& y);

	/* Returns the input pin number n (0-indexed) of the component, NULL if switch */
	virtual Pin* GetInputPin(int n) = 0;

	/* Returns the output pin of the component, NULL if LED */
	virtual Pin* GetOutputPin() = 0;

	/* Returns next connected */
	virtual Component* GetNextComponent(int index) = 0;

	/* Returns number of connected components */
	virtual int GetConnectedCount() = 0;

	/* Destructor */
	virtual ~Gate();
};