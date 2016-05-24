#pragma once
#include <string>
using namespace std;

/*
	This header file contains some defenitions to be used all over the application
*/

#define MAX_COMPONENTS	400	// Maximum number of components
#define MAX_CONNECTIONS	5	// Maximum number of input pins that can be connected to any output pin
#define GATES_FANOUT	3
#define SWITCH_FANOUT	3
#define LED_FANOUT		0

#ifndef NULL
#define NULL			0
#endif

class Component;	// Forward class declaration

/* All possible actions a user can perform */
enum ActionType {
	ADD_GATE_AND,		// Add AND gate
	ADD_GATE_OR,		// Add OR gate
	ADD_GATE_NOT,		// Add NOT gate
	ADD_GATE_NAND,		// Add NAND gate
	ADD_GATE_NOR,		// Add NOR gate
	ADD_GATE_XOR,		// Add XOR gate
	ADD_GATE_XNOR,		// Add XNOR gate
	ADD_GATE_AND3,		// Add AND3 gate
	ADD_GATE_NOR3,		// Add NOR3 gate
	ADD_GATE_XOR3,		// Add XOR3 gate
	ADD_GATE_BUFFER,	// Add BUFFER gate
	ADD_SWITCH,			// Add Switch
	ADD_LED,			// Add LED
	ADD_CONNECTION,		// Add Wire Connection

	//ADD_LABEL,		// Add label to a component, a connection
	EDIT,				// Edit label of a component, a connection
	DEL,				// Delete a component, a connection
	COPY,				// Copy components
	CUT,				// Cut components
	PASTE,				// Paste components
	UNDO,				// Undo the last action performed
	REDO,				// Redo the last action
	SIMULATION_MODE,	// Switch to simulatiom mode
	DESIGN_MODE,		// Switch to design mode
	CREATE_TRUTH_TABLE,	// Create Truth Table of the Circuit
	SAVE,				// Save the whole circuit to a file
	LOAD,				// Load a circuit from a file
	EXIT,				// Exit the application

	//CHANGE_SWITCH,	// Change switch status in simulation mode
	SELECT,				// Select a component, a connection
	HOVER,				// Hover over a certain Item or a component
	MOVE,				// Move a component, a connection

	TOOL_BAR,			// A click on an empty place in the toolbar
	GATE_BAR,			// A click on an empty place in the gatebar
	STATUS_BAR,			// A click on the status bar
};

/* Tool bar items */
enum ToolBarItem {
	ITEM_EDIT,
	ITEM_DELETE,
	ITEM_COPY,
	ITEM_CUT,
	ITEM_PASTE,
	ITEM_UNDO,
	ITEM_REDO,
	ITEM_PLAY,
	ITEM_PAUSE,
	ITEM_TRUTHTABLE,
	ITEM_SAVE,
	ITEM_LOAD,
	ITEM_EXIT,

	TOOLS_COUNT,
};

/* Gate bar items */
enum GateBarItem {
	ITEM_AND,
	ITEM_OR,
	ITEM_NOT,
	ITEM_NAND,
	ITEM_NOR,
	ITEM_XOR,
	ITEM_XNOR,
	ITEM_AND3,
	ITEM_NOR3,
	ITEM_XOR3,
	ITEM_BUFFER,
	ITEM_SWITCH,
	ITEM_LED,
	ITEM_CONNECTION,

	GATES_COUNT
};

/* Status of a pin (0 or 1) */
enum Status {
	LOW,
	HIGH
};

/* Modes of the application */
enum Mode {
	DESIGN,
	SIMULATION
};

/* Type of what the pin is containing */
enum PinType {
	EMPTY,						// Empty pin
	GATE,						// Pin containing gate, switch or led
	HOR_CONNECTION,				// Pin containing horizontal connection
	VER_CONNECTION,				// Pin containing vertical connection
	INTERSECTING_CONNECTIONS	// Pin containing intersecting horizontal and vertical connections
};

/* Infromation of what the pin is containing */
struct PinInfo {
	PinType Type;
	Component* Comp;
	Component* PreviousComp;	// Used to get the overlapped connection

	PinInfo() {
		Type = PinType::EMPTY;
		Comp = NULL;
		PreviousComp = NULL;
	}
};

/* Structure holding the index of a pin, used in calculating the path of the connection */
struct Node {
	int x, y;	// The X and Y indices of the pin

	/* Zero-argument constructor */
	Node() {
		x = y = -1;		// Invalid indices as default value
	}

	/* Constructor for ease of access */
	Node(int x, int y) {
		this->x = x;
		this->y = y;
	}

	/* Equality operator for ease of access */
	bool operator==(const Node& rhs) const {
		return (x == rhs.x && y == rhs.y);
	}

	/* Non-equality operator for ease of access */
	bool operator!=(const Node& rhs) const {
		return (x != rhs.x || y != rhs.y);
	}
};

/* Structure holding drawing parameters for components */
struct GraphicsInfo {
	int x1, y1;		// Upper left point
	int x2, y2;		// Lower right point

	/* Zero-argument constructor */
	GraphicsInfo() {
		x1 = x2 = y1 = y2 = 0;
	}

	/* Constructor for ease of access */
	GraphicsInfo(int x1, int y1, int x2, int y2) {
		// To preserve the upper left and lower right points
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);

		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	/* Equality operator for ease of access */
	bool operator==(const GraphicsInfo& rhs) const {
		return (x1 == rhs.x1 && y1 == rhs.y1 && x2 == rhs.x2 && y2 == rhs.y2);
	}
};

/* Structure holding the loaded information needed for creating new components */
struct Data {
	string Label;
	GraphicsInfo GfxInfo;
};

enum DialogBoxButton {
	YES,
	NO,
	OK,
	CANCEL
};

enum DialogBoxType {
	Type_A,         // Three buttons exist YES, NO and CANCEL
	Type_B,         // Two buttons exist OK, CANCEL
	Type_C          // One button exists OK
};