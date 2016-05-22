#include "Simulate.h"

/* Constructor */
Simulate::Simulate(ApplicationManager* pAppMan) : Action(pAppMan) {
	stopSimulation = false;
}

/* Reads parameters required for action to execute */
bool Simulate::ReadActionParameters() {
	return true;
}

/* Executes action */
bool Simulate::Execute() {
	Component** list = mAppManager->GetComponentList();
	int count = mAppManager->GetComponentsCount();

	for (int i = 0; i < count; i++) {
		if (dynamic_cast<LED*>(list[i]) && !list[i]->IsDeleted())
			TestGate(list[i]);
		
		visited.clear();
	}	

	ActionType act = DESIGN_MODE;
	if (stopSimulation) {
		mAppManager->ExecuteAction(act);
		mAppManager->GetOutput()->PrintMsg("Error !! : Components are not connected properly.");
	}
	
	return false;
}

/* Tests the output on a led */
int Simulate::TestGate(Component* pComp) {
	//validation

	int n = visited.size();
	if (pComp != NULL)
		visited.insert(pComp);
	else
		return -1;

	// Detects inner feedback
	if (n == visited.size()) {
		stopSimulation = true;
		return -1;
	}

	int returnValue;

	if (pComp != NULL) {
		if (dynamic_cast<Switch*>(pComp)) {
			visited.erase(pComp);
			return pComp->GetOutputPinStatus();
		}
		else if (dynamic_cast<LED*>(pComp)) {
			if (((LED*)pComp)->GetInputPin(0)->IsFull())
				returnValue = TestGate(((LED*)pComp)->GetInputPin(0)->GetConnection(0)->GetSourcePin()->GetGate());
			else { 
				returnValue = -1;
				stopSimulation = true;
			}
			if (returnValue > -1)
				((LED*)pComp)->SetInputPinStatus(0, returnValue ? Status::HIGH : Status::LOW);
			return returnValue;
		}
		else if (dynamic_cast<LogicGate*>(pComp)) {

			for (int i = 0; i<((LogicGate*)pComp)->GetInputsCount(); i++) {
				if (((LogicGate*)pComp)->GetInputPin(i)->IsFull()) {
					returnValue = TestGate(((LogicGate*)pComp)->GetInputPin(i)->GetConnection(0)->GetSourcePin()->GetGate());
					if (returnValue > -1)
						((Gate*)pComp)->SetInputPinStatus(i, returnValue ? Status::HIGH : Status::LOW);
					else {
						visited.erase(pComp);
						return -1;
					}
				}
				else {
					stopSimulation = true;
					return -1;
				}
			}

			visited.erase(pComp);
			((LogicGate*)pComp)->Operate();
			return ((LogicGate*)pComp)->GetOutputPinStatus();

		}
	}
	else return 0;
}

/* Undo action */
void Simulate::Undo() {
	return;
}

/* Redo action */
void Simulate::Redo() {
	return;
}

/* Destructor */
Simulate::~Simulate() {

}