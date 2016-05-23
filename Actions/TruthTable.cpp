#include "TruthTable.h"


/* Constructor */
TruthTable::TruthTable(ApplicationManager* pAppMan) : Action(pAppMan) {
	mSwitchesCount = 0;
	mLedsCount = 0;
	mWrite.open("TruthTable.txt");
	mWrite.clear();	
	mCanDraw = true;
}

/* Reads parameters required for action to execute */
bool TruthTable::ReadActionParameters() {
	mRows = pow(2, mSwitchesCount);
	mColumns = mLedsCount + mSwitchesCount;
	return (mSwitchesCount < 6 && mColumns < 12);
}

/* Executes action */
bool TruthTable::Execute() {
	Populate();
	if (ReadActionParameters())
		DrawWindow();
	else
		mCanDraw = false;
	DrawHeaders();
	CreateCompinations("");
	ReturnToDefault();
	Exits();
	return false;
}

/* Undo action */
void TruthTable::Undo() {
	return;
}

/* Redo action */
void TruthTable::Redo() {
	return;
}


TruthTable::~TruthTable() {
	delete pWind;
}

/* Populates */
void TruthTable::Populate() {
	Component ** list = mAppManager->GetComponentList();
	int count = mAppManager->GetComponentsCount();
	mLeds = new LED*[count];
	mSwitches = new Switch*[count];
	mSwitchesDefault = new int[count];
	for (int i = 0; i < count; i++) {
		if (dynamic_cast<LED*>(list[i]) && !list[i]->IsDeleted()) {
			mLeds[mLedsCount++] = (LED*)list[i];
		}
		else if (dynamic_cast<Switch*>(list[i]) && !list[i]->IsDeleted()) {
			mSwitches[mSwitchesCount] = (Switch*)list[i];
			mSwitchesDefault[mSwitchesCount++] = list[i]->GetOutputPinStatus();
		}
	}
}

/* Draws truth table window */
void TruthTable::DrawWindow() {
	pWind = CreateWind(mColumns * 100 + 230, mRows * 20 + 80, UI.StartX, UI.StartY);
	ChangeTitle("Truth Table");
	ClearDrawingArea();
	DrawTruthTable();
	Hover(true);
}

/* Creates a new Window object */
window* TruthTable::CreateWind(int w, int h, int x, int y) const {
	return new window(w, h, x, y);
}

/* Chnages the title of the Window */
void TruthTable::ChangeTitle(const string& title) const {
	pWind->ChangeTitle(title);
}

/* Clears the drawing area */
void TruthTable::ClearDrawingArea() const {
	pWind->SetPen(UI.DarkColor);
	pWind->SetBrush(UI.DarkColor);
	pWind->DrawRectangle(0, 0, UI.Width, UI.Height);
}

/*Draws truth table*/
void TruthTable::DrawTruthTable() const {
	// Vertical lines
	pWind->SetPen(BLACK);
	for (int x = 0; x <= (mColumns + 1) * 100; x += 100) {
		pWind->DrawLine(x, 20, x, (2 + mRows) * 20);
	}

	// Horizontal lines
	for (int y = 0; y <= (2 + mRows) * 20; y += 20) {
		pWind->DrawLine(100, y, (1 + mColumns) * 100, y);
	}
}

/* Hovers */
void TruthTable::Hover(bool stopHovering) {
	pWind->SetFont(40, BOLD, BY_NAME, "Arial");
	if (stopHovering)
		pWind->SetPen(WHITE);
	else
		pWind->SetPen(RED);
	DrawExit();
}

/* Draws exit button */
void TruthTable::DrawExit() const {
	pWind->DrawString(mColumns * 100 + 190, 0, "x");
}

/* Draw headers */
void TruthTable::DrawHeaders() {
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(UI.FontSize, BOLD, BY_NAME, "Arial");
	string msg = "header";
	int n = mSwitchesCount;
	int count = 0;

	for (int i = 100; i <= mColumns * 100; i += 100) {
		if (i / 100 <= n)
			msg = mSwitches[i / 100 - 1]->GetLabel();
		else
			msg = mLeds[count++]->GetLabel();
		Normalizetxt(msg);
		int w, h;
		pWind->GetStringSize(w, h, msg);
		if (mCanDraw)
			pWind->DrawString(i +(100-w)/2, 20, msg);
		mWrite << msg << "   ";
	}
	mWrite << endl;
}

