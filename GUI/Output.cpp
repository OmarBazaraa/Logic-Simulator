#include "Output.h"

/* Constructor that initializes the user interface */
Output::Output() {
	// Design mode is the startup mode
	UI.AppMode = DESIGN;

	// Initialize interface colors
	UI.DrawColor = BLACK;
	UI.SelectionColor = color(255, 193, 7);
	UI.ConnectionColor = WHITE;
	UI.MsgColor = WHITE;
	UI.StatusBarColor = color(66, 66, 66);
	UI.BackgroundColor = color(97, 97, 97);

	// Create and initialize the drawing window
	pWind = CreateWind(UI.Width, UI.Height, UI.StartX, UI.StartY);
	ChangeTitle("Logic Simulator");
	CreateToolBar();
	CreateStatusBar();
	ClearDrawingArea();

	// Initialize the pin grid
	mPinGrid = new PinInfo*[UI.HorPinsCount];
	for (int x = 0; x < UI.HorPinsCount; x++) mPinGrid[x] = new PinInfo[UI.VerPinsCount];
}

/* Creates an Input object and assigns it to the same Window */
Input* Output::CreateInput() const {
	Input* pIn = new Input(pWind);
	return pIn;
}

/* Creates a new Window object */
window* Output::CreateWind(int w, int h, int x, int y) const {
	// The additional width & height is due to a strange error in the graphics
	// library which doesn't create the Window with the exact given dimensions
	return new window(w + 14, h + 15, x, y);
}

/* Returns the grid of pins */
Component* Output::GetComponentAtPin(int x, int y) const {
	getPinIndices(x, y);
	return mPinGrid[x][y].Comp;
}

/* Chnages the title of the Window */
void Output::ChangeTitle(const string& title) const {
	pWind->ChangeTitle(title);
}

/* Draws the tool bar and the gate bar */
void Output::CreateToolBar() const {
	string toolbar, gatebar;

	if (UI.AppMode == Mode::DESIGN) {
		toolbar = "images\\bars\\toolbar_design.jpg";
		gatebar = "images\\bars\\gatebar_active.jpg";
	}
	else {
		toolbar = "images\\bars\\toolbar_simulation.jpg";
		gatebar = "images\\bars\\gatebar_inactive.jpg";
	}
	
	pWind->DrawImage(toolbar, 0, 0, UI.Width, UI.ToolBarHeight);
	pWind->DrawImage(gatebar, 0, UI.ToolBarHeight, UI.Width, UI.GateBarHeight);
}

/* Draws the status bar */
void Output::CreateStatusBar() const {
	pWind->SetPen(UI.StatusBarColor);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.Height - UI.StatusBarHeight, UI.Width, UI.Height);
}

/* Clears the drawing area */
void Output::ClearDrawingArea() const {
	pWind->SetPen(UI.BackgroundColor);
	pWind->SetBrush(UI.BackgroundColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight + UI.GateBarHeight, UI.Width, UI.Height - UI.StatusBarHeight);

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
	}
}

/* Clears the status bar */
void Output::ClearStatusBar() const {
	// Set the message offset from the status bar
	int msgX = 10;
	int msgY = UI.Height - UI.StatusBarHeight / 2 - UI.StatusFontSize / 2;

	// Overwrite using bachground color to erase the message
	pWind->SetPen(UI.StatusBarColor);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(msgX, msgY, UI.Width, UI.Height);
}

/* Prints a message on the status bar */
void Output::PrintMsg(const string& msg) const {
	// Clear the status bar first to print message on it
	ClearStatusBar();

	// Set the Message offset from the status bar
	int msgX = 10;
	int msgY = UI.Height - UI.StatusBarHeight / 2 - UI.StatusFontSize / 2;

	// Print the message
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(UI.StatusFontSize, BOLD, BY_NAME, "Arial");
	pWind->DrawString(msgX, msgY, msg);
}

/* Checks if the given y-coordinate is within the drawing area */
bool Output::IsDrawingArea(int y) {
	if (y <= UI.ToolBarHeight + UI.GateBarHeight || y >= UI.Height - UI.StatusBarHeight) return false;
	return true;
}

/* Marks the given area of pins */
void Output::MarkPins(const GraphicsInfo& gfxInfo, PinType mark, Component* comp) {
	int x1 = gfxInfo.x1, y1 = gfxInfo.y1;
	int x2 = gfxInfo.x2, y2 = gfxInfo.y2;
	getPinIndices(x1, y1);
	getPinIndices(x2, y2);

	for (int x = x1; x < x2; x++) {
		for (int y = y1; y < y2; y++) {
			mPinGrid[x][y].Type = mark;
			mPinGrid[x][y].Comp = comp;
		}
	}
}

