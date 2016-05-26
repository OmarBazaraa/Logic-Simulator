#include "ApplicationManager.h"
#include "Actions\AddGate.h"
#include "Actions\AddConnection.h"
#include "Actions\Edit.h"
#include "Actions\Delete.h"
#include "Actions\Copy.h"
#include "Actions\Cut.h"
#include "Actions\Paste.h"
#include "Actions\UndoAction.h"
#include "Actions\RedoAction.h"
#include "Actions\Simulate.h"
#include "Actions\TruthTable.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction.h"
#include "Actions\Select.h"
#include "Actions\Move.h"
#include "Actions\Hover.h"
#include "Actions\Exit.h"
using namespace std;

/* Constructor */
ApplicationManager::ApplicationManager() {
	mCompCount = 0;
	mCopiedComp = NULL;
	mCompList = new Component*[MAX_COMPONENTS];
	for (int i = 0; i < MAX_COMPONENTS; i++) mCompList[i] = NULL;

	// Creates the Input/Output objects and initialize the GUI
	pOut = new Output();
	pIn = pOut->CreateInput();
}

/* Returns the number of the existing components */
int ApplicationManager::GetExistingComponentsCount() const {
	int s = 0;
	for (int i = 0; i < mCompCount; i++)
		if (mCompList[i]->IsDeleted())
			s++;
	return mCompCount - s;
}

/* Sets the last copied/cut component */
void ApplicationManager::SetCopiedComp(Component* pComp) {
	mCopiedComp = pComp;
}

/* Returns the last copied/cut component */
Component* ApplicationManager::GetCopiedComp() const {
	return mCopiedComp;
}

/* Returns a pointer to Input object */
Input* ApplicationManager::GetInput() {
	return pIn;
}

/* Returns a pointer to Output object */
Output* ApplicationManager::GetOutput() {
	return pOut;
}

/* Reads the required action from the user and returns the corresponding action type */
ActionType ApplicationManager::GetUserAction() {
	return pIn->GetUserAction(pOut);
}

/* Creates an action and executes it */
void ApplicationManager::ExecuteAction(ActionType& actType) {
	Action* pAct = NULL;

	switch (actType) {
		case ADD_GATE_AND:
		case ADD_GATE_OR:
		case ADD_GATE_NOT:
		case ADD_GATE_NAND:
		case ADD_GATE_NOR:
		case ADD_GATE_XOR:
		case ADD_GATE_XNOR:
		case ADD_GATE_AND3:
		case ADD_GATE_NOR3:
		case ADD_GATE_XOR3:
		case ADD_GATE_BUFFER:
		case ADD_SWITCH:
		case ADD_LED:
			pAct = new AddGate(this, actType);
			break;
		case ADD_CONNECTION:
			pAct = new AddConnection(this);
			break;
		case EDIT:
			pAct = new Edit(this);
			break;
		case DEL:
			pAct = new Delete(this);
			break;
		case COPY:
			pAct = new Copy(this);
			break;
		case CUT:
			pAct = new Cut(this);
			break;
		case PASTE:
			pAct = new Paste(this);
			break;
		case UNDO:
			pAct = new UndoAction(this);
			break;
		case REDO:
			pAct = new RedoAction(this);
			break;
		case SIMULATION_MODE:
			UI.AppMode = Mode::SIMULATION;
			pOut->CreateToolBar();
			pOut->CreateGateBar();
			pAct = new Simulate(this);
			//pOut->PrintMsg("SIMULATION MODE");
			break;
		case DESIGN_MODE:
			UI.AppMode = Mode::DESIGN;
			pOut->CreateToolBar();
			pOut->CreateGateBar();
			//pOut->PrintMsg("DESIGN MODE");
			break;
		case CREATE_TRUTH_TABLE:
			pAct = new TruthTable(this);
			break;
		case SAVE:
			pAct = new SaveAction(this);
			break;
		case LOAD:
			pAct = new LoadAction(this);
			break;
		case SELECT:
			pAct = new Select(this);
			break;
		case MOVE:
			pAct = new Move(this);
			break;
		case HOVER:
			pAct = new Hover(this);
			break;
		case EXIT:
			pAct = new Exit(this);
			break;
		case TOOL_BAR:
			//pOut->PrintMsg("TOOL BAR");
			break;
		case GATE_BAR:
			//pOut->PrintMsg("GATE BAR");
			break;
		case STATUS_BAR:
			//pOut->PrintMsg("STATUS BAR");
			break;
	}

	if (pAct != NULL) {
		if (pAct->Execute()) {
			mUndoStack.push(pAct);
			while (!mRedoStack.empty()) delete mRedoStack.top(), mRedoStack.pop();	// Clear the RedoStack
		}
		else {
			if (actType == EXIT) actType = GATE_BAR;	// To cancel exit action
			delete pAct;
		}
	}
}

