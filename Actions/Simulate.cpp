#include "Simulate.h"


/* Constructor */
Simulate::Simulate(ApplicationManager* pAppMan) : Action(pAppMan) {

}


bool Simulate::Execute() {
	Component ** list = mAppManager->GetComponentList();
	int count = mAppManager->GetComponentsCount();
	for (int i = 0; i < count; i++) {
		if (dynamic_cast<LED*>(list[i]) && !list[i]->IsDeleted())
			list[i]->SetInputPinStatus(0,(Status)TestGate(list[i]));
	}	
	return false;
}

/*Tests the output on a led*/
int Simulate::TestGate(Component*c) {

	if (dynamic_cast<Switch*>(c))
		return c->GetOutputPinStatus();

	if (dynamic_cast<LED*>(c))
		return TestGate(((LED*)c)->GetInputPin(0)->GetComponent());

	if (dynamic_cast<Connection*>(c))
		return TestGate(((Connection*)c)->GetSourcePin()->GetComponent());

	else if (dynamic_cast<LogicGate*>(c)) {
		
		for (int i = 0;; i++) {
			if (((LogicGate*)c)->GetInputPin(i)->GetComponent()) {
				((LogicGate*)c)->SetInputPinStatus(i, Status(TestGate(((LogicGate*)c)->GetInputPin(i)->GetComponent())));
			}
			else break;
		}
			((LogicGate*)c)->Operate();
			return ((LogicGate*)c)->GetOutputPinStatus();
	}
}

Simulate::~Simulate()
{
}
