#include "InputPin.h"
#include "../Components/Component.h"
#include "../Components/Connection.h"

/* Constructor */
InputPin::InputPin() {
	mComp = NULL;
	mConnection = NULL;
}

/* Sets the associated component of this input pin */
void InputPin::SetComponent(Component* pComp) {
	mComp = pComp;
}

/* Returns the component of this input pin */
Component* InputPin::GetComponent() const {
	return mComp;
}

/* Sets the associated connection of this input pin */
void InputPin::SetConnection(Connection* pConnection) {
	mConnection = pConnection;
}

/* Returns the connection of this input pin */
Connection* InputPin::GetConnection() const {
	return mConnection;
}

/* Checks if this pin is full or not */
bool InputPin::IsFull() const {
	return (mConnection != NULL);
}