/* Redraws all the drawing window */
void ApplicationManager::UpdateInterface() {
	for (int i = 0; i < mCompCount; i++) mCompList[i]->Draw(pOut);
	//pOut->Debug();
	pOut->UpdateScreen();
}

/* Adds a new component to the list of components */
void ApplicationManager::AddComponent(Component* pComp) {
	if (mCompCount < MAX_COMPONENTS) {
		mCompList[mCompCount++] = pComp;
	}
}

/* Returns the number of the existing components */
int ApplicationManager::GetExistingComponentsCount() const {
	int n = 0;

	for (int i = 0; i < mCompCount; i++) {
		if (!mCompList[i]->IsDeleted()) {
			n++;
		}
	}

	return n;
}

/* Counts and returns the number of selected components */
int ApplicationManager::CountSelectedComponents() const {
	int n = 0;

	for (int i = 0; i < mCompCount; i++) {
		if (!mCompList[i]->IsDeleted() && mCompList[i]->IsSelected()) {
			n++;
		}
	}

	return n;
}

/* Sets a selection value to all components */
void ApplicationManager::SetSelectionOfComponents(bool s) {
	for (int i = 0; i < mCompCount; i++) {
		mCompList[i]->SetSelected(s);
	}
}

/* Returns a vector of all selected components */
vector<Component*> ApplicationManager::GetSelectedComponents() {
	vector<Component*> vec;

	for (int i = 0; i < mCompCount; i++) {
		if (!mCompList[i]->IsDeleted() && mCompList[i]->IsSelected()) {
			vec.push_back(mCompList[i]);
		}
	}

	return vec;
}

/* Returns a vector of all selected gates */
vector<Gate*> ApplicationManager::GetSelectedGates() {
	vector<Gate*> vec;

	for (int i = 0; i < mCompCount; i++) {
		Gate* ptr = dynamic_cast<Gate*>(mCompList[i]);

		if (ptr != NULL && !ptr->IsDeleted() && ptr->IsSelected()) {
			vec.push_back(ptr);
		}
	}

	return vec;
}

/* Returns a vector of all connections */
vector<Connection*> ApplicationManager::GetConnections() {
	vector<Connection*> vec;

	for (int i = 0; i < mCompCount; i++) {
		Connection* ptr = dynamic_cast<Connection*>(mCompList[i]);

		if (ptr != NULL && !ptr->IsDeleted()) {
			vec.push_back(ptr);
		}
	}

	return vec;
}

/* Returns a vector of all leds */
vector<LED*> ApplicationManager::GetLeds() {
	vector<LED*> vec;

	for (int i = 0; i < mCompCount; i++) {
		LED* ptr = dynamic_cast<LED*>(mCompList[i]);

		if (ptr != NULL && !ptr->IsDeleted()) {
			vec.push_back(ptr);
		}
	}

	return vec;
}

/* Returns a vector of all switches */
vector<Switch*> ApplicationManager::GetSwitches() {
	vector<Switch*> vec;

	for (int i = 0; i < mCompCount; i++) {
		Switch* ptr = dynamic_cast<Switch*>(mCompList[i]);

		if (ptr != NULL && !ptr->IsDeleted()) {
			vec.push_back(ptr);
		}
	}

	return vec;
}

