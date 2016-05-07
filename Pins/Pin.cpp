#include "Pin.h"

/* Constructor */
Pin::Pin() {
	mStatus = Status::LOW;	// Default status is LOW
}

/* Sets the pin state */
void Pin::SetStatus(Status s) {
	mStatus = s;
}

/* Returns the status of the pin */
Status Pin::GetStatus() const {
	return mStatus;
}
