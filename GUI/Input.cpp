#include "Input.h"
#include "Output.h"
#include "..\Components\Gate.h"

/* Constructor */
Input::Input(window* pW) {
	pWind = pW;
}

/* Returns the last point clicked by the user */
void Input::GetLastPointClicked(int& x, int& y) const {
	x = mLastX;
	y = mLastY;
}

/* Waits and returns the user's mouse click coordinate */
void Input::WaitMouseClick(int& x, int& y) {
	pWind->WaitMouseClick(x, y);
	mLastX = x;
	mLastY = y;
}

/* Returns information on the current state of the mouse buttons and it's position */
buttonstate Input::GetButtonState(const button btMouse, int& x, int& y) {
	return pWind->GetButtonState(btMouse, x, y);;
}

// Returns the user's key press
keytype Input::GetKeyPress(char& key) {
	//pWind->FlushKeyQueue();
	return pWind->GetKeyPress(key);
}

// Returns the user's key press without removing it from the queue
keytype Input::GetKeyState(char& key) {
	return pWind->GetKeyState(key);
}

/* Returns the string entered by the user and reflect it on the status bar */
string Input::GetSrting(Output* pOut, string msg, string str) const {
	// ASCII Codes
	const int ESCAPE = 27;
	const int ENTER = 13;
	const int BACKSPACE = 8;

	char c;
	string s = str;

	pWind->FlushKeyQueue();

	do {
		pOut->PrintMsg(msg + " " + s);
		pWind->WaitKeyPress(c);
		
		switch (c) {
		case BACKSPACE:
			if (!s.empty()) s.pop_back();
			break;
		case ESCAPE:
			s.clear();
			break;
		case ENTER:
			// Nothing to be done here
			break;
		default:
			s.push_back(c);
			break;
		}

	} while (c != ESCAPE && c != ENTER);

	return s;
}

