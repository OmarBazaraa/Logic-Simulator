#include "Delete.h"

/* Constructor */
Delete::Delete(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Delete::ReadActionParameters() {
	mDeletedComps = mAppManager->GetSelectedComponents();

	return (!mDeletedComps.empty());
}

/* Executes action */
bool Delete::Execute() {
	if (!ReadActionParameters()) {
		return false;
	}

	Output* pOut = mAppManager->GetOutput();

	// Delete selected components
	for (int i = 0; i < mDeletedComps.size(); i++) {
		mDeletedComps[i]->Delete(pOut);
	}

	// Update the path of all connections
	mConnections = mAppManager->GetConnections();
	for (int i = 0; i < mConnections.size(); i++) pOut->ClearConnectionPins(mConnections[i]->GetPath());
	for (int i = 0; i < mConnections.size(); i++) mConnections[i]->UpdatePath(pOut);

	pOut->ClearDrawingArea();
	pOut->PrintMsg("Deleted");
	return true;
}

/* Undo action */
void Delete::Undo() {
	Output* pOut = mAppManager->GetOutput();

	vector<Connection*> connections = mAppManager->GetConnections();

	// Clear all connections
	for (int i = 0; i < connections.size(); i++) pOut->ClearConnectionPins(connections[i]->GetPath());

	// Restore deleted components
	for (int i = 0; i < (int)mDeletedComps.size(); i++) {
		mDeletedComps[i]->Restore(pOut);
	}

	// Update the path of all connections
	for (int i = 0; i < connections.size(); i++) connections[i]->UpdatePath(pOut);

	pOut->ClearDrawingArea();
}

/* Redo action */
void Delete::Redo() {
	Output* pOut = mAppManager->GetOutput();

	// Delete selected components
	for (int i = 0; i < (int)mDeletedComps.size(); i++) {
		mDeletedComps[i]->Delete(pOut);
	}

	// Update the path of all connections
	for (int i = 0; i < mConnections.size(); i++) pOut->ClearConnectionPins(mConnections[i]->GetPath());
	for (int i = 0; i < mConnections.size(); i++) mConnections[i]->UpdatePath(pOut);

	pOut->ClearDrawingArea();
}

/* Destructor */
Delete::~Delete() {

}