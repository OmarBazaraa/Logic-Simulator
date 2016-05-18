#include "Hover.h"
#include "..\\Components\Connection.h"

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
	int x, y;
	pOut->StoreWindowImage();

	while (pOut->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_UP) {
		if (y > UI.ToolBarHeight && y < UI.ToolBarHeight + UI.GateBarHeight && UI.AppMode == DESIGN) {
			int HoveredItemOrder = x / UI.GateItemWidth;
			pOut->DrawImage(UI.AppMode == DESIGN ? "Images\\bars\\toolbar_design.jpg" : "Images\\bars\\toolbar_simulation.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
			switch (HoveredItemOrder) {
			case GateBarItem::ITEM_AND:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\1.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_NAND:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\2.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_AND3:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\3.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_OR:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\4.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_NOR:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\5.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_NOR3:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\6.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_XOR:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\7.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_XNOR:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\8.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_XOR3:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\9.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_BUFFER:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\10.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_NOT:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\11.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_CONNECTION:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\12.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_SWITCH:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\13.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			case GateBarItem::ITEM_LED:
				pOut->DrawImage("Images\\bars\\gatebar_hover\\14.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			default:
				pOut->DrawImage("Images\\bars\\gatebar_active.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
				break;
			}
		}
		else if (y < UI.ToolBarHeight && UI.AppMode == DESIGN) {
			pOut->DrawImage(UI.AppMode == DESIGN ? "Images\\bars\\gatebar_active.jpg" : "Images\\bars\\gatebar_inactive.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);

			int HoveredItemOrder = x / UI.ToolItemWidth;

			switch (HoveredItemOrder) {
			case ToolBarItem::ITEM_EDIT:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\1.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_DELETE:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\2.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_COPY:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\3.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_CUT:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\4.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_PASTE:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\5.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_UNDO:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\6.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_REDO:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\7.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_PLAY:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\8.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_SAVE:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\9.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_LOAD:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\10.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_EXIT:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\11.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			default:
				pOut->DrawImage("Images\\bars\\toolbar_design.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			}
		}

		else if (y < UI.ToolBarHeight && UI.AppMode == SIMULATION) {
			pOut->DrawImage(UI.AppMode == DESIGN ? "Images\\bars\\gatebar_active.jpg" : "Images\\bars\\gatebar_inactive.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
			int HoveredItemOrder = x / UI.ToolItemWidth;
			switch (HoveredItemOrder) {
			case ToolBarItem::ITEM_PAUSE:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\12.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_TRUTHTABLE:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\13.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			case ToolBarItem::ITEM_EXIT:
				pOut->DrawImage("Images\\bars\\toolbar_hover\\14.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			default:
				pOut->DrawImage("Images\\bars\\toolbar_simulation.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
				break;
			}
		}
		else
			pOut->DrawImage(pOut->GetWindowImage(), 0, 0, UI.Width, UI.Height);
		//else if (y < UI.Height - UI.StatusBarHeight) {
		//	pOut->DrawImage(UI.AppMode == DESIGN ? "Images\\bars\\gatebar_active.jpg" : "Images\\bars\\gatebar_inactive.jpg", 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
		//	pOut->DrawImage(UI.AppMode == DESIGN ? "Images\\bars\\toolbar_design.jpg" : "Images\\bars\\toolbar_simulation.jpg", 0, 0, UI.Width, UI.ToolBarHeight);
		//	pOut->StoreWindow();
		//	Component* Comp = pOut->GetComponentAtPin(x, y);
		//	if (Comp == NULL) 
		//		pOut->DrawImage(pOut->GetWindow(), 0, 0, UI.Width, UI.Height);
		//	else {
		//		ActionType actType = Comp->GetAddActionType();
		//		GraphicsInfo Gfxinfo = Comp->GetGraphicsInfo();
		//		switch (actType)
		//		{
		//		case ADD_GATE_AND:
		//			pOut->DrawAND(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_OR:
		//			pOut->DrawOR(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_NOT:
		//			pOut->DrawNOT(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_NAND:
		//			pOut->DrawNAND(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_NOR:
		//			pOut->DrawNOR(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_XOR:
		//			pOut->DrawXOR(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_XNOR:
		//			pOut->DrawXNOR(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_AND3:
		//			pOut->DrawAND3(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_NOR3:
		//			pOut->DrawNOR(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_XOR3:
		//			pOut->DrawXOR3(Gfxinfo, true);
		//			break;
		//		case ADD_GATE_BUFFER:
		//			pOut->DrawBuffer(Gfxinfo, true);
		//			break;
		//		case ADD_SWITCH:
		//			pOut->DrawSwitch(Gfxinfo, true);
		//			break;
		//		case ADD_LED:
		//			pOut->DrawLED(Gfxinfo, true);
		//			break;
		//		case ADD_CONNECTION:
		//			pOut->DrawConnection(dynamic_cast <Connection *> (Comp)->GetPath(), true);
		//			break;
		//		default:
		//			break;
		//		}
		//	}
		//}
	}

	pOut->DrawImage(pOut->GetWindowImage(), 0, 0, UI.Width, UI.Height);

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