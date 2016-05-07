#include "Save.h"

/* Constructor */
Save::Save(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Save::ReadActionParameters() {
	return true;
}

/* Executes action */
bool Save::Execute() {
	int ComponentCount = mAppManager->GetComponentsCount();
	write.open("Data.txt");
	write.clear();
	Component**ComponentList = mAppManager->GetComponentList();
	write << ComponentCount << endl;
	for (int i = 0; i < ComponentCount; i++)
		if (!(ComponentList[i]->IsDeleted() || dynamic_cast<Connection*>(ComponentList[i])))
			ComponentList[i]->Save(write);
	write << "Connections\n";
	for (int i = 0; i < ComponentCount; i++)
		if (!ComponentList[i]->IsDeleted() && dynamic_cast<Connection*>(ComponentList[i]))
			ComponentList[i]->Save(write);
	write << "-1\n";
	
	return false;
}

/* Undo action */
void Save::Undo() {
	return;
}

/* Redo action */
void Save::Redo() {
	return;
}

/* Destructor */
Save::~Save() {

}