/* Normalize message position */
void TruthTable::Normalizetxt(string& msg) {
	string temp = "";
	int l = msg.length();
	for (int i = 0; i<8 && i < l; i++)
		temp += msg[i];
	if (l > 8)
		temp[7] = '-';
	msg = temp;
}

/*Create Compinations */
void TruthTable::CreateCompinations(string compination) {
	if (compination.length() == mSwitchesCount) { Test(compination); return; }
	CreateCompinations(compination + '0');
	CreateCompinations(compination + '1');
}

/* Test input */
void TruthTable::Test(string compination) {
	int pos = ToInt(compination) * 20 + 40;
	string status;
	for (int i = 0; i < mSwitchesCount; i++) {
		mSwitches[i]->GetOutputPin()->SetStatus(Status(compination[i] - '0'));
		status = compination[i];
		if (mCanDraw)pWind->DrawString((i + 1) * 100 + 45, pos, status);
		mWrite << "   " << status << "       ";
	}
	for (int i = 0; i < mLedsCount; i++) {
		status = "";
		status += ('0' + TestGate(mLeds[i]));
		if (status[0] - '0')pWind->SetPen(GREEN);
		else pWind->SetPen(RED);
		if (mCanDraw)pWind->DrawString((i + 1) * 100 + 45 + mSwitchesCount * 100, pos, status);
		mWrite << "   " << status << "       ";
		pWind->SetPen(WHITE);
	}
	mWrite << endl;
}

int TruthTable::ToInt(string k) {
	int x = 0;
	for (int i = 0; i < k.length(); i++)
		x += (k[i] - '0')*(int)pow(2, k.length() - 1 - i);
	return x;
}

/* Tests the output on a led */
int TruthTable::TestGate(Component*pComp) {

	int returnValue;

	if (pComp != NULL) {
		if (dynamic_cast<Switch*>(pComp)) {
			return pComp->GetOutputPinStatus();
		}
		else if (dynamic_cast<LED*>(pComp)) {
			returnValue = TestGate(((LED*)pComp)->GetInputPin(0)->GetConnection(0)->GetSourcePin()->GetGate());
			((LED*)pComp)->SetInputPinStatus(0, returnValue ? Status::HIGH : Status::LOW);
			return returnValue;
		}
		else if (dynamic_cast<LogicGate*>(pComp)) {

			for (int i = 0; i<((LogicGate*)pComp)->GetInputsCount(); i++) {
				returnValue = TestGate(((LogicGate*)pComp)->GetInputPin(i)->GetConnection(0)->GetSourcePin()->GetGate());
				((Gate*)pComp)->SetInputPinStatus(i, returnValue ? Status::HIGH : Status::LOW);
			}

			((LogicGate*)pComp)->Operate();
			return ((LogicGate*)pComp)->GetOutputPinStatus();

		}
	}
	else return 0;
}

/* Returns switches status to default */
void TruthTable::ReturnToDefault() {
	for (int i = 0; i<mSwitchesCount; i++) {
		mSwitches[i]->GetOutputPin()->SetStatus((Status)mSwitchesDefault[i]);
	}
	for (int i = 0; i < mLedsCount; i++) {
		TestGate(mLeds[i]);
	}
}

/* Exits Truth Table */
void TruthTable::Exits() {
	int x=0, y=0;
	bool isHovering = 0;
	while(!IsButton(x, y))
		while (pWind->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_UP) {
			if (IsButton(x, y)) {
				if (!isHovering)
					Hover(false);
				isHovering = true;
			}
			else {
				if (isHovering)
					Hover(true);
				isHovering = false;
			}
		}
}

/* detects if the value of those coordinates */
bool TruthTable::IsButton(int x,int y) {
	return (y < 30 && y > 0 && x > mColumns * 100 + 190 && x < mColumns * 100 + 210);
}
