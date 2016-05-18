#include "Pin.h"
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"

/* Constructor */
Pin::Pin(int fanout) {
	mStatus = Status::LOW;	// Default status is LOW
	mConnectionsCount = 0;	// Initially pin is not connected to anything
	mFanout = fanout > MAX_CONNECTIONS ? MAX_CONNECTIONS : fanout;
	mGate = NULL;
}

/* Sets the pin state */
void Pin::SetStatus(Status s) {
	mStatus = s;
}

/* Returns the status of the pin */
Status Pin::GetStatus() const {
	return mStatus;
}

/* Sets the associated gate of this pin */
void Pin::SetGate(Gate* pGate) {
	mGate = pGate;
}

/* Returns the gate of this pin */
Gate* Pin::GetGate() const {
	return mGate;
}

/* Connects the output pin to a new connection if the fanout permits */
bool Pin::ConnectTo(Connection* pConnection) {
	if (mConnectionsCount < mFanout) {
		mConnections[mConnectionsCount++] = pConnection;
		return true;
	}

	return false;	// Can't connect any more connections
}

/* Removes the given connection from the pin */
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

/* Deletes the pin which removes all connected connections from the pin */
void Pin::Delete(Output* pOut) {
	mBackupConnections.clear();

	for (int i = mConnectionsCount - 1; i >= 0; i--) {
		mBackupConnections.push_back(mConnections[i]);
		mConnections[i]->Delete(pOut);
	}
}

/* Restores the pin after being deleted */
void Pin::Restore(Output* pOut) {
	for (int i = 0; i < (int)mBackupConnections.size(); i++) {
		mBackupConnections[i]->Restore(pOut);
	}
}