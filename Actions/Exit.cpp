#include "Exit.h"

/* Constructor */
Exit::Exit(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Exit::ReadActionParameters() {
	ifstream originalFile, backUpFile;
	
	originalFile.open("Data.txt");
	backUpFile.open("BackUp.txt");

	if (!originalFile.is_open() || !backUpFile.is_open()) {
		return true;
	}

	string s1, s2;

	while (!originalFile.eof() && !backUpFile.eof()) {
		std::getline(originalFile, s1);
		std::getline(backUpFile, s2);

		if (s1 != s2) {
			originalFile.close();
			backUpFile.close();
			return true;
		}

	}
	originalFile.close();
	backUpFile.close();

	return false;
}

/* Executes action */
bool Exit::Execute() {
	mWrite.open("BackUp.txt");
	mWrite.clear();
	mAppManager->Save(mWrite);
	mWrite << "-1\n";
	mWrite.close();

	if (ReadActionParameters()){
		Dialog dialog("Would you like to save before exiting?");

		DialogBoxButton cType = dialog.GetUserClick();

		if (cType == DialogBoxButton::YES) {
			Action*	pAct = new SaveAction(this->mAppManager);
			pAct->Execute();
			delete pAct;
		}
		else if (cType == DialogBoxButton::CANCEL) {
			return false;
		}
	}

	return true;
}

/* Undo action */
void Exit::Undo() {
	return;
}

/* Redo action */
void Exit::Redo() {
	return;
}

/* Destructor */
Exit::~Exit() {
	mWrite.close();
}