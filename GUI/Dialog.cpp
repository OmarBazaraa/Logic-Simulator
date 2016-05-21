#include "Dialog.h"
#include "../CMUgraphicsLib/PNG.h"

/* Constructor that initializes the user interface */
Dialog::Dialog(string s) {
	// Create and initialize the drawing window
	pWind = CreateWind(400, 200, 500, 500);
	ChangeTitle(""); int x; int y;
	CreateInput();

	pWind->SetPen(BLACK);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial"); 
	for (int i = 0; i < 400; i += 20)
		for (int j = 0; j < 200; j += 20)
			pWind->DrawString(i, j, to_string(i) + to_string(j));
	pWind->WaitMouseClick(x, y);
	pWind->WaitMouseClick(x, y);
	pWind->WaitMouseClick(x, y);

}

/* Creates an Input object and assigns it to the same Window */
Input* Dialog::CreateInput() const {
	Input* pIn = new Input(pWind);
	return pIn;
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
void Dialog::ClearDrawingArea() const {
	pWind->SetBrush(WHITE);
	pWind->SetPen(WHITE);
	pWind->DrawRectangle(500, 500, 400, 300);
}
/*
/* Prints a message on the status bar *
void Dialog::PrintMsg(const string& msg) const {

	// Set the Message offset from the status bar
	int msgX = 10;
	int msgY = UI.Height - UI.StatusBarHeight / 2 - UI.StatusFontSize / 2;

	// Print the message
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(msgX, msgY, msg);
}
*/
/* Checks if the given y-coordinate is within the drawing area */
bool Dialog::IsDrawingArea(int y) {
	if (y <= UI.ToolBarHeight + UI.GateBarHeight || y >= UI.Height - UI.StatusBarHeight) return false;
	return true;
}

void Dialog::StoreImage(image & imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight) {
	pWind->StoreImage(imgThis, usX, usY, usWidth, usHeight);
}

buttonstate Dialog::GetButtonState(const button btMouse, int & iX, int & iY) {
	return pWind->GetButtonState(btMouse, iX, iY);
}

void Dialog::DrawImage(const image & imgThis, const int iX, const int iY, const int iWidth, const int iHeight) {
	pWind->DrawImage(&imgThis, iX, iY, iWidth, iHeight);
}

color Dialog::SetBrush(const color & colBrush) {
	return pWind->SetBrush(colBrush);
}

color Dialog::SetPen(const color c, int width) {
	return pWind->SetPen(c, width);
}

void Dialog::DrawLine(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle) {
	pWind->DrawLine(iX1, iY1, iX2, iY2, dsStyle);
}

clicktype Dialog::WaitMouseClick(int & iX, int & iY) {
	return pWind->WaitMouseClick(iX, iY);
}

void Dialog::DrawRectangle(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle, const int iWidth, const int iHeight) {
	pWind->DrawRectangle(iX1, iY1, iX2, iY2, dsStyle, iWidth, iHeight);
}

void Dialog::FlushMouseQueue() {
	pWind->FlushMouseQueue();
}

void Dialog::StoreWindowImage() {
	pWind->StoreImage(WindowImage, 0, 0, UI.Width, UI.Height);
}

image Dialog::GetWindowImage() {
	return WindowImage;
}

/* Destructor */
Dialog::~Dialog() {
	delete pWind;
}