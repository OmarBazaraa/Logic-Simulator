/*
#include "GUI\Input.h"
#include "GUI\Output.h"

/* The demo function of phase-1, just in case you need to check something *//*
int demo() {
	int x, y;

	// Create Input and Output objects to test
	Output *pOut = new Output();
	Input *pIn = pOut->CreateInput();

	// Starting the demo
	pOut->PrintMsg("This demo is to test Input and Output classes. Click anywhere to start the test");
	pIn->GetPointClicked(x, y);

	////////////////////////////////////////////////////////////////////////////////////////
	// TEST 1: Create The FULL ToolBar, the Drawing Area and the StatusBar	
	////////////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST1: Drawing ToolBar and StatusBar. Click anywhere to continue");
	pIn->GetPointClicked(x, y);

	////////////////////////////////////////////////////////////////////////////////////////
	// TEST 2: Drawing all the Components with all possible states: Normal, highlighted
	////////////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST2: Now we will show that the Output class can draw any component in any state. Click anywhere to continue");
	pIn->GetPointClicked(x, y);

	GraphicsInfo gfxInfo;

	// 1. AND & NAND Gates test
	pOut->PrintMsg("Drawing AND & NAND gates, normal and highlighted. Click to continue");

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawAND(gfxInfo);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawAND(gfxInfo, true);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 300;
	pOut->DrawAND3(gfxInfo);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 400;
	pOut->DrawAND3(gfxInfo, true);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawNAND(gfxInfo);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawNAND(gfxInfo, true);

	pIn->GetPointClicked(x, y);
	pOut->ClearDrawingArea();

	// 2. OR & NOR Gates test
	pOut->PrintMsg("Drawing OR & NOR gates, normal and highlighted. Click to continue");

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawOR(gfxInfo);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawOR(gfxInfo, true);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 300;
	pOut->DrawNOR(gfxInfo);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 400;
	pOut->DrawNOR(gfxInfo, true);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawNOR3(gfxInfo);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawNOR3(gfxInfo, true);

	pIn->GetPointClicked(x, y);
	pOut->ClearDrawingArea();

	// 3. XOR & XNOR Gates test
	pOut->PrintMsg("Drawing XOR & XNOR gates, normal and highlighted. Click to continue");

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawXOR(gfxInfo);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawXOR(gfxInfo, true);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 300;
	pOut->DrawXNOR(gfxInfo);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 400;
	pOut->DrawXNOR(gfxInfo, true);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawXOR3(gfxInfo);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawXOR3(gfxInfo, true);

	pIn->GetPointClicked(x, y);
	pOut->ClearDrawingArea();

	// 4. Buffer & Inverter Gates test
	pOut->PrintMsg("Drawing Buffer & Inverter gates, normal and highlighted. Click to continue");

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawBuffer(gfxInfo);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawBuffer(gfxInfo, true);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawNOT(gfxInfo);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawNOT(gfxInfo, true);

	pIn->GetPointClicked(x, y);
	pOut->ClearDrawingArea();

	// 5. Switch & LED test 
	pOut->PrintMsg("Drawing Switch & LED, normal and highlighted. Click to continue");

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawSwitch(gfxInfo);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawSwitch(gfxInfo, true);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 100;
	pOut->DrawLED(gfxInfo);

	gfxInfo.x1 = 400;	gfxInfo.y1 = UI.GateBarHeight + 200;
	pOut->DrawLED(gfxInfo, true);

	pIn->GetPointClicked(x, y);
	pOut->ClearDrawingArea();

	// 6. Connections
	pOut->PrintMsg("Drawing connections, normal, highlighted, straight, and broken. Click to continue");

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 100;
	gfxInfo.x2 = 400;	gfxInfo.y2 = UI.GateBarHeight + 100;
	//pOut->DrawConnection(gfxInfo);

	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 400;
	gfxInfo.x2 = 400;	gfxInfo.y2 = UI.GateBarHeight + 400;
	//pOut->DrawConnection(gfxInfo, true);

	gfxInfo.x1 = 800;	gfxInfo.y1 = UI.GateBarHeight + 100;
	gfxInfo.x2 = 1100;	gfxInfo.y2 = UI.GateBarHeight + 300;
	//pOut->DrawConnection(gfxInfo);

	gfxInfo.x1 = 800;	gfxInfo.y1 = UI.GateBarHeight + 400;
	gfxInfo.x2 = 1100;	gfxInfo.y2 = UI.GateBarHeight + 600;
	//pOut->DrawConnection(gfxInfo, true);

	pIn->GetPointClicked(x, y);
	pOut->ClearDrawingArea();

	////////////////////////////////////////////////////////////////////////////////////////
	// TEST 3: Read strings from the user
	////////////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST3: Now time to test the Input class. Click anywhere to continue");
	pIn->GetPointClicked(x, y);

	pOut->PrintMsg("Testing Input ability to read strings");
	pIn->GetPointClicked(x, y);

	//TODO: Add code here to 
	// 1- Read a string from the user on the status bar and print it inside the drawing area
	pOut->ClearStatusBar();
	gfxInfo.x1 = 100;	gfxInfo.y1 = UI.GateBarHeight + 100;
	string s = pIn->GetSrting(pOut);
	pOut->DrawLabel(gfxInfo, s);

	pIn->GetPointClicked(x, y);
	pOut->ClearDrawingArea();

	////////////////////////////////////////////////////////////////////////////////////////
	// TEST 4: Check for the user actions
	////////////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST4: Testing Input ability to detect User Action. click anywhere to continue");

	ActionType ActType;

	do {
		ActType = pIn->GetUserAction();

		switch (ActType)
		{
		case ADD_GATE_AND:
			pOut->PrintMsg("AND");
			break;
		case ADD_GATE_NAND:
			pOut->PrintMsg("NAND");
			break;
		case ADD_GATE_AND3:
			pOut->PrintMsg("AND 3");
			break;
		case ADD_GATE_OR:
			pOut->PrintMsg("OR");
			break;
		case ADD_GATE_NOR:
			pOut->PrintMsg("NOR");
			break;
		case ADD_GATE_NOR3:
			pOut->PrintMsg("NOR 3");
			break;
		case ADD_GATE_XOR:
			pOut->PrintMsg("XOR");
			break;
		case ADD_GATE_XNOR:
			pOut->PrintMsg("XNOR");
			break;
		case ADD_GATE_XOR3:
			pOut->PrintMsg("XOR 3");
			break;
		case ADD_GATE_BUFFER:
			pOut->PrintMsg("BUFFER");
			break;
		case ADD_GATE_NOT:
			pOut->PrintMsg("NOT");
			break;
		case ADD_CONNECTION:
			pOut->PrintMsg("CONNECTION");
			break;
		case ADD_SWITCH:
			pOut->PrintMsg("SWITCH");
			break;
		case ADD_LED:
			pOut->PrintMsg("LED");
			break;
		case EDIT:
			pOut->PrintMsg("EDIT");
			break;
		case DEL:
			pOut->PrintMsg("DELETE");
			break;
		case COPY:
			pOut->PrintMsg("COPY");
			break;
		case CUT:
			pOut->PrintMsg("CUT");
			break;
		case PASTE:
			pOut->PrintMsg("PASTE");
			break;
		case UNDO:
			pOut->PrintMsg("UNDO");
			break;
		case REDO:
			pOut->PrintMsg("REDO");
			break;
		case SIMULATION_MODE:
			pOut->PrintMsg("SIMULATION MODE");
			UI.AppMode = Mode::SIMULATION;
			pOut->CreateSimulationToolBar();
			pOut->CreateSimulationGateBar();
			break;
		case DESIGN_MODE:
			pOut->PrintMsg("DESIGN MODE");
			UI.AppMode = Mode::DESIGN;
			pOut->CreateDesignToolBar();
			pOut->CreateDesignGateBar();
			break;
		case CREATE_TRUTH_TABLE:
			pOut->PrintMsg("TRUTH TABLE");
			break;
		case SAVE:
			pOut->PrintMsg("SAVE");
			break;
		case LOAD:
			pOut->PrintMsg("LOAD");
			break;
		case EXIT:
			pOut->PrintMsg("EXIT");
			break;
		case TOOL_BAR:
			pOut->PrintMsg("TOOL BAR");
			break;
		case GATE_BAR:
			pOut->PrintMsg("GATE BAR");
			break;
		case SELECT:
			pOut->PrintMsg("DRAWING AREA");
			break;
		case STATUS_BAR:
			pOut->PrintMsg("STATUS BAR");
			break;
		}

	} while (ActType != EXIT);

	pIn->GetPointClicked(x, y);

	// Exiting the demo
	pOut->PrintMsg("Test is finished. Click anywhere to exit");

	delete pIn;
	delete pOut;
	return 0;
}
*/