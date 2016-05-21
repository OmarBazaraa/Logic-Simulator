#pragma once
#include "..\Utilities\Defs.h"
#include "..\GUI\Output.h"
#include <vector>

class Gate;			// Forward class declaration
class Connection;	// Forward class declaration

class Pin
{
private:
	int mFanout;								// Maximum number of connections that can be connected to that pin
	int mConnectionsCount;						// Actual number of connections connected to that pin
	Status mStatus;								// Status of the Pin (high or low)
	Gate* mGate;								// Gate at which this pin is associated
	Connection* mConnections[MAX_CONNECTIONS];	// Array of connections to be connected to that pin
	vector<Connection*> mBackupConnections;		// Vector of backup connections, used in UNDO & REDO actions

public:
	/* Constructor */
	Pin(int fanout = 1);

	/* Sets the pin state */
	void SetStatus(Status s);

	/* Returns the status of the pin */
	Status GetStatus() const;

	/* Sets the associated gate of this pin */
	void SetGate(Gate* pGate);

	/* Returns the gate of this pin */
	Gate* GetGate() const;

	/* Connects the output pin to a new connection if the fanout permits */
	bool ConnectTo(Connection* pConnection);

	/* Removes the given connection from the pin */
	bool RemoveConnection(Connection* pConnection);

	/* Returns the number of connected connections to the pin */
	int GetConnectionsCount() const;

	/* Checks if this pin is full or not */
	bool IsFull() const;

	/* Returns the connection connected to the pin */
	Connection* GetConnection(int index);

	/* Deletes the pin which removes all connected connections from the pin */
	void Delete(Output* pOut);

	/* Restores the pin after being deleted */
	void Restore(Output* pOut);
};