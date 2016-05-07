#include "OutputPin.h"
#include "../Components/Connection.h"

/* Constructor */
OutputPin::OutputPin(int fanout) {
	mConnectionsCount = 0;	// Initially pin is not connected to anything
	mFanout = fanout > MAX_CONNECTIONS ? MAX_CONNECTIONS: fanout;
}

/* Connects the output pin to a new connection if the fanout permits */
bool OutputPin::ConnectTo(Connection* pConnection) {
	if (mConnectionsCount < mFanout) {
		mConnections[mConnectionsCount++] = pConnection;
		return true;
	}
	
	return false;	// Can't connect any more connections
}

/* Removes the given connection from the output pin */
bool OutputPin::RemoveConnection(Connection* pConnection) {
	int idx = -1;

	// Searching for the given connection
	for (int i = 0; i < mConnectionsCount; i++) {
		if (mConnections[i] == pConnection) {
			idx = i;
			break;
		}
	}

	if (idx == -1) return false;	// The given connection was not found

	// Removing the given connection from the pin
	mConnectionsCount--;

	for (int i = idx; i < mConnectionsCount; i++) {
		mConnections[i] = mConnections[i + 1];
	}

	mConnections[mConnectionsCount] = NULL;

	return true;
}

/* Checks if this pin is full or not */
bool OutputPin::IsFull() const {
	return (mConnectionsCount == mFanout);
}