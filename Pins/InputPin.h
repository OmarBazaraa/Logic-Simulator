#pragma once
#include "Pin.h"

class Component;	// Forward class declaration
class Connection;	// Forward class declaration

class InputPin : public Pin
{
private:
	Component* mComp;			// Component at which this pin is associated
	Connection* mConnection;	// Connection at which this pin is associated

public:
	/* Constructor */
	InputPin();

	/* Sets the associated component of this input pin */
	void SetComponent(Component* pComp);

	/* Returns the component of this input pin */
	Component* GetComponent() const;

	/* Sets the associated connection of this input pin */
	void SetConnection(Connection* pConnection);

	/* Returns the connection of this input pin */
	Connection* GetConnection() const;

	/* Checks if this pin is full or not */
	virtual bool IsFull() const;
};