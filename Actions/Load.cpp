#include "Load.h"



Load::Load(ApplicationManager* pAppMan) : Action(pAppMan) {
	read.open("Data.txt");
}


bool Load::Execute() {
	int n, id, cX, cY;
	string t, l;
	read >> n;
	for (int i = 0; i < n; i++) {
		Action *pAct = 0;
		read >> t >> id >> l >> cX >> cY;
		if (t == "AND")
			pAct = new AddGate(mAppManager, ADD_GATE_AND, cX, cY, l);
		else if (t == "OR")
			pAct = new AddGate(mAppManager, ADD_GATE_OR, cX, cY, l);
		else if (t == "NOR")
			pAct = new AddGate(mAppManager, ADD_GATE_NOR, cX, cY);
		else if (t == "XOR")
			pAct = new AddGate(mAppManager, ADD_GATE_XOR, cX, cY, l);
		else if (t == "NOR3")
			pAct = new AddGate(mAppManager, ADD_GATE_NOR3, cX, cY, l);
		else if (t == "XNOR")
			pAct = new AddGate(mAppManager, ADD_GATE_XNOR, cX, cY, l);
		else if (t == "BUFFER")
			pAct = new AddGate(mAppManager, ADD_GATE_BUFFER, cX, cY, l);
		else if (t == "LED")
			pAct = new AddGate(mAppManager, ADD_LED, cX, cY, l);
		else if (t == "XOR3")
			pAct = new AddGate(mAppManager, ADD_GATE_XOR3, cX, cY, l);
		else if (t == "NAND")
			pAct = new AddGate(mAppManager, ADD_GATE_NAND, cX, cY, l);
		else if (t == "AND3")
			pAct = new AddGate(mAppManager, ADD_GATE_AND3, cX, cY, l);
		else if (t == "NOT")
			pAct = new AddGate(mAppManager, ADD_GATE_NOT, cX, cY, l);
		else if (t == "SWITCH")
			pAct = new AddGate(mAppManager, ADD_SWITCH, cX, cY, l);
		if (pAct)
			pAct->Execute();
		delete pAct;
	}
	return true;
}

Load::~Load()
{
}
