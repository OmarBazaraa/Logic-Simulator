#pragma once
#include "Pin.h"

class Connection;	// Forward class declaration

class OutputPin : public Pin
{
private:
	int mFanout;								// Maximum number of connections that can be connected to that pin
	int mConnectionsCount;						// Actual number of connections connected to that pin
	Connection* mConnections[MAX_CONNECTIONS];	// Array of connections to be connected to that pin
	
public:
	/* Constructor */
	OutputPin(int fanout);

	/* Connects the output pin to a new connection if the fanout permits */
	bool ConnectTo(Connection* pConnection);

	/* Removes the given connection from the output pin */
	bool RemoveConnection(Connection* pConnection);

	/* Checks if this pin is full or not */
	virtual bool IsFull() const;
};