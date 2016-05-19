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

	/*int n = visited.size();
	visited.insert(c);
	if(c==NULL || n==visited.size()){
		mAppManager->ExecuteAction(DESIGN_MODE);
		mAppManager->GetOutput()->PrintMsg("Error !! : Components are not connected properly.");
	}*/

	if (dynamic_cast<Switch*>(c))
		return c->GetOutputPinStatus();

	if (dynamic_cast<LED*>(c))
		return TestGate(((LED*)c)->GetInputPin(0)->GetGate());

	if (dynamic_cast<Connection*>(c))
		return TestGate(((Connection*)c)->GetSourcePin()->GetGate());

	else if (dynamic_cast<LogicGate*>(c)) {
		
		for (int i = 0;; i++) {
			if (((LogicGate*)c)->GetInputPin(i)->GetGate()) {
				((LogicGate*)c)->SetInputPinStatus(i, Status(TestGate(((LogicGate*)c)->GetInputPin(i)->GetGate())));
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
