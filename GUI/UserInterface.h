#pragma once
#include "..\Utilities\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

/*
	User Interface information file.
	This file contains info that is needed by Input and Output classes to
	handle the user interface
*/
__declspec(selectany)	// This line to prevent "redefinition error"

struct UserInterface
{
	// Windows Dimension constants
	static const int Width = 1344,	Height = 800;				// Window width and height
	static const int StartX = 15,	StartY = 15;				// Window starting coordinates
	static const int ToolBarHeight = 50;						// Tool bar height
	static const int ToolItemWidth = 50;						// Width of each item in the tool bar menu
	static const int GateBarHeight = 75;						// Gate bar height
	static const int GateItemWidth = 96;						// Width of each item in the gate bar menu
	static const int StatusBarHeight = 35;						// Status bar height
	static const int StatusFontSize = 20;						// Status bar font size
	static const int PinMargin = 8;								// The margin distance around the pin
	static const int PinOffset = PinMargin * 2;					// The distance between two successive pins
	static const int HorPinsCount = Width / PinOffset;
	static const int VerPinsCount = (Height - ToolBarHeight - GateBarHeight - StatusBarHeight) / PinOffset;

	// Components Dimension constants
	static const int LogicGateWidth = 80,	LogicGateHeight = 48;
	static const int SwitchWidth = 48,		SwitchHeight = 48;
	static const int LedWidth = 48,			LedHeight = 48;

	Mode AppMode;	// Application Mode (design or simulation)

	// Colors
	color BackgroundColor;
	color DarkColor;
	color SelectionColor;
	color MsgColor;
	color ConnectionColor;
	color ConnectionOnColor;

} UI;	// Create a single global object UI