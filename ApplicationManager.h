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
	Component* mCopiedComp;		// Pointer to the last copied/cut component
	stack<Action*> mUndoStack;	// Stack holding the done actions
	stack<Action*> mRedoStack;	// Stack holding the un-done actions
	Input* pIn;					// Pointer to the Input class
	Output* pOut;				// Pointer to the Output class

public:
	/* Constructor */
	ApplicationManager();

	/* Returns the number of the components */
	int GetComponentsCount() const;

	/* Returns the list of components */
	Component** GetComponentList() const;

	/* Sets the last copied/cut component */
	void SetCopiedComp(Component* pComp);

	/* Returns the last copied/cut component */
	Component* GetCopiedComp() const;

	/* Returns a pointer to Input object */
	Input* GetInput();

	/* Returns a pointer to Output object */
	Output* GetOutput();

	/* Reads the required action from the user and returns the corresponding action type */
	ActionType GetUserAction();
	
	/* Creates an action and executes it */
	void ExecuteAction(ActionType &actType);
	
	/* Redraws all the drawing window */
	void UpdateInterface();	

	/* Adds a new component to the list of components */
	void AddComponent(Component* pComp);

	/* Deselects all the components */
	void DeselectComponents();

	/* Counts and returns the number of selected components */
	int CountSelectedComponents();

	/* Undoes the last action */
	void Undo();

	/* Redoes the last action */
	void Redo();

	/* Frees Memory */
	void FreeMemory();

	/* Destructor */
	~ApplicationManager();
};