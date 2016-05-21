#include "TruthTable.h"


/* Constructor */
TruthTable::TruthTable(ApplicationManager* pAppMan) : Action(pAppMan) {
	switchesCount = 0;
	ledsCount = 0;
	write.open("TruthTable.txt");
	write.clear();
	// Create and initialize the drawing window
	pWind = CreateWind(UI.Width, UI.Height, UI.StartX, UI.StartY);
	ChangeTitle("Truth Table");
	ClearDrawingArea();
	canDraw = 1;
}

/* Creates a new Window object */
window* TruthTable::CreateWind(int w, int h, int x, int y) const {
	// The additional width & height is due to a strange error in the graphics
	// library which doesn't create the Window with the exact given dimensions
	return new window(w, h, x, y);
}

/* Chnages the title of the Window */
void TruthTable::ChangeTitle(const string& title) const {
	pWind->ChangeTitle(title);
}

/* Clears the drawing area */
void TruthTable::ClearDrawingArea() const {
	pWind->SetPen(BACKGROUND_BLUE);
	pWind->SetBrush(BACKGROUND_BLUE);
	pWind->DrawRectangle(0, 0, UI.Width, UI.Height);

}

/*Draws truth table*/
void TruthTable::DrawTruthTable() const {
	// Vertical lines
	pWind->SetPen(WHITE);
	for (int x = 0; x <= (columns + 1) * 100; x += 100) {
		pWind->DrawLine(x, 20, x, (2 + rows) * 20);
	}

	// Horizontal lines
	for (int y = 0; y <= (2 + rows) * 20; y += 20) {
		pWind->DrawLine(100, y, (1 + columns) * 100, y);
	}
}

bool TruthTable::Execute() {

	Component ** list = mAppManager->GetComponentList();
	int count = mAppManager->GetComponentsCount();
	leds = new LED*[count];
	switches = new Switch*[count];
	switchesDefault = new int[count];
	for (int i = 0; i < count; i++) {
		if (dynamic_cast<LED*>(list[i]) && !list[i]->IsDeleted()) {
			leds[ledsCount++] = (LED*)list[i];
		}
		else if (dynamic_cast<Switch*>(list[i]) && !list[i]->IsDeleted()) {
			switches[switchesCount] = (Switch*)list[i];
			switchesDefault[switchesCount++] = list[i]->GetOutputPinStatus();
		}
	}
	rows = pow(2, switchesCount);
	columns = ledsCount + switchesCount;
	if (switchesCount < 6 && columns < 12) {
		DrawTruthTable();
	}
	else
		canDraw = 0;
	DrawHeaders();
	CreateCompinations("");
	for(int i=0;i<switchesCount;i++){
		switches[i]->GetOutputPin()->SetStatus((Status)switchesDefault[i]);
	}
	for (int i = 0; i < ledsCount; i++) {
		TestGate(leds[i]);
	}
	return false;
}


/*Draw headers*/
void TruthTable::DrawHeaders() {
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(UI.FontSize, BOLD, BY_NAME, "Arial");
	string msg = "header";
	int n = switchesCount;
	int k = 0;

	for (int i = 100; i <= columns * 100; i += 100) {
		if (i / 100 <= n)
			msg = switches[i / 100 - 1]->GetLabel();
		else
			msg = leds[k++]->GetLabel();
		Normalizetxt(msg);
		if (canDraw)
			pWind->DrawString(i, 20, msg);
		write << msg << "   ";
	}
	write << endl;
}

/* Normalize message position */
void TruthTable::Normalizetxt(string& msg) {
	string temp="         ";
	int l = msg.length();
	for (int i = 0; i < l; i++)
		temp[i] = msg[i];
	/*msg += "             ";
	int n = (1+l)/2;
	temp[5] = msg[n];
	for (int i = 1; (n-i)>-1&&i < 6; i++) {
		temp[5 + i] = msg[n + i];
		temp[5 - i] = msg[n - i];
	}*/
	msg = temp;
}

/*Create Compinations*/
void TruthTable::CreateCompinations(string k) {
	if (k.length() == switchesCount) { Test(k); return; }
	CreateCompinations(k + '0');
	CreateCompinations(k + '1');
}

void TruthTable::Test(string k) {
	int pos = ToInt(k) * 20 + 40;
	string h;
	for (int i = 0; i < switchesCount; i++) {
		switches[i]->GetOutputPin()->SetStatus(Status(k[i] - '0'));
		h = k[i];
		if (canDraw)pWind->DrawString((i + 1) * 100 + 45, pos, h);
		write << "   " << h << "       ";
	}
	for (int i = 0; i < ledsCount; i++) {
		h = "";
		h += ('0' + TestGate(leds[i]));
		if (h[0] - '0')pWind->SetPen(GREEN);
		else pWind->SetPen(RED);
		if (canDraw)pWind->DrawString((i + 1) * 100 + 45 + switchesCount * 100, pos, h);
		write << "   " << h << "       ";
		pWind->SetPen(WHITE);
	}
	write << endl;
}

/* Tests the output on a led */
int TruthTable::TestGate(Component*c) {

	int returnValue;
	if (c) {

		if (dynamic_cast<Switch*>(c)) {
			return c->GetOutputPinStatus();
		}

		else if (dynamic_cast<LED*>(c)) {
			returnValue = TestGate(((LogicGate*)c)->GetInputPin(0)->GetConnection(0)->GetSourcePin()->GetGate());
			((Gate*)c)->SetInputPinStatus(0, (Status)returnValue);
			return returnValue;
		}

		else if (dynamic_cast<LogicGate*>(c)) {

			for (int i = 0; i<((LogicGate*)c)->GetInputsCount(); i++) {
				returnValue = TestGate(((LogicGate*)c)->GetInputPin(i)->GetConnection(0)->GetSourcePin()->GetGate());
				((Gate*)c)->SetInputPinStatus(i, (Status)returnValue);
			}

			((LogicGate*)c)->Operate();
			return ((LogicGate*)c)->GetOutputPinStatus();

		}
	}
	else 0;
}

int TruthTable::ToInt(string k) {
	int x = 0;
	for (int i = 0; i < k.length(); i++)
		x += (k[i] - '0')*(int)pow(2, k.length() - 1 - i);
	return x;
}

TruthTable::~TruthTable()
{
}
