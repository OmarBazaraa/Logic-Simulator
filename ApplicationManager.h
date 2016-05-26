#pragma once
#include "Utilities\Defs.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Components\Component.h"
#include "Components\Gate.h"
#include "Components\Connection.h"
#include "Components\Switch.h"
#include "Components\LED.h"
#include "Actions\Action.h"
#include <vector>
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
	void ExecuteAction(ActionType& actType);
	
	/* Redraws all the drawing window */
	void UpdateInterface();	

	/* Adds a new component to the list of components */
	void AddComponent(Component* pComp);

	/* Returns the number of the existing components */
	int GetExistingComponentsCount() const;

	/* Counts and returns the number of selected components */
	int CountSelectedComponents() const;

	/* Sets a selection value to all components */
	void SetSelectionOfComponents(bool s);

	/* Returns a vector of all selected components */
	vector<Component*> GetSelectedComponents();

	/* Returns a vector of all selected gates */
	vector<Gate*> GetSelectedGates();

	/* Returns a vector of all connections */
	vector<Connection*> GetConnections();

	/* Returns a vector of all leds */
	vector<LED*> GetLeds();

	/* Returns a vector of all switches */
	vector<Switch*> GetSwitches();

	/* Undoes the last action */
	void Undo();

	/* Redoes the last action */
	void Redo();

	/* Saves the current circuit */
	void Save(ofstream& file);

	/* Loads the circuit from the file */
	void Load(ifstream& file);

	/* Releases all the memory used by the components */
	void ReleaseMemory();

	/* Destructor */
	~ApplicationManager();
};