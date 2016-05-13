#pragma once
#include "..\Utilities\Defs.h"

class Component;	// Forward class declaration
class Connection;	// Forward class declaration

class Pin
{
private:
	int mFanout;								// Maximum number of connections that can be connected to that pin
	int mConnectionsCount;						// Actual number of connections connected to that pin
	Connection* mConnections[MAX_CONNECTIONS];	// Array of connections to be connected to that pin
	Component* mComp;							// Component at which this pin is associated
	Status mStatus;								// Status of the Pin (high or low)

public:
	/* Constructor */
	Pin(int fanout = 1);

	/* Connects the output pin to a new connection if the fanout permits */
	bool ConnectTo(Connection* pConnection);

	/* Removes the given connection from the output pin */
	bool RemoveConnection(Connection* pConnection);

	/* Checks if this pin is full or not */
	bool IsFull() const;

	/* Sets the associated component of this input pin */
	void SetComponent(Component* pComp);

	/* Returns the component of this input pin */
	Component* GetComponent() const;

	/* Sets the pin state */
	void SetStatus(Status s);

	/* Returns the status of the pin */
	Status GetStatus() const;
};