/* Marks the pins of the connection as used */
void Output::MarkConnectionPins(const vector<GraphicsInfo>& path, Component* comp) {
	for (int i = 1; i < (int)path.size(); i++) {
		// Horizontal line
		if (path[i].y1 == path[i].y2) {
			int x1 = path[i].x1 / UI.PinOffset;
			int x2 = path[i].x2 / UI.PinOffset;
			int y = (path[i].y1 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;

			if (x1 > x2) swap(x1, x2);

			for (int x = x1; x <= x2; x++) {
				if (mPinGrid[x][y].Type == EMPTY) {
					mPinGrid[x][y].Type = PinType::HOR_CONNECTION;
				}
				else {
					mPinGrid[x][y].Type = PinType::INTERSECTING_CONNECTIONS;
					mPinGrid[x][y].PreviousComp = mPinGrid[x][y].Comp;
				}
				
				mPinGrid[x][y].Comp = comp;
			}
		}
		// Vertical line
		else {
			int y1 = (path[i].y1 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;
			int y2 = (path[i].y2 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;
			int x = path[i].x1 / UI.PinOffset;

			if (y1 > y2) swap(y1, y2);

			for (int y = y1; y <= y2; y++) {
				if (mPinGrid[x][y].Type == EMPTY) {
					mPinGrid[x][y].Type = PinType::VER_CONNECTION;
				}
				else {
					mPinGrid[x][y].Type = PinType::INTERSECTING_CONNECTIONS;
					mPinGrid[x][y].PreviousComp = mPinGrid[x][y].Comp;
				}

				mPinGrid[x][y].Comp = comp;
			}
		}
	}
}

/* Clears the pins of the connection */
void Output::ClearConnectionPins(const vector<GraphicsInfo>& path) {
	for (int i = 1; i < (int)path.size(); i++) {
		// Horizontal line
		if (path[i].y1 == path[i].y2) {
			int x1 = path[i].x1 / UI.PinOffset;
			int x2 = path[i].x2 / UI.PinOffset;
			int y = (path[i].y1 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;

			if (x1 > x2) swap(x1, x2);

			for (int x = x1; x <= x2; x++) {
				if (mPinGrid[x][y].Type == INTERSECTING_CONNECTIONS) {
					mPinGrid[x][y].Type = PinType::VER_CONNECTION;
					mPinGrid[x][y].Comp = mPinGrid[x][y].PreviousComp;
					mPinGrid[x][y].PreviousComp = NULL;
				}
				else {
					mPinGrid[x][y].Type = PinType::EMPTY;
					mPinGrid[x][y].Comp = NULL;
				}
			}
		}
		// Vertical line
		else {
			int y1 = (path[i].y1 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;
			int y2 = (path[i].y2 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;
			int x = path[i].x1 / UI.PinOffset;

			if (y1 > y2) swap(y1, y2);

			for (int y = y1; y <= y2; y++) {
				if (mPinGrid[x][y].Type == INTERSECTING_CONNECTIONS) {
					mPinGrid[x][y].Type = PinType::HOR_CONNECTION;
					mPinGrid[x][y].Comp = mPinGrid[x][y].PreviousComp;
					mPinGrid[x][y].PreviousComp = NULL;
				}
				else {
					mPinGrid[x][y].Type = PinType::EMPTY;
					mPinGrid[x][y].Comp = NULL;
				}
			}
		}
	}
}

/* Checks if the given area of pins is empty */
bool Output::IsEmptyArea(const GraphicsInfo& gfxInfo) const {
	int x1 = gfxInfo.x1, y1 = gfxInfo.y1;
	int x2 = gfxInfo.x2, y2 = gfxInfo.y2;
	getPinIndices(x1, y1);
	getPinIndices(x2, y2);

	for (int x = x1; x < x2; x++) {
		for (int y = y1; y < y2; y++) {
			if (mPinGrid[x][y].Type != PinType::EMPTY) return false;	// Occupied area
		}
	}

	return true;
}

/* Draws label*/
void Output::DrawLabel(const GraphicsInfo& gfxInfo, const string& label) const {
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(gfxInfo.x1, gfxInfo.y1, label);
}

/* Draws AND gate */
void Output::DrawAND(const GraphicsInfo& gfxInfo, bool selected) const {
	//string dir = (selected ? "Images\\gates\\and_highlighted.jpg" : "Images\\gates\\and.jpg");
	//pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.AndGateWidth, UI.AndGateHeight);

	//
	// JUST FOR TESTING
	//
	pWind->SetPen(UI.SelectionColor, 3);

	pWind->DrawLine(gfxInfo.x1, gfxInfo.y1, gfxInfo.x2, gfxInfo.y1);
	pWind->DrawLine(gfxInfo.x1, gfxInfo.y1, gfxInfo.x1, gfxInfo.y2);
	pWind->DrawLine(gfxInfo.x1, gfxInfo.y2, gfxInfo.x2, gfxInfo.y2);
	pWind->DrawLine(gfxInfo.x2, gfxInfo.y1, gfxInfo.x2, gfxInfo.y2);
}

/* Draws OR gate */
void Output::DrawOR(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\or_highlighted.jpg" : "Images\\gates\\or.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.OrGateWidth, UI.OrGateHeight);
}

/* Draws NOT gate */
void Output::DrawNOT(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\not_highlighted.jpg" : "Images\\gates\\not.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.NotGateWidth, UI.NotGateHeight);
}

/* Draws NAND gate */
void Output::DrawNAND(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\nand_highlighted.jpg" : "Images\\gates\\nand.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.NandGateWidth, UI.NandGateHeight);
}

/* Draws NOR gate */
void Output::DrawNOR(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\nor_highlighted.jpg" : "Images\\gates\\nor.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.NorGateWidth, UI.NorGateHeight);
}

/* Draws XOR gate */
void Output::DrawXOR(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\xor_highlighted.jpg" : "Images\\gates\\xor.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.XorGateWidth, UI.XorGateHeight);
}

/* Draws XNOR gate */
void Output::DrawXNOR(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\xnor_highlighted.jpg" : "Images\\gates\\xnor.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.XnorGateWidth, UI.XnorGateHeight);
}

