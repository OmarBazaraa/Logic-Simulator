#pragma once
/*
	This header file contains some useful helper functions be used all over the application
*/

/* Returns the indices of the pin based on the given coordinates */
void getPinIndices(int& x, int& y);

/* Normalizes the given coordinates to concide exactly above a pin */
void normalizeCoordinates(int& x, int& y);