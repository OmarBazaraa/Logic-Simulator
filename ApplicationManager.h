#pragma once
#include "Utilities\Defs.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Components\Component.h"
#include "Actions\Action.h"
#include <stack>

/*
	Main class that manages everything in the application
*/
class ApplicationManager
{
private:
	int mCompCount;				// Actual number of components
	Component** mCompList;		// List of all components
	Input* pIn;					// Pointer to the Input class
	Output* pOut;				// Pointer to the Output class
	stack<Action*> mUndoStack;	// Stack holding the done actions
	stack<Action*> mRedoStack;	// Stack holding the un-done actions

public:
	/* Constructor */
	ApplicationManager();

	/* Returns the number of the components */
	int GetComponentsCount() const;

	/* Returns the list of components */
	Component** GetComponentList() const;

	/* Returns a pointer to Input object */
	Input* GetInput();

	/* Returns a pointer to Output object */
	Output* GetOutput();

	/* Returns the stack of done actions */
	stack<Action*>* GetUndoStack();

	/* Returns the stack of un-done actions */
	stack<Action*>* GetRedoStack();

	/* Reads the required action from the user and returns the corresponding action type */
	ActionType GetUserAction();
	
	/* Creates an action and executes it */
	void ExecuteAction(ActionType actType);
	
	/* Redraws all the drawing window */
	void UpdateInterface();	

	/* Adds a new component to the list of components */
	void AddComponent(Component* pComp);

	/* Destructor */
	~ApplicationManager();
};