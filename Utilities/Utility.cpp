#pragma once
#include "Utility.h"
#include "..\GUI\UserInterface.h"

/* Returns the indices of the pin based on the given coordinates */
void getPinIndices(int& x, int& y) {
	x = (x / UI.PinOffset);
	y = (y - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;
}

/* Normalizes the given coordinates to concide exactly above a pin */
void normalizeCoordinates(int& x, int& y) {
	getPinIndices(x, y);

	x = (x * UI.PinOffset) + UI.PinMargin;
	y = (y * UI.PinOffset) + UI.PinMargin + UI.ToolBarHeight + UI.GateBarHeight;
}