/* Reads the user's selection and determine the desired action */
ActionType Input::GetUserAction(Output* pOut) {
	pWind->FlushMouseQueue();

	int x, y;
	char hotKey;
	keytype keyType;

	while (GetButtonState(LEFT_BUTTON, x, y) == BUTTON_UP) {
		keyType = pWind->GetKeyState(hotKey);

		if (keyType == NO_KEYPRESS) {
			return ActionType::HOVER;
		}

		// Detecting actions using hotkeys
		if (UI.AppMode == Mode::DESIGN) {
			if (keyType == keytype::KEY_DEL) {
				pWind->FlushKeyQueue();
				return ActionType::DEL;
			}
			else if (keyType == ASCII) {
				switch (hotKey)
				{
				case CTRL_A:
					return ActionType::SELECT;
				case CTRL_S:
					pWind->FlushKeyQueue();
					return ActionType::SAVE;
				case CTRL_Z:
					pWind->FlushKeyQueue();
					return ActionType::UNDO;
				case CTRL_Y:
					pWind->FlushKeyQueue();
					return ActionType::REDO;
				case CTRL_C:
					pWind->FlushKeyQueue();
					return ActionType::COPY;
				case CTRL_X:
					pWind->FlushKeyQueue();
					return ActionType::CUT;
				case CTRL_V:
					pWind->FlushKeyQueue();
					return ActionType::PASTE;
				case CTRL_O:
					pWind->FlushKeyQueue();
					return ActionType::LOAD;
				}
			}
		}
		
		pWind->FlushKeyQueue();
	}

	mLastX = x;
	mLastY = y;

	// User clicks on the drawing area
	if (y >= UI.ToolBarHeight + UI.GateBarHeight && y < UI.Height - UI.StatusBarHeight) {
		if (UI.AppMode == Mode::DESIGN) {
			Component* pComp = pOut->GetComponentAtPin(x, y);

			if (pComp != NULL) {
				int startX = x;
				int startY = y;

				while (GetButtonState(LEFT_BUTTON, x, y) == BUTTON_DOWN) {
					if (startX != x || startY != y) {
						return ActionType::MOVE;
					}
				}
			}

			Gate* pGate = dynamic_cast<Gate*>(pComp);

			int iX, iY;

			if (pGate != NULL) {
				pGate->GetOutputPinCoordinates(iX, iY);

				getPinIndices(x, y);
				getPinIndices(iX, iY);

				if (x == iX - 1 && y == iY) {
					return ActionType::ADD_CONNECTION;
				}
			}

			return ActionType::SELECT;
		}
		else {
			WaitMouseClick(x, y);
			return ActionType::SELECT;
		}
	}

	pWind->WaitMouseClick(x, y);

	// User clicks on the tool bar
	if (y >= 0 && y < UI.ToolBarHeight) {
		int clickedItemOrder = x / UI.ToolItemWidth;

		if (UI.AppMode == Mode::DESIGN) {
			switch (clickedItemOrder) {
			case ToolBarItem::ITEM_EDIT:
				return ActionType::EDIT;
			case ToolBarItem::ITEM_DELETE:
				return ActionType::DEL;
			case ToolBarItem::ITEM_COPY:
				return ActionType::COPY;
			case ToolBarItem::ITEM_CUT:
				return ActionType::CUT;
			case ToolBarItem::ITEM_PASTE:
				return ActionType::PASTE;
			case ToolBarItem::ITEM_UNDO:
				return ActionType::UNDO;
			case ToolBarItem::ITEM_REDO:
				return ActionType::REDO;
			case ToolBarItem::ITEM_PLAY:
				return ActionType::SIMULATION_MODE;
			case ToolBarItem::ITEM_SAVE:
				return ActionType::SAVE;
			case ToolBarItem::ITEM_LOAD:
				return ActionType::LOAD;
			case ToolBarItem::ITEM_EXIT:
				return ActionType::EXIT;
			default:
				return ActionType::TOOL_BAR;
			}
		}
		else {
			switch (clickedItemOrder) {
			case ToolBarItem::ITEM_PAUSE:
				return ActionType::DESIGN_MODE;
			case ToolBarItem::ITEM_TRUTHTABLE:
				return ActionType::CREATE_TRUTH_TABLE;
			case ToolBarItem::ITEM_EXIT:
				return ActionType::EXIT;
			default:
				return ActionType::TOOL_BAR;
			}
		}
	}
	// User clicks on the gate bar
	else if (y >= UI.ToolBarHeight && y < UI.ToolBarHeight + UI.GateBarHeight) {
		int clickedItemOrder = x / UI.GateItemWidth;

		if (UI.AppMode == Mode::DESIGN) {
			switch (clickedItemOrder) {
			case GateBarItem::ITEM_AND:
				return ActionType::ADD_GATE_AND;
			case GateBarItem::ITEM_NAND:
				return ActionType::ADD_GATE_NAND;
			case GateBarItem::ITEM_AND3:
				return ActionType::ADD_GATE_AND3;
			case GateBarItem::ITEM_OR:
				return ActionType::ADD_GATE_OR;
			case GateBarItem::ITEM_NOR:
				return ActionType::ADD_GATE_NOR;
			case GateBarItem::ITEM_NOR3:
				return ActionType::ADD_GATE_NOR3;
			case GateBarItem::ITEM_XOR:
				return ActionType::ADD_GATE_XOR;
			case GateBarItem::ITEM_XNOR:
				return ActionType::ADD_GATE_XNOR;
			case GateBarItem::ITEM_XOR3:
				return ActionType::ADD_GATE_XOR3;
			case GateBarItem::ITEM_BUFFER:
				return ActionType::ADD_GATE_BUFFER;
			case GateBarItem::ITEM_NOT:
				return ActionType::ADD_GATE_NOT;
			case GateBarItem::ITEM_CONNECTION:
				return ActionType::ADD_CONNECTION;
			case GateBarItem::ITEM_SWITCH:
				return ActionType::ADD_SWITCH;
			case GateBarItem::ITEM_LED:
				return ActionType::ADD_LED;
			default:
				return ActionType::GATE_BAR;
			}
		}
		else {
			return ActionType::GATE_BAR;
		}
	}
	// User clicks on the status bar
	else {
		return ActionType::STATUS_BAR;
	}	
}

/* Destructor */
Input::~Input() {

}