#include "Pin.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"

/* Constructor */
Pin::Pin(int fanout) {
	mStatus = Status::LOW;	// Default status is LOW
	mConnectionsCount = 0;	// Initially pin is not connected to anything
	mFanout = fanout > MAX_CONNECTIONS ? MAX_CONNECTIONS : fanout;
	mComp = NULL;
}

/* Connects the output pin to a new connection if the fanout permits */
bool Pin::ConnectTo(Connection* pConnection) {
	if (mConnectionsCount < mFanout) {
		mConnections[mConnectionsCount++] = pConnection;
		return true;
	}

	return false;	// Can't connect any more connections
}

/* Removes the given connection from the output pin */
bool Pin::RemoveConnection(Connection* pConnection) {
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
bool Pin::IsFull() const {
	return (mConnectionsCount == mFanout);
}

/* Sets the associated component of this input pin */
void Pin::SetComponent(Component* pComp) {
	mComp = pComp;
}

/* Returns the component of this input pin */
Component* Pin::GetComponent() const {
	return mComp;
}

/* Sets the pin state */
void Pin::SetStatus(Status s) {
	mStatus = s;
}

/* Returns the status of the pin */
Status Pin::GetStatus() const {
	return mStatus;
}