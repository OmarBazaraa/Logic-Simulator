#pragma once
#include "..\Utilities\Defs.h"

class Pin
{
protected:
	Status mStatus;	// Status of the Pin (high or low)

public:
	/* Constructor */
	Pin();

	/* Sets the pin state */
	void SetStatus(Status s);

	/* Returns the status of the pin */
	Status GetStatus() const;

	/* Checks if this pin is full or not */
	virtual bool IsFull() const = 0;
};