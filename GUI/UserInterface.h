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
	static const int Width = 1344,	Height = 768;				// Window width and height
	static const int StartX = 10,	StartY = 10;				// Window starting coordinates
	static const int ToolBarHeight = 50;						// Tool bar height
	static const int ToolItemWidth = 50;						// Width of each item in the tool bar menu
	static const int GateBarHeight = 75;						// Gate bar height
	static const int GateItemWidth = 96;						// Width of each item in the gate bar menu
	static const int StatusBarHeight = 35;						// Status bar height
	static const int FontSize = 20;								// Font size
	static const int TextMargin = 10;							// The margin distance between text
	static const int PinMargin = 8;								// The margin distance around the pin
	static const int PinOffset = PinMargin * 2;					// The distance between two successive pins
	static const int HorPinsCount = Width / PinOffset;
	static const int VerPinsCount = (Height - ToolBarHeight - GateBarHeight - StatusBarHeight) / PinOffset;
	static const int TruthTableMargin = 20;
	static const int ExitMargin = 10;
	static const int Column = 100;
	static const int Row = 20;
	static const int Exit = 20;
	static const int StatusMargin = 45;
	static const int DialogStartX = 485;
	static const int DialogStartY = 400;
	static const int DialogWidth = 414;
	static const int DialogHeight = 165;
	static const int ButtonWidht = 100;
	static const int ButtonHeight = 30;
	static const int DialogMargin = 25;
	static const int ButtonStartY = 90;
	static const int MessageStartX = 15;
	static const int MessageStartY = 35;



	// Components Dimension constants
	static const int LogicGateWidth = 80,	LogicGateHeight = 48;
	static const int SwitchWidth = 48,		SwitchHeight = 48;
	static const int LedWidth = 48,			LedHeight = 48;

	Mode AppMode;	// Application Mode (design or simulation)

	// Colors
	color BackgroundColor;
	color DarkColor;
	color SelectionColor;
	color InvalidColor;
	color MsgColor;
	color ConnectionColor;
	color ConnectionOnColor;

} UI;	// Create a single global object UI