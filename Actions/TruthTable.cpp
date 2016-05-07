#include "TruthTable.h"


/* Constructor */
TruthTable::TruthTable(ApplicationManager* pAppMan) : Action(pAppMan) {
	switchesCount = 0;
	ledsCount = 0;
	
	// Create and initialize the drawing window
	pWind = CreateWind(UI.Width, UI.Height, UI.StartX, UI.StartY);
	ChangeTitle("Truth Table");
	ClearDrawingArea();
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
	/*
	//
	// JUST FOR TESTING
	//
	pWind->SetPen(WHITE, 1);

	int startX = 0;
	int endX = UI.HorPinsCount * UI.PinOffset;
	int startY = UI.ToolBarHeight + UI.GateBarHeight;
	int endY = startY + UI.VerPinsCount * UI.PinOffset;

	// Vertical lines
	for (int x = startX; x <= endX; x += UI.PinOffset) {
		pWind->DrawLine(x, startY, x, endY);
	}

	// Horizontal lines
	for (int y = startY; y <= endY; y += UI.PinOffset) {
		pWind->DrawLine(startX, y, endX, y);
	}

	startX += UI.PinMargin;
	endX -= UI.PinMargin;
	startY += UI.PinMargin;
	endY -= UI.PinMargin;

	// Pins
	for (int x = startX; x <= endX; x += UI.PinOffset) {
		for (int y = startY; y <= endY; y += UI.PinOffset) {
			pWind->DrawPixel(x, y);
		}
	}*/
}

/*Draws truth table*/
void TruthTable::DrawTruthTable() const {
	// Vertical lines
	pWind->SetPen(WHITE);
	for (int x = 0; x <= (columns+1)*100; x += 100) {
		pWind->DrawLine(x, 100, x, (2+rows)*100);
	}

	// Horizontal lines
	for (int y = 0; y <= (2+rows)*100; y += 100) {
		pWind->DrawLine(100, y, (1+columns)*100, y);
	}
}

bool TruthTable::Execute() {

	Component ** list=mAppManager->GetComponentList();
	int count = mAppManager->GetComponentsCount();
	leds = new LED*[count];
	switches = new Switch*[count];
	for (int i = 0; i < count; i++) {
		if (dynamic_cast<LED*>(list[i]))
			leds[ledsCount++] = (LED*)list[i];
		else if (dynamic_cast<Switch*>(list[i]))
			switches[switchesCount++] = (Switch*)list[i];
	}
	rows = pow(2, switchesCount);
	columns = ledsCount + switchesCount;
	DrawTruthTable();
	DrawHeaders();
	CreateCompinations("");

	return false;
}


/*Draw headers*/
void TruthTable::DrawHeaders() const {
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(UI.StatusFontSize, BOLD, BY_NAME, "Arial");
	string msg = "header";
	int n = switchesCount;
	int k = 0;
	for (int i = 110; i <= columns * 100 + 10; i += 100) {
		if (i / 100 <= n)
			msg = "sw ID " + to_string(switches[i / 100 - 1]->GetID());
		else
			msg = "led ID " + to_string(leds[k++]->GetID());
		pWind->DrawString(i, 140, msg);
	}
}

/*Create Compinations*/
void TruthTable::CreateCompinations(string k) {
	if (k.length() == switchesCount) { Test(k); return; }
	CreateCompinations(k + '0');
	CreateCompinations(k + '1');
}

void TruthTable::Test(string k) {
	int pos = ToInt(k) * 100 + 240;
	string h;
	for (int i = 0; i < switchesCount; i++) {
		//switches[i]->GetOutptPin().SetStatus((Status)(k[i] - '0'));
		h = k[i];
		pWind->DrawString((i + 1) * 100 + 45, pos, h);
	}
	for (int i = 0; i < ledsCount; i++) {
		h = "";
		h+=('0'+TestGate(leds[i]));
	}
}

/*Tests the output on a led*/
int TruthTable::TestGate(Component*c) {
	if (dynamic_cast<Switch*>(c))return c->GetOutputPinStatus();
	/*if (dynamic_cast<LED*>(c))return TestGate(((LED*)c)->GetInputPin().GetComponent());
	if (dynamic_cast<Connection*>(c))
	{
		return TestGate(((Connection*)c)->GetSourcePin()->GetComponent());
	}*/
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
