#include "ApplicationManager.h"

int main() {
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") 
	
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