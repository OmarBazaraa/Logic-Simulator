#include "Dialog.h"
#include "../CMUgraphicsLib/PNG.h"

/* Constructor that initializes the user interface */
Dialog::Dialog(string s, DialogBoxType pType) {
	// Create and initialize the drawing window
	pWind = new window(UI.DialogWidth, UI.DialogHeight, UI.DialogStartX, UI.DialogStartY);
	pWind->SetWaitClose(false);
	mMsg = s;
	mType = pType;
	DrawDialog();
}

/* Draws dialog box */
void Dialog::DrawDialog() const {

	pWind->SetBrush(UI.BackgroundColor);
	pWind->SetPen(UI.BackgroundColor);
	pWind->DrawRectangle(0, 0, UI.DialogWidth, UI.DialogHeight);

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

	pWind->DrawString(UI.MessageStartX, UI.MessageStartY, mMsg);

}

/* Draws OK button */
void Dialog::DrawOK() const {
	pWind->SetPen(UI.DarkColor);
	pWind->DrawRectangle(2 * UI.DialogMargin + UI.ButtonWidht, UI.ButtonStartY, 2 * UI.DialogMargin + 2 * UI.ButtonWidht, UI.ButtonStartY + UI.ButtonHeight);
	pWind->SetPen(WHITE);
	pWind->DrawString(UI.ButtonWidht + 2 * UI.DialogMargin + 38, UI.ButtonStartY + 5, "OK");
}

/* Draws YES button */
void Dialog::DrawYES() const {
	pWind->SetPen(UI.DarkColor);
	pWind->DrawRectangle(UI.DialogMargin, UI.ButtonStartY, UI.DialogMargin+UI.ButtonWidht, UI.ButtonStartY+UI.ButtonHeight);
	pWind->SetPen(WHITE);
	pWind->DrawString(UI.DialogMargin + 34, UI.ButtonStartY + 5, "YES");
}

/* Draws NO button */
void Dialog::DrawNO() const {
	pWind->SetPen(UI.DarkColor);
	pWind->DrawRectangle(2 * UI.DialogMargin + UI.ButtonWidht, UI.ButtonStartY, 2 * UI.DialogMargin + 2 * UI.ButtonWidht, UI.ButtonStartY + UI.ButtonHeight);
	pWind->SetPen(WHITE);
	pWind->DrawString(UI.ButtonWidht + 2 * UI.DialogMargin + 38, UI.ButtonStartY + 5, "NO");
}

/* Draws CANCEL button */
void Dialog::DrawCANCEL() const {
	pWind->SetPen(UI.DarkColor);
	pWind->DrawRectangle(3 * UI.DialogMargin + 2 * UI.ButtonWidht, UI.ButtonStartY, 3 * UI.DialogMargin + 3 * UI.ButtonWidht, UI.ButtonStartY + UI.ButtonHeight);
	pWind->SetPen(WHITE);
	pWind->DrawString(2 * UI.ButtonWidht + 3 * UI.DialogMargin + 17, UI.ButtonStartY + 5, "CANCEL");
}

/* Gets user clicked button */
DialogBoxButton Dialog::GetUserClick() {
	int x, y, oldX = 0, oldY = 0;
	while (1) {

		if (pWind->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_UP) {

			if (IsButton(x, y) && !IsButton(oldX, oldY)) {

				if (x > UI.DialogMargin && x < UI.ButtonWidht + UI.DialogMargin) {
					pWind->DrawRectangle(UI.DialogMargin, UI.ButtonStartY, UI.DialogMargin + UI.ButtonWidht, UI.ButtonStartY + UI.ButtonHeight);
					pWind->DrawString(UI.DialogMargin + 34, UI.ButtonStartY + 5, "YES");
				}

				if (x > UI.ButtonWidht + 2 * UI.DialogMargin && x < 2 * UI.ButtonWidht + 2 * UI.DialogMargin) {
					pWind->DrawRectangle(2 * UI.DialogMargin + UI.ButtonWidht, UI.ButtonStartY, 2 * UI.DialogMargin + 2 * UI.ButtonWidht, UI.ButtonStartY + UI.ButtonHeight);
					if (mType == Type_A)
						pWind->DrawString(UI.ButtonWidht + 2 * UI.DialogMargin + 38, UI.ButtonStartY + 5, "NO");
					else
						pWind->DrawString(UI.ButtonWidht + 2 * UI.DialogMargin + 38, UI.ButtonStartY + 5, "OK");
				}

				if (x > 2 * UI.ButtonWidht + 3 * UI.DialogMargin && x < 3 * UI.ButtonWidht + 2 * UI.DialogMargin) {
					pWind->DrawRectangle(3 * UI.DialogMargin + 2 * UI.ButtonWidht, UI.ButtonStartY, 3 * UI.DialogMargin + 3 * UI.ButtonWidht, UI.ButtonStartY + UI.ButtonHeight);
					pWind->DrawString(2 * UI.ButtonWidht + 3 * UI.DialogMargin + 17, UI.ButtonStartY + 5, "CANCEL");
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

				if (x > UI.DialogMargin && x < UI.ButtonWidht + UI.DialogMargin) {
					return YES;
				}

				if (x > UI.ButtonWidht + 2 * UI.DialogMargin && x < 2 * UI.ButtonWidht + 2 * UI.DialogMargin) {
					if (mType == Type_A)
						return NO;
					else
						return OK;
				}

				if (x > 2 * UI.ButtonWidht + 3 * UI.DialogMargin && x < 3 * UI.ButtonWidht + 2 * UI.DialogMargin) {
					return CANCEL;
				}

			}
		}
	}
}

/* Checks if the given y-coordinate is button */
bool Dialog::IsButton(int x, int y) {
	return (y < UI.ButtonHeight + UI.ButtonStartY && y > UI.ButtonStartY 
		&& (x > UI.DialogMargin && x < UI.ButtonWidht + UI.DialogMargin && mType == Type_A
			|| (x > UI.ButtonWidht + 2 * UI.DialogMargin && x < 2 * UI.ButtonWidht + 2 * UI.DialogMargin)
			|| (x > 2 * UI.ButtonWidht + 3 * UI.DialogMargin && x < 3 * UI.ButtonWidht + 2 * UI.DialogMargin && mType != Type_C)));
}

/* Destructor */
Dialog::~Dialog() {
	delete pWind;
}