#include "Simulate.h"

/* Constructor */
Simulate::Simulate(ApplicationManager* pAppMan) : Action(pAppMan) {
	mStopSimulation = false;
}

/* Reads parameters required for action to execute */
bool Simulate::ReadActionParameters() {
	return true;
}

/* Executes action */
bool Simulate::Execute() {

	mAppManager->SetSelectionOfComponents(false);

	int count = mAppManager->GetExistingComponentsCount();

	vector<LED*>pLeds = mAppManager->GetLeds();
	int n = pLeds.size();
	
	for (int i = 0; i < n; i++) {
		Cascade(pLeds[i]);
		mVisited.clear();
	}	

	if (mStopSimulation || mCircuit.size() < count || count == 0) {
		ActionType act = ActionType::DESIGN_MODE;

		Dialog dialog("Circuit is not valid. Cannot start simulation.", Type_C);
		dialog.GetUserClick();

		mAppManager->ExecuteAction(act);
	}
	
	return false;
}

/* Tests the output on a led */
int Simulate::Cascade(Component* pComp) {
	//validation

	int n = mVisited.size();
	if (pComp != NULL) {
		mCircuit.insert(pComp);
		mVisited.insert(pComp);
	}
	else
		return -1;

	// Detects inner feedback
	if (n == mVisited.size()) {
		mStopSimulation = true;
		return -1;
	}

	int returnValue;

	if (pComp != NULL) {
		if (dynamic_cast<Switch*>(pComp)) {
			mVisited.erase(pComp);
			return pComp->GetOutputPinStatus();
		}
		else if (dynamic_cast<LED*>(pComp)) {
			if (((LED*)pComp)->GetInputPin(0)->IsFull()) {
				mCircuit.insert(((LED*)pComp)->GetInputPin(0)->GetConnection(0));
				returnValue = Cascade(((LED*)pComp)->GetInputPin(0)->GetConnection(0)->GetSourcePin()->GetGate());
			}
			else { 
				returnValue = -1;
				mStopSimulation = true;
			}
			if (returnValue > -1)
				((LED*)pComp)->SetInputPinStatus(0, returnValue ? Status::HIGH : Status::LOW);
			return returnValue;
		}
		else if (dynamic_cast<LogicGate*>(pComp)) {

			for (int i = 0; i<((LogicGate*)pComp)->GetInputsCount(); i++) {
				if (((LogicGate*)pComp)->GetInputPin(i)->IsFull()) {
					mCircuit.insert(((LED*)pComp)->GetInputPin(i)->GetConnection(0));
					returnValue = Cascade(((LogicGate*)pComp)->GetInputPin(i)->GetConnection(0)->GetSourcePin()->GetGate());
					if (returnValue > -1)
						((Gate*)pComp)->SetInputPinStatus(i, returnValue ? Status::HIGH : Status::LOW);
					else {
						mVisited.erase(pComp);
						return -1;
					}
				}
				else {
					mStopSimulation = true;
					return -1;
				}
			}

			mVisited.erase(pComp);
			((LogicGate*)pComp)->Operate();
			return ((LogicGate*)pComp)->GetOutputPinStatus();

		}
	}

	return false;
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