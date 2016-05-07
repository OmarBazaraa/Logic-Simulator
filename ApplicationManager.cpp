#include "ApplicationManager.h"
#include "Actions\AddGate.h"
#include "Actions\AddConnection.h"
#include "Actions\Select.h"
#include "Actions\Save.h"
#include "Actions\TruthTable.h"
#include "Actions\Copy.h"
#include "Actions\Cut.h"
#include "Actions\Delete.h"
#include "Actions\Paste.h"
#include "Actions\Edit.h"
#include "Actions\UndoAction.h"
#include "Actions\RedoAction.h"

/* Constructor */
ApplicationManager::ApplicationManager() {
	mCompCount = 0;
	mCompList = new Component*[MAX_COMPONENTS];
	for (int i = 0; i < MAX_COMPONENTS; i++) mCompList[i] = NULL;

	// Creates the Input/Output objects and initialize the GUI
	pOut = new Output();
	pIn = pOut->CreateInput();
}

/* Get the number of components */
int ApplicationManager::GetComponentsCount() const {
	return mCompCount;
}

/* Get the list of components */
Component** ApplicationManager::GetComponentList() const {
	return mCompList;
}

/* Returns a pointer to Input object */
Input* ApplicationManager::GetInput() {
	return pIn;
}

/* Returns a pointer to Output object */
Output* ApplicationManager::GetOutput() {
	return pOut;
}

/* Returns the stack of done actions */
stack<Action*>* ApplicationManager::GetUndoStack() {
	return &mUndoStack;
}

/* Returns the stack of un-done actions */
stack<Action*>* ApplicationManager::GetRedoStack() {
	return &mRedoStack;
}

/* Reads the required action from the user and returns the corresponding action type */
ActionType ApplicationManager::GetUserAction() {
	return pIn->GetUserAction(); 	
}

/* Creates an action and executes it */
void ApplicationManager::ExecuteAction(ActionType actType) {
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
			pOut->PrintMsg("SIMULATION MODE");
			UI.AppMode = Mode::SIMULATION;
			pOut->CreateToolBar();
			//TODO:
			break;
		case DESIGN_MODE:
			pOut->PrintMsg("DESIGN MODE");
			UI.AppMode = Mode::DESIGN;
			pOut->CreateToolBar();
			//TODO:
			break;
		case CREATE_TRUTH_TABLE:
			pAct = new TruthTable(this);
			break;
		case SAVE:
			pAct = new Save(this);
			pOut->PrintMsg("Saved");
			break;
		case LOAD:
			pOut->PrintMsg("LOAD");
			//TODO:
			break;
		case EXIT:
			pOut->PrintMsg("EXIT");
			//TODO: create ExitAction here
			break;
		case TOOL_BAR:
			pOut->PrintMsg("TOOL BAR");
			//TODO:
			break;
		case GATE_BAR:
			pOut->PrintMsg("GATE BAR");
			//TODO:
			break;
		case SELECT:
			pAct = new Select(this);
			break;
		case STATUS_BAR:
			pOut->PrintMsg("STATUS BAR");
			//TODO:
			break;
	}

	if(pAct && pAct->Execute()) {
		mUndoStack.push(pAct);

		// Clear the RedoStack
		while (!mRedoStack.empty()) delete mRedoStack.top(), mRedoStack.pop();
	}
}

/* Redraws all the drawing window */
void ApplicationManager::UpdateInterface() {
	for (int i = 0; i < mCompCount; i++) mCompList[i]->Draw(pOut);
}

/* Adds a new component to the list of components */
void ApplicationManager::AddComponent(Component* pComp) {
	if (mCompCount < MAX_COMPONENTS) {
		mCompList[mCompCount++] = pComp;
	}
}

/* Destructor */
ApplicationManager::~ApplicationManager() {
	for (int i = 0; i < mCompCount; i++) delete mCompList[i];
	delete[] mCompList;
	delete pIn;
	delete pOut;

	while (!mUndoStack.empty()) delete mUndoStack.top(), mUndoStack.pop();
	while (!mRedoStack.empty()) delete mRedoStack.top(), mRedoStack.pop();
}