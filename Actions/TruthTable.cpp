#include "TruthTable.h"
#include "queue"

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
	if (mWrite.is_open()) {
		Populate();
		if (ReadActionParameters())
			DrawWindow();
		else
			mCanDraw = false;
		DrawHeaders();
		CreateCompinations("");
		ReturnToDefault();
		Exits();
	}
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
	if (mWrite.is_open())
		mWrite.close();
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
	pWind = new window(mColumns * UI.Column + 2 * UI.TruthTableMargin + UI.ExitMargin + UI.Exit,
		UI.Row * (1 + mRows) + 3 * UI.TruthTableMargin,
		(UI.Width - mColumns * UI.Column + 2 * UI.TruthTableMargin + UI.ExitMargin + UI.Exit) / 2,
		(UI.Height -(1+ mRows) * UI.Row + 3 * UI.TruthTableMargin) / 2);
	pWind->ChangeTitle("");
	ClearDrawingArea();
	DrawTruthTable();
	Hover(true);
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
	for (int x = 0; x < (mColumns + 1) * UI.Column; x += UI.Column) {
		pWind->DrawLine(x + UI.Row, UI.Row, x + UI.Row, (2 + mRows) * UI.Row);
	}

	// Horizontal lines
	for (int y = UI.Row; y <= (2 + mRows) * UI.Row; y += UI.Row) {
		pWind->DrawLine(UI.Row, y, mColumns * UI.Column + UI.Row, y);
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
	pWind->DrawString(mColumns * UI.Column + UI.TruthTableMargin + UI.ExitMargin, 0, "x");
}

/* Draws headers */
void TruthTable::DrawHeaders() {
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(UI.FontSize, BOLD, BY_NAME, "Arial");
	string msg = "header";
	int n = mSwitchesCount;
	int count = 0;

	for (int i = UI.TruthTableMargin; i < mColumns * UI.Column; i += UI.Column) {
		if (i / UI.Column < n)
			msg = mSwitches[i / UI.Column]->GetLabel();
		else
			msg = mLeds[count++]->GetLabel();
		Normalizetxt(msg);
		int w, h;
		pWind->GetStringSize(w, h, msg);
		if (mCanDraw)
			pWind->DrawString(i + (UI.Column - w) / 2 , UI.TruthTableMargin, msg);
		mWrite << msg << "   ";
	}
	mWrite << endl;
}

/* Normalizes message to fit */
void TruthTable::Normalizetxt(string& msg) {
	string temp = "";
	int l = msg.length();
	for (int i = 0; i < 8 && i < l; i++)
		temp += msg[i];
	if (l > 8)
		temp[6] = temp[7] = '.';
	msg = temp;
}

/* Creates all possible compinations of inputs on switches */
void TruthTable::CreateCompinations(string compination) {
	if (compination.length() == mSwitchesCount) { Test(compination); return; }
	CreateCompinations(compination + '0');
	CreateCompinations(compination + '1');
}

/* Tests input */
void TruthTable::Test(string compination) {
	int pos = (1 + ToInt(compination)) * UI.Row + UI.TruthTableMargin;
	string status;
	queue<Component*>q;
	if (compination[mSwitchesCount - 1] == '0')pWind->SetPen(UI.BackgroundColor);
	else pWind->SetPen(WHITE);
	for (int i = 0; i < mSwitchesCount; i++) {
		mSwitches[i]->GetOutputPin()->SetStatus(Status(compination[i] - '0') == HIGH ? LOW : HIGH);
		status = compination[i];
		q.push(mSwitches[i]);

		if (mCanDraw)pWind->DrawString(i * UI.Column + UI.TruthTableMargin + UI.StatusMargin, pos, status);
		mWrite << "   " << status << "       ";
	}
	Cascade(q);
	for (int i = 0; i < mLedsCount; i++) {
		status = "";
		status += ('0' + mLeds[i]->GetInputPinStatus(0));
		/*if (status[0] - '0') {
			if (compination[mSwitchesCount - 1] == '0')
				pWind->SetPen(((color)(DARKGREEN)));
			else
				pWind->SetPen(((color)(GREEN)));
		}
		else { 
			if (compination[mSwitchesCount - 1] == '0')				
				pWind->SetPen(((color)(111)));
			else 
				pWind->SetPen(((color)(250)));
		}*/

		if (mCanDraw)pWind->DrawString(i * UI.Column + UI.TruthTableMargin + UI.StatusMargin + mSwitchesCount * UI.Column, pos, status);
		mWrite << "   " << status << "       ";
	}
	mWrite << endl;
}

/* Cascades */
void TruthTable::Cascade(queue<Component*>qComp) {
	while (!qComp.empty()) {
		qComp.front()->Operate();
		int n = qComp.front()->GetConnectedCount();
		for (int i = 0; i < n; i++)
			qComp.push(qComp.front()->GetNextComponent(i));
		qComp.pop();
	}
}

/* Changes string to int */
int TruthTable::ToInt(string k) {
	int x = 0, n = k.length();
	for (int i = 0; i < n; i++)
		x += (k[i] - '0')*(int)pow(2, k.length() - 1 - i);
	return x;
}

/* Returns switches status to default */
void TruthTable::ReturnToDefault() {
	queue<Component*>q;
	for (int i = 0; i<mSwitchesCount; i++) {
		mSwitches[i]->GetOutputPin()->SetStatus((Status)mSwitchesDefault[i]);
		q.push(mSwitches[i]);
	}
	Cascade(q);
}

/* Exits Truth Table */
void TruthTable::Exits() {
	int x=0, y=0;
	bool isHovering = 0;
	while (!IsButton(x, y)) {
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

}

/* Checks if the value of coordinates is on exit button */
bool TruthTable::IsButton(int x,int y) {
	return (y < UI.ExitMargin + UI.Exit && y > 0 
		&& x > mColumns * UI.Column + UI.TruthTableMargin + UI.ExitMargin 
		&& x < mColumns * UI.Column + UI.TruthTableMargin * 2 + UI.ExitMargin);
}