/* Undoes the last action */
void ApplicationManager::Undo() {
	if (mUndoStack.empty()) {
		return;
	}

	Action* lastAction = mUndoStack.top();
	lastAction->Undo();

	mUndoStack.pop();
	mRedoStack.push(lastAction);
}

/* Redoes the last action */
void ApplicationManager::Redo() {
	if (mRedoStack.empty()) {
		return;
	}

	Action* lastAction = mRedoStack.top();
	lastAction->Redo();

	mRedoStack.pop();
	mUndoStack.push(lastAction);
}

/* Saves the current circuit */
void ApplicationManager::Save(ofstream& file) {
	for (int i = 0; i < mCompCount; i++) {
		if (!mCompList[i]->IsDeleted()) {
			mCompList[i]->Save(file);
		}
	}
}

/* Loads the circuit from the file */
void ApplicationManager::Load(ifstream& file) {
	Data compData;
	string compType;
	Action* pAct;

	while (file >> compType, compType != "-1") {
		if (file.eof()) {
			break;
		}

		if (compType == "CONNECTION") {
			file >> compData.Label;
			file >> compData.GfxInfo.x1 >> compData.GfxInfo.y1 >> compData.GfxInfo.x2 >> compData.GfxInfo.y2;
			pAct = new AddConnection(this, &compData);
		}
		else {
			file >> compData.Label;
			file >> compData.GfxInfo.x1 >> compData.GfxInfo.y1;

			if (compType == "AND")
				pAct = new AddGate(this, ADD_GATE_AND, &compData);
			else if (compType == "OR")
				pAct = new AddGate(this, ADD_GATE_OR, &compData);
			else if (compType == "NOT")
				pAct = new AddGate(this, ADD_GATE_NOT, &compData);
			else if (compType == "NAND")
				pAct = new AddGate(this, ADD_GATE_NAND, &compData);
			else if (compType == "NOR")
				pAct = new AddGate(this, ADD_GATE_NOR, &compData);
			else if (compType == "XOR")
				pAct = new AddGate(this, ADD_GATE_XOR, &compData);
			else if (compType == "XNOR")
				pAct = new AddGate(this, ADD_GATE_XNOR, &compData);
			else if (compType == "AND3")
				pAct = new AddGate(this, ADD_GATE_AND3, &compData);
			else if (compType == "NOR3")
				pAct = new AddGate(this, ADD_GATE_NOR3, &compData);
			else if (compType == "XOR3")
				pAct = new AddGate(this, ADD_GATE_XOR3, &compData);
			else if (compType == "BUFFER")
				pAct = new AddGate(this, ADD_GATE_BUFFER, &compData);
			else if (compType == "SWITCH")
				pAct = new AddGate(this, ADD_SWITCH, &compData);
			else if (compType == "LED")
				pAct = new AddGate(this, ADD_LED, &compData);
		}

		pAct->Execute();
		delete pAct;
	}
}

/* Releases all the memory used by the components */
void ApplicationManager::ReleaseMemory() {
	for (int i = 0; i < mCompCount; i++) {
		mCompList[i]->Delete(pOut);
		delete mCompList[i];
	}

	mCompCount = 0;
	mCopiedComp = NULL;
	for (int i = 0; i < MAX_COMPONENTS; i++) mCompList[i] = NULL;

	while (!mUndoStack.empty()) delete mUndoStack.top(), mUndoStack.pop();
	while (!mRedoStack.empty()) delete mRedoStack.top(), mRedoStack.pop();
}

/* Destructor */
ApplicationManager::~ApplicationManager() {
	while (!mUndoStack.empty()) delete mUndoStack.top(), mUndoStack.pop();
	while (!mRedoStack.empty()) delete mRedoStack.top(), mRedoStack.pop();

	for (int i = 0; i < mCompCount; i++) delete mCompList[i];
	delete[] mCompList;
	delete pIn;
	delete pOut;
}