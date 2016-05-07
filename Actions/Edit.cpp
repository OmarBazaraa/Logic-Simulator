#include "Edit.h"
#include "..\Components\AND.h"
#include "..\Components\AND3.h"
#include "..\Components\Buffer.h"
#include "..\Components\NAND.h"
#include "..\Components\NOR.h"
#include "..\Components\NOR3.h"
#include "..\Components\NOT.h"
#include "..\Components\OR.h"
#include "..\Components\Switch.h"
#include "..\Components\XNOR.h"
#include "..\Components\XOR.h"
#include "..\Components\XOR3.h"
#include "..\Components\Connection.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"

/* Constructor */
Edit::Edit(ApplicationManager* pAppMan) : Action(pAppMan) {

}

/* Reads parameters required for action to execute */
bool Edit::ReadActionParameters() {
	Input* pIn = mAppManager->GetInput();
	Output* pOut = mAppManager->GetOutput();

	pOut->PrintMsg("Please select a component to edit");
	pIn->GetPointClicked(mX, mY);
	pOut->ClearStatusBar();

	if (!pOut->IsDrawingArea(mY)) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	mComp = pOut->GetComponentAtPin(mX, mY);

	if (mComp == NULL) {
		pOut->PrintMsg("Invalid position. Operation was cancelled");
		return false;
	}

	mPrvLabel = mComp->GetLabel();
	mNewLabel = pIn->GetSrting(pOut, "Please enter a new label:", mPrvLabel);
	pOut->ClearStatusBar();

	if (mNewLabel.empty() || mNewLabel == mPrvLabel) {
		return false;
	}

	return true;
}

/* Executes action */
bool Edit::Execute() {
	/*int count = mAppManager->GetComponentsCount();
	Component** compList = mAppManager->GetComponentList();

	for (int i = 0; i < count; i++) {
		if (compList[i]->IsSelected()) {
			Connection * ptr = dynamic_cast <Connection *> (compList[i]);
			if (ptr != NULL) {
				string Msg = "1- Edit the label.  2-Edit the Path. Connection ID ";
				Msg += (compList[i]->GetID() + '0');
				string s = mAppManager->GetInput()->GetSrting(mAppManager->GetOutput(), Msg + " : ");
				if (s.size() == 2 && s[0] == '1') {
					mAppManager->GetOutput()->ClearStatusBar();
					string s = mAppManager->GetInput()->GetSrting(mAppManager->GetOutput(), "Please enter the new label for the connection : ");
					if (!s.empty())
						compList[i]->SetLabel(s);
					mAppManager->GetOutput()->ClearStatusBar();
				}
				else if (s.size() == 2 && s[0] == '2') {
					Input* pIn = mAppManager->GetInput();
					Output* pOut = mAppManager->GetOutput();
					GraphicsInfo GfxInfo;
					vector <GraphicsInfo>* Path;

					mAppManager->GetOutput()->ClearConnectionPins(*ptr->GetPath());
					compList[i]->SetDeleted(true);
					mAppManager->UpdateInterface();

					pOut->PrintMsg("Connection: select the source pin");
					pIn->GetPointClicked(GfxInfo.x1, GfxInfo.y1);
					pOut->ClearStatusBar();

					if (!pOut->IsDrawingArea(GfxInfo.y1)) {
						pOut->PrintMsg("Invalid position. Operation was cancelled");
						continue;
					}

					if (!DetectSourceComponent(GfxInfo)) {
						pOut->PrintMsg("Invalid source pin. Operation was cancelled");
						continue;
					}

					pOut->PrintMsg("Connection: select the destination pin");
					pIn->GetPointClicked(GfxInfo.x2, GfxInfo.y2);
					pOut->ClearStatusBar();

					if (!pOut->IsDrawingArea(GfxInfo.y2)) {
						pOut->PrintMsg("Invalid position. Operation was cancelled");
						continue;
					}

					if (!DetectDestinationComponent(GfxInfo)) {
						pOut->PrintMsg("Invalid destination pin. Operation was cancelled");
						continue;
					}

					Path = pOut->GetConnectionPath(GfxInfo);

					if (Path == NULL) {
						pOut->PrintMsg("There is no available path. Operation was cancelled");
						continue;
					}
					ptr->SetPath(Path);
					ptr->SetGraphicsInfo(GfxInfo);
					mAppManager->GetOutput()->MarkConnectionPins(*Path, ptr);
					compList[i]->SetDeleted(false);
					mAppManager->UpdateInterface();
				}
				else {
					mAppManager->GetOutput()->ClearStatusBar();
					mAppManager->GetOutput()->PrintMsg("Invalid number cancelling the operation");
				}
			}
			else {
				mAppManager->GetOutput()->ClearStatusBar();
				string s = mAppManager->GetInput()->GetSrting(mAppManager->GetOutput(), "Please enter the new label for the component : " + GetComponentName(compList[i]) + " : ");
				if (!s.empty())
					compList[i]->SetLabel(s);
				mAppManager->GetOutput()->ClearStatusBar();
			}
		}
	}*/

	if (!ReadActionParameters()) {
		return false;
	}

	mComp->SetLabel(mNewLabel);

	return true;
}

/* Undo action */
void Edit::Undo() {
	mComp->SetLabel(mPrvLabel);
}

/* Redo action */
void Edit::Redo() {
	mComp->SetLabel(mNewLabel);
}

/*Destructor*/
Edit::~Edit() {

}

/* Detects the source component of the connection */
bool Edit::DetectSourceComponent(GraphicsInfo &GfxInfo) {
	Component* SrcComp = mAppManager->GetOutput()->GetComponentAtPin(GfxInfo.x1, GfxInfo.y1);

	if (SrcComp == NULL) {
		return false;
	}

	return true;
}

/* Detects the destination component of the connection */
bool Edit::DetectDestinationComponent(GraphicsInfo &GfxInfo) {
	Component* DstComp = mAppManager->GetOutput()->GetComponentAtPin(GfxInfo.x1, GfxInfo.y1);

	if (DstComp == NULL) {
		return false;
	}

	return true;
}

string Edit::GetComponentName(Component* comp) {
	string name;
	Action * pAct = NULL;
	LogicGate * ptr = dynamic_cast <LogicGate *> (comp);
	if (ptr != NULL) {
		if (dynamic_cast <AND *> (comp))
			name = "And";
		else if (dynamic_cast <AND3 *> (comp))
			name = "And3";
		else if (dynamic_cast <Buffer *> (comp))
			name = "Buffer";
		else if (dynamic_cast <NAND *> (comp))
			name = "Nand";
		else if (dynamic_cast <NOR *> (comp))
			name = "Nor";
		else if (dynamic_cast <NOR3 *> (comp))
			name = "Nor3";
		else if (dynamic_cast <NOT *> (comp))
			name = "Not";
		else if (dynamic_cast <OR *> (comp))
			name = "Or";
		else if (dynamic_cast <Switch *> (comp))
			name = "Switch";
		else if (dynamic_cast <XNOR *> (comp))
			name = "Xnor";
		else if (dynamic_cast <XOR *> (comp))
			name = "Xor";
		else if (dynamic_cast <XOR3 *> (comp))
			name = "Xor3";
	}
	else if (dynamic_cast <Switch *> (comp))
		name = "Switch";
	else if (dynamic_cast <LED *> (comp))
		name = "Led";
	name += " With ID ";
	name += (comp->GetID() + '0');
	return name;
}