/* Draws AND3 gate */
void Output::DrawAND3(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\and3_highlighted.jpg" : "Images\\gates\\and3.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.And3GateWidth, UI.And3GateHeight);
}

/* Draws NOR3 gate */
void Output::DrawNOR3(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\nor3_highlighted.jpg" : "Images\\gates\\nor3.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.Nor3GateWidth, UI.Nor3GateHeight);
}

/* Draws XOR3 gate */
void Output::DrawXOR3(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\xor3_highlighted.jpg" : "Images\\gates\\xor3.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.Xor3GateWidth, UI.Xor3GateHeight);
}

/* Draws Buffer gate */
void Output::DrawBuffer(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected && UI.AppMode == DESIGN ? "Images\\gates\\buffer_highlighted.jpg" : "Images\\gates\\buffer.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.BufferGateWidth, UI.BufferGateHeight);
}

/* Draws Switch */
void Output::DrawSwitch(const GraphicsInfo& gfxInfo, bool selected, bool on) const {
	string dir = (selected && UI.AppMode == DESIGN || on && UI.AppMode == SIMULATION ? "Images\\gates\\switch_on.jpg" : "Images\\gates\\switch_off.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.SwitchWidth, UI.SwitchHeight);
}

/* Draws LED */
void Output::DrawLED(const GraphicsInfo& gfxInfo, bool selected, bool on) const {
	string dir = (selected && UI.AppMode == DESIGN || on && UI.AppMode == SIMULATION ? "Images\\gates\\led_on.jpg" : "Images\\gates\\led_off.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LedWidth, UI.LedHeight);
}

/* Draws connection */
void Output::DrawConnection(const vector<GraphicsInfo>& path, bool selected, bool on) {
	pWind->SetPen(selected && UI.AppMode == DESIGN || on && UI.AppMode == SIMULATION ? UI.SelectionColor : BLACK, 2);

	for (int i = 0; i < (int)path.size(); i++) {
		pWind->DrawLine(path[i].x1, path[i].y1, path[i].x2, path[i].y2);
	}
}

/* Returns the shortest available path for the connection, null if no path found */
vector<GraphicsInfo>* Output::GetConnectionPath(const GraphicsInfo& gfxInfo) {
	int dx[] = { 0, 0, 1, -1 };
	int dy[] = { 1, -1, 0, 0 };

	Node parents[UI.HorPinsCount][UI.VerPinsCount];
	Node src(gfxInfo.x1 / UI.PinOffset, (gfxInfo.y1 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset);
	Node dst(gfxInfo.x2 / UI.PinOffset, (gfxInfo.y2 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset);
	Node u, v;
	queue<Node> q;

	parents[src.x][src.y] = src;
	q.push(src);

	while (!q.empty()) {
		u = q.front();
		q.pop();

		if (u == dst) break;

		for (int i = 0; i < 4; i++) {
			v = u;
			v.x += dx[i];
			v.y += dy[i];

			if (!IsValidNode(v, u) || parents[v.x][v.y].x != -1) continue;

			q.push(v);
			parents[v.x][v.y] = u;
		}
	}

	return (u != dst ? NULL : GenerateConnectionPath(src, dst, parents));
}

void Output::StoreImage(image & imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight) {
	pWind->StoreImage(imgThis, usX, usY, usWidth, usHeight);
}

buttonstate Output::GetButtonState(const button btMouse, int & iX, int & iY) {
	return pWind->GetButtonState(btMouse, iX, iY);
}

void Output::DrawImage(const image & imgThis, const int iX, const int iY, const int iWidth, const int iHeight) {
	pWind->DrawImage(&imgThis, iX, iY, iWidth, iHeight);
}

color Output::SetBrush(const color & colBrush) {
	return pWind->SetBrush(colBrush);
}

color Output::SetPen(const color c, int width) {
	return pWind->SetPen(c, width);
}

void Output::DrawLine(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle) {
	pWind->DrawLine(iX1, iY1, iX2, iY2, dsStyle);
}

clicktype Output::WaitMouseClick(int & iX, int & iY) {
	return pWind->WaitMouseClick(iX, iY);
}

void Output::DrawRectangle(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle, const int iWidth, const int iHeight) {
	pWind->DrawRectangle(iX1, iY1, iX2, iY2, dsStyle, iWidth, iHeight);
}

void Output::FlushMouseQueue() {
	pWind->FlushMouseQueue();
}

void Output::StoreWindowImage() {
	pWind->StoreImage(WindowImage, 0, 0, UI.Width, UI.Height);
}

image Output::GetWindowImage() {
	return WindowImage;
}

/* Generate the connection path */
vector<GraphicsInfo>* Output::GenerateConnectionPath(Node& src, Node& dst, Node parents[UI.HorPinsCount][UI.VerPinsCount]) {
	vector<GraphicsInfo>* path = new vector<GraphicsInfo>;
	Node prv = dst;
	Node cur = parents[prv.x][prv.y];
	Node nxt;
	int x1, y1, x2, y2;

	x1 = dst.x * UI.PinOffset + UI.PinMargin;
	y1 = dst.y * UI.PinOffset + UI.PinMargin + UI.ToolBarHeight + UI.GateBarHeight;
	x2 = dst.x * UI.PinOffset + UI.PinOffset;
	y2 = dst.y * UI.PinOffset + UI.PinMargin + UI.ToolBarHeight + UI.GateBarHeight;
	path->push_back(GraphicsInfo(x1, y1, x2, y2));

	while (cur != src) {
		nxt = parents[cur.x][cur.y];

		if ((prv.x != cur.x || cur.x != nxt.x) && (prv.y != cur.y || cur.y != nxt.y)) {
			x1 = prv.x * UI.PinOffset + UI.PinMargin;
			y1 = prv.y * UI.PinOffset + UI.PinMargin + UI.ToolBarHeight + UI.GateBarHeight;
			x2 = cur.x * UI.PinOffset + UI.PinMargin;
			y2 = cur.y * UI.PinOffset + UI.PinMargin + UI.ToolBarHeight + UI.GateBarHeight;
			path->push_back(GraphicsInfo(x1, y1, x2, y2));
			prv = cur;
		}

		cur = nxt;
	}

	x1 = prv.x * UI.PinOffset + UI.PinMargin;
	y1 = prv.y * UI.PinOffset + UI.PinMargin + UI.ToolBarHeight + UI.GateBarHeight;
	x2 = cur.x * UI.PinOffset + UI.PinMargin;
	y2 = cur.y * UI.PinOffset + UI.PinMargin + UI.ToolBarHeight + UI.GateBarHeight;
	path->push_back(GraphicsInfo(x1, y1, x2, y2));

	x1 = src.x * UI.PinOffset;
	y1 = src.y * UI.PinOffset + UI.PinMargin + UI.ToolBarHeight + UI.GateBarHeight;
	x2 = src.x * UI.PinOffset + UI.PinMargin;
	y2 = src.y * UI.PinOffset + UI.PinMargin + UI.ToolBarHeight + UI.GateBarHeight;
	path->push_back(GraphicsInfo(x1, y1, x2, y2));

	return path;
}

/* Checks if the given pin index is valid or not */
bool Output::IsValidNode(const Node& cur, const Node& par) {
	if (cur.x < 0 || cur.x >= UI.HorPinsCount || cur.y < 0 || cur.y >= UI.VerPinsCount)
		return false;

	return mPinGrid[cur.x][cur.y].Type == PinType::EMPTY
		|| (cur.y == par.y && mPinGrid[cur.x][cur.y].Type == PinType::VER_CONNECTION)
		|| (cur.x == par.x && mPinGrid[cur.x][cur.y].Type == PinType::HOR_CONNECTION);
}

/* Destructor */
Output::~Output() {
	delete pWind;
	for (int x = 0; x < UI.HorPinsCount; x++) delete[] mPinGrid[x];
	delete[] mPinGrid;
}