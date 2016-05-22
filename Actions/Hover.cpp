#include "Hover.h"
#include "..\Components\Connection.h"

/* Constructor */
Hover::Hover(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Hover::ReadActionParameters() {
	return true;
}

/* Executes action */
bool Hover::Execute() {
	Output* pOut = mAppManager->GetOutput();
	Input* pIn = mAppManager->GetInput();

	Component* pComp = NULL;
	
	int x, y;
	int prvX = -1;
	int prvY = -1;

	int minX = 0;
	int maxX = UI.Width;
	int minY = UI.ToolBarHeight + UI.GateBarHeight;
	int maxY = UI.Height - minY;
	
	int lastHovedArea = -1;		// 0 for tool bar, 1 for gate bar, 2 for drawing area , 3 for status bar
	int hoveredItemOrder = -1;
	int lastHoveredItemOrder = -1;

	// Store the previous window
	image wind;
	pOut->StoreImage(wind, minX, minY, maxX, maxY);

	// Loop until the user click the mouse left button
	while (pIn->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_UP) {
		// User hovers on the tool bar
		if (y >= 0 && y < UI.ToolBarHeight) {
			if (lastHovedArea != 0) {
				lastHovedArea = 0;
				lastHoveredItemOrder = -1;
				pOut->CreateGateBar();
				pOut->DrawImage(wind, minX, minY, maxX, maxY);
			}

			hoveredItemOrder = x / UI.ToolItemWidth;

			if (hoveredItemOrder != lastHoveredItemOrder && hoveredItemOrder < TOOLS_COUNT) {
				pOut->CreateToolBar(hoveredItemOrder);
				lastHoveredItemOrder = hoveredItemOrder;
			}
		}
		// User hovers on the gate bar
		else if (y > UI.ToolBarHeight && y < UI.ToolBarHeight + UI.GateBarHeight) {
			if (lastHovedArea != 1) {
				lastHovedArea = 1;
				lastHoveredItemOrder = -1;
				pOut->CreateToolBar();
				pOut->DrawImage(wind, minX, minY, maxX, maxY);
			}

			hoveredItemOrder = x / UI.GateItemWidth;

			if (hoveredItemOrder != lastHoveredItemOrder && hoveredItemOrder < GATES_COUNT) {
				pOut->CreateGateBar(hoveredItemOrder);
				lastHoveredItemOrder = hoveredItemOrder;
			}
		}
		// User hovers on the drawing area
		else if (y >= UI.ToolBarHeight + UI.GateBarHeight && y < UI.Height - UI.StatusBarHeight) {
			if (lastHovedArea != 2) {
				lastHovedArea = 2;
				pOut->CreateToolBar();
				pOut->CreateGateBar();
			}

			normalizeCoordinates(x, y);

			if (x != prvX || y != prvY) {
				pComp = pOut->GetComponentAtPin(x, y);
				pOut->DrawImage(wind, minX, minY, maxX, maxY);

				if (pComp != NULL) {
					// Show label
					if (UI.AppMode == Mode::DESIGN) {
						pOut->DrawLabel(x, y, pComp->GetLabel());
					}
					// Probe the connections
					else if (dynamic_cast<Connection*>(pComp)) {
						pOut->DrawLabel(x, y, to_string(pComp->GetInputPinStatus(0)));
					}
				}

				prvX = x;
				prvY = y;
			}
		}
		// User hovers on the status bar
		else {
			if (lastHovedArea != 4) {
				lastHovedArea = 4;
				pOut->CreateToolBar();
				pOut->CreateGateBar();
				pOut->DrawImage(wind, minX, minY, maxX, maxY);
			}
		}
	}

	// Redraw the initial window
	pOut->DrawImage(wind, minX, minY, maxX, maxY);

	return false;	// To prevent adding this action to the stack
}

/* Undo action */
void Hover::Undo() {
	return;
}

/* Redo action */
void Hover::Redo() {
	return;
}

/* Destructor */
Hover::~Hover() {

}