#include "Simulate.h"


/* Constructor */
Simulate::Simulate(ApplicationManager* pAppMan) : Action(pAppMan) {
	stopSimulation = 0;
}


bool Simulate::Execute() {
	Component ** list = mAppManager->GetComponentList();
	int count = mAppManager->GetComponentsCount();
	for (int i = 0; i < count; i++) {
		if (dynamic_cast<LED*>(list[i]) && !list[i]->IsDeleted())
			TestGate(list[i]);
		visited.clear();
	}	
	if (stopSimulation) {
		mAppManager->ExecuteAction(DESIGN_MODE);
		mAppManager->GetOutput()->PrintMsg("Error !! : Components are not connected properly.");
	}
	return false;
}

/*Tests the output on a led*/
int Simulate::TestGate(Component*c) {

	int n = visited.size();
	if (c)
		visited.insert(c);
	else
		return -1;
	if(n==visited.size()) {
		stopSimulation = 1;
		return -1;
	}
	int returnValue;
	if (c) {

		if (dynamic_cast<Switch*>(c))
			return c->GetOutputPinStatus();

		else if (dynamic_cast<LED*>(c)) {
			returnValue = TestGate(((LogicGate*)c)->GetInputPin(0)->GetConnection(0));
			if (returnValue > -1)
				((Gate*)c)->SetInputPinStatus(0, (Status)returnValue);
			return returnValue;
		}

		else if (dynamic_cast<Connection*>(c)) {
			return TestGate(((Connection*)c)->GetSourcePin()->GetGate());
		}

		else if (dynamic_cast<LogicGate*>(c)) {

			for (int i = 0;; i++) {
				if (((LogicGate*)c)->GetInputPin(i)->GetConnection(0)) {
					returnValue = TestGate(((LogicGate*)c)->GetInputPin(i)->GetConnection(0));
					if (returnValue > -1)
						((Gate*)c)->SetInputPinStatus(i, (Status)returnValue);
					else break;
				}
				else break;
			}
			((LogicGate*)c)->Operate();
			return ((LogicGate*)c)->GetOutputPinStatus();
		}
	}
	else 0;
}

Simulate::~Simulate()
{
}
