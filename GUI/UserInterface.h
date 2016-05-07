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
	static const int StatusBarHeight = 50;						// Status bar height
	static const int StatusFontSize = 20;						// Status bar font size
	static const int PinMargin = 10;							// The margin distance around the pin
	static const int PinOffset = PinMargin * 2;					// The distance between two successive pins
	static const int HorPinsCount = Width / PinOffset;
	static const int VerPinsCount = (Height - ToolBarHeight - GateBarHeight - StatusBarHeight) / PinOffset;

	// Components Dimension constants
	static const int AndGateWidth = 79,		AndGateHeight = 45;
	static const int OrGateWidth = 79,		OrGateHeight = 46;
	static const int NotGateWidth = 74,		NotGateHeight = 46;
	static const int NandGateWidth = 86,	NandGateHeight = 45;
	static const int NorGateWidth = 86,		NorGateHeight = 46;
	static const int XorGateWidth = 79,		XorGateHeight = 46;
	static const int XnorGateWidth = 86,	XnorGateHeight = 46;
	static const int And3GateWidth = 79,	And3GateHeight = 45;
	static const int Nor3GateWidth = 86,	Nor3GateHeight = 46;
	static const int Xor3GateWidth = 79,	Xor3GateHeight = 46;
	static const int BufferGateWidth = 66,	BufferGateHeight = 46;
	static const int SwitchWidth = 50,		SwitchHeight = 27;
	static const int LedWidth = 40,			LedHeight = 51;

	Mode AppMode;	// Application Mode (design or simulation)

	// Colors
	color DrawColor;
	color SelectionColor;
	color ConnectionColor;
	color MsgColor;
	color BackgroundColor;
	color StatusBarColor;

} UI;	// Create a single global object UI