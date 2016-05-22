#include "Dialog.h"
#include "../CMUgraphicsLib/PNG.h"

/* Constructor that initializes the user interface */
Dialog::Dialog(string s) {
	// Create and initialize the drawing window
	pWind = CreateWind(400, 150, 485, 400);
	pWind->SetWaitClose(false);
	msg = s;
	DrawDialog();
}


/* Creates a new Window object */
window* Dialog::CreateWind(int w, int h, int x, int y) const {
	return new window(w + 14, h + 15, x, y);	
}

/* Chnages the title of the Window */
void Dialog::ChangeTitle(const string& title) const {
	pWind->ChangeTitle(title);
}

/* Clears the drawing area */
void Dialog::DrawDialog() const {
	pWind->SetBrush(UI.BackgroundColor);
	pWind->DrawRectangle(0, 0, 400, 150);
	ChangeTitle("");
	pWind->SetPen(WHITE);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");

	pWind->SetPen(UI.DarkColor);
	pWind->SetBrush(UI.DarkColor);
	pWind->DrawRectangle(25, 90, 125, 120);
	pWind->DrawRectangle(150, 90, 250, 120);
	pWind->DrawRectangle(275, 90, 375, 120);
	pWind->SetPen(WHITE);
	pWind->DrawString(59, 95, "YES");
	//pWind->SetPen(RED);
	pWind->DrawString(188, 95, "NO");
	//pWind->SetPen(PURPLE);
	pWind->DrawString(292, 95, "CANCEL");
	pWind->SetPen(WHITE);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(15, 35, msg);
}

/* Checks if the given y-coordinate is button */
bool Dialog::IsButton(int x, int y) {
	return(y < 120 && y>90&&((x > 25 && x < 125)|| (x > 150 && x < 250)|| (x > 275 && x < 375)));
}

/* Get user clicked button */
DialogBoxButton Dialog::GetUserClick() {
	int x, y,oldX=10,oldY=10;
	while (1) {
		if (pWind->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_UP) {
			if (IsButton(x,y)&&!IsButton(oldX,oldY)) {
				pWind->SetPen(WHITE);
				if (x > 25 && x < 125) {
					pWind->DrawRectangle(25, 90, 125, 120);
					pWind->DrawString(59, 95, "YES");
				}
				if (x > 150 && x < 250) {
					pWind->DrawRectangle(150, 90, 250, 120);
					pWind->DrawString(188, 95, "NO");
				}
				if (x > 275 && x < 375) {
					pWind->DrawRectangle(275, 90, 375, 120);
					pWind->DrawString(292, 95, "CANCEL");
				}
			}
			else if (!IsButton(x, y) && IsButton(oldX,oldY)){
				DrawDialog();
			}
			oldX = x;
			oldY = y;
		}
		else if (pWind->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_DOWN)
			if (IsButton(x,y)) {
				if (x > 25 && x < 125)
					return YES;
				if (x > 150 && x < 250)
					return NO;
				if (x > 275 && x < 375)
					return CANCEL;
			}
	}
}

/* Destructor */
Dialog::~Dialog() {
	delete pWind;
}