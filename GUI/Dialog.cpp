#include "Dialog.h"
#include "../CMUgraphicsLib/PNG.h"

/* Constructor that initializes the user interface */
Dialog::Dialog(string s, DialogBoxType pType) {
	// Create and initialize the drawing window
	pWind = new window(414, 165, 485, 400);	
	pWind->SetWaitClose(false);
	mMsg = s;
	mType = pType;
	DrawDialog();
}

/* Draws dialog box */
void Dialog::DrawDialog() const {

	pWind->SetBrush(UI.BackgroundColor);
	pWind->SetPen(UI.BackgroundColor);
	pWind->DrawRectangle(0, 0, 400, 150);

	pWind->ChangeTitle("");

	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->SetBrush(UI.DarkColor);

	switch (mType) {

	case Type_A:
		DrawYES();
		DrawNO();
		DrawCANCEL();
		break;

	case Type_B:
		DrawOK();
		DrawCANCEL();
		break;

	case Type_C:
		DrawOK();
		break;

	}

	pWind->DrawString(15, 35, mMsg);

}

/* Draws OK button */
void Dialog::DrawOK() const {
	pWind->SetPen(UI.DarkColor);
	pWind->DrawRectangle(150, 90, 250, 120);
	pWind->SetPen(WHITE);
	pWind->DrawString(188, 95, "OK");
}

/* Draws YES button */
void Dialog::DrawYES() const {
	pWind->SetPen(UI.DarkColor);
	pWind->DrawRectangle(25, 90, 125, 120);
	pWind->SetPen(WHITE);
	pWind->DrawString(59, 95, "YES");
}

/* Draws NO button */
void Dialog::DrawNO() const {
	pWind->SetPen(UI.DarkColor);
	pWind->DrawRectangle(150, 90, 250, 120);
	pWind->SetPen(WHITE);
	pWind->DrawString(188, 95, "NO");
}

/* Draws CANCEL button */
void Dialog::DrawCANCEL() const {
	pWind->SetPen(UI.DarkColor);
	pWind->DrawRectangle(275, 90, 375, 120);
	pWind->SetPen(WHITE);
	pWind->DrawString(292, 95, "CANCEL");
}

/* Gets user clicked button */
DialogBoxButton Dialog::GetUserClick() {
	int x, y, oldX = 0, oldY = 0;
	while (1) {

		if (pWind->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_UP) {

			if (IsButton(x, y) && !IsButton(oldX, oldY)) {

				if (x > 25 && x < 125) {
					pWind->DrawRectangle(25, 90, 125, 120);
					pWind->DrawString(59, 95, "YES");
				}

				if (x > 150 && x < 250) {
					pWind->DrawRectangle(150, 90, 250, 120);
					if (mType == Type_A)
						pWind->DrawString(188, 95, "NO");
					else
						pWind->DrawString(188, 95, "OK");
				}

				if (x > 275 && x < 375) {
					pWind->DrawRectangle(275, 90, 375, 120);
					pWind->DrawString(292, 95, "CANCEL");
				}

			}

			else if (!IsButton(x, y) && IsButton(oldX, oldY)) {
				DrawDialog();
			}

			oldX = x;
			oldY = y;

		}
		else {

			if (IsButton(x, y)) {

				if (x > 25 && x < 125) {
					return YES;
				}

				if (x > 150 && x < 250) {
					if (mType == Type_A)
						return NO;
					else
						return OK;
				}

				if (x > 275 && x < 375) {
					return CANCEL;
				}

			}
		}
	}
}

/* Checks if the given y-coordinate is button */
bool Dialog::IsButton(int x, int y) {
	return (y < 120 && y > 90 && (x > 25 && x < 125 && mType == Type_A || (x > 150 && x < 250) || (x > 275 && x < 375 && mType != Type_C)));
}

/* Destructor */
Dialog::~Dialog() {
	delete pWind;
}