#include "ApplicationManager.h"

int main() {
	ActionType ActType;
	ApplicationManager AppManager;

	do {		
		// Read user action
		ActType = AppManager.GetUserAction();

		// Exexute the action
		AppManager.ExecuteAction(ActType);

		// Update the drawing window
		AppManager.UpdateInterface();

	} while (ActType != EXIT);
		
	return 0;
}