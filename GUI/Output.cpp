#include "Output.h"
#include "..\Components\Component.h"

/* Constructor that initializes the user interface */
Output::Output() {
	// Design mode is the startup mode
	UI.AppMode = DESIGN;

	// Initialize interface colors
	UI.BackgroundColor = color(117, 117, 117);
	UI.DarkColor = color(66, 66, 66);
	UI.SelectionColor = color(255, 193, 7);
	UI.InvalidColor = color(213, 0, 0);
	UI.MsgColor = WHITE;
	UI.ConnectionColor = BLACK;
	UI.ConnectionOnColor = color(139, 195, 74);

	// Create and initialize the drawing window
	pWind = CreateWind(UI.Width, UI.Height, UI.StartX, UI.StartY);

	pWind->SetWaitClose(false);
	pWind->SetBuffering(true);

	ChangeTitle("Logic Simulator");
	CreateToolBar();
	CreateGateBar();
	ClearDrawingArea();
	CreateStatusBar();

	pWind->UpdateBuffer();

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

/* Chnages the title of the Window */
void Output::ChangeTitle(const string& title) const {
	pWind->ChangeTitle(title);
}

/* Draws the tool bar and the gate bar */
void Output::CreateToolBar(int hoverdItem) const {
	// Prepare list of image directories for each tool item
	string toolBarImages[TOOLS_COUNT], states[TOOLS_COUNT], dir;

	toolBarImages[ITEM_EDIT] =			"\\edit.jpg";
	toolBarImages[ITEM_DELETE] =		"\\delete.jpg";
	toolBarImages[ITEM_COPY] =			"\\copy.jpg";
	toolBarImages[ITEM_CUT] =			"\\cut.jpg";
	toolBarImages[ITEM_PASTE] =			"\\paste.jpg";
	toolBarImages[ITEM_UNDO] =			"\\undo.jpg";
	toolBarImages[ITEM_REDO] =			"\\redo.jpg";
	toolBarImages[ITEM_PLAY] =			"\\play.jpg";
	toolBarImages[ITEM_PAUSE] =			"\\pause.jpg";
	toolBarImages[ITEM_TRUTHTABLE] =	"\\truth_table.jpg";
	toolBarImages[ITEM_SAVE] =			"\\save.jpg";
	toolBarImages[ITEM_LOAD] =			"\\load.jpg";
	toolBarImages[ITEM_EXIT] =			"\\exit.jpg";
	
	if (UI.AppMode == Mode::DESIGN) {
		states[ITEM_EDIT] = "active";
		states[ITEM_DELETE] = "active";
		states[ITEM_COPY] = "active";
		states[ITEM_CUT] = "active";
		states[ITEM_PASTE] = "active";
		states[ITEM_UNDO] = "active";
		states[ITEM_REDO] = "active";
		states[ITEM_PLAY] = "active";
		states[ITEM_PAUSE] = "inactive";
		states[ITEM_TRUTHTABLE] = "inactive";
		states[ITEM_SAVE] = "active";
		states[ITEM_LOAD] = "active";
		states[ITEM_EXIT] = "active";
	}
	else {
		states[ITEM_EDIT] = "inactive";
		states[ITEM_DELETE] = "inactive";
		states[ITEM_COPY] = "inactive";
		states[ITEM_CUT] = "inactive";
		states[ITEM_PASTE] = "inactive";
		states[ITEM_UNDO] = "inactive";
		states[ITEM_REDO] = "inactive";
		states[ITEM_PLAY] = "inactive";
		states[ITEM_PAUSE] = "active";
		states[ITEM_TRUTHTABLE] = "active";
		states[ITEM_SAVE] = "inactive";
		states[ITEM_LOAD] = "inactive";
		states[ITEM_EXIT] = "active";
	}

	if (hoverdItem != -1 && states[hoverdItem] != "inactive") {
		states[hoverdItem] = "highlighted";
	}

	pWind->SetBrush(UI.DarkColor);
	pWind->SetPen(UI.DarkColor);
	pWind->DrawRectangle(0, 0, UI.Width, UI.ToolBarHeight);

	// Draw menu item one image at a time
	for (int i = 0; i < TOOLS_COUNT; i++) {
		dir = "Images\\menu\\toolbar\\" + states[i] + toolBarImages[i];
		pWind->DrawImage(dir, i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);
	}
}

/* Draws the the gate bar */
void Output::CreateGateBar(int hoverdItem) const {
	// Prepare list of image directories for each tool item
	string gateBarImages[GATES_COUNT], states[GATES_COUNT], dir;

	gateBarImages[ITEM_AND] =			"\\and.jpg";
	gateBarImages[ITEM_OR] =			"\\or.jpg";
	gateBarImages[ITEM_NOT] =			"\\not.jpg";
	gateBarImages[ITEM_NAND] =			"\\nand.jpg";
	gateBarImages[ITEM_NOR] =			"\\nor.jpg";
	gateBarImages[ITEM_XOR] =			"\\xor.jpg";
	gateBarImages[ITEM_XNOR] =			"\\xnor.jpg";
	gateBarImages[ITEM_AND3] =			"\\and3.jpg";
	gateBarImages[ITEM_NOR3] =			"\\nor3.jpg";
	gateBarImages[ITEM_XOR3] =			"\\xor3.jpg";
	gateBarImages[ITEM_BUFFER] =		"\\buffer.jpg";
	gateBarImages[ITEM_SWITCH] =		"\\switch.jpg";
	gateBarImages[ITEM_LED] =			"\\led.jpg";
	gateBarImages[ITEM_CONNECTION] =	"\\connection.jpg";

	if (UI.AppMode == Mode::DESIGN) {
		for (int i = 0; i < GATES_COUNT; i++) states[i] = "active";
	}
	else {
		for (int i = 0; i < GATES_COUNT; i++) states[i] = "inactive";
	}

	if (hoverdItem != -1 && states[hoverdItem] != "inactive") {
		states[hoverdItem] = "highlighted";
	}

	// Draw menu item one image at a time
	for (int i = 0; i < GATES_COUNT; i++) {
		dir = "Images\\menu\\gatebar\\" + states[i] + gateBarImages[i];
		pWind->DrawImage(dir, i * UI.GateItemWidth, UI.ToolBarHeight, UI.GateItemWidth, UI.GateBarHeight);
	}

	// Draw a separator line between tool bar and gate bar
	pWind->SetPen(WHITE, 1);
	pWind->DrawLine(UI.TextMargin, UI.ToolBarHeight, UI.Width - UI.TextMargin, UI.ToolBarHeight);

	pWind->UpdateBuffer();
}

/* Draws the status bar */
void Output::CreateStatusBar() const {
	pWind->SetPen(UI.DarkColor);
	pWind->SetBrush(UI.DarkColor);
	pWind->DrawRectangle(0, UI.Height - UI.StatusBarHeight, UI.Width, UI.Height);
}

/* Clears the drawing area */
void Output::ClearDrawingArea() const {
	pWind->SetBrush(UI.BackgroundColor);
	pWind->SetPen(UI.BackgroundColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight + UI.GateBarHeight, UI.Width, UI.Height - UI.StatusBarHeight);
}

/* Clears the status bar */
void Output::ClearStatusBar() const {
	// Set the message offset from the status bar
	int msgX = UI.TextMargin;
	int msgY = UI.Height - UI.StatusBarHeight / 2 - UI.FontSize / 2;

	// Overwrite using bachground color to erase the message
	pWind->SetPen(UI.DarkColor);
	pWind->SetBrush(UI.DarkColor);
	pWind->DrawRectangle(msgX, msgY, UI.Width, UI.Height);
}

/* Prints a message on the status bar */
void Output::PrintMsg(const string& msg) const {
	// Clear the status bar first to print message on it
	ClearStatusBar();

	// Set the Message offset from the status bar
	int msgX = UI.TextMargin;
	int msgY = UI.Height - UI.StatusBarHeight / 2 - UI.FontSize / 2;

	// Print the message
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(UI.FontSize, BOLD, BY_NAME, "Arial");
	pWind->DrawString(msgX, msgY, msg);
	pWind->UpdateBuffer();
}

/* Updates the window with double buffering */
void Output::UpdateScreen() {
	pWind->UpdateBuffer();
}

/* Stores and returns an image with certain coordinates */
void Output::StoreImage(image& img, int x, int y, int width, int height) {
	pWind->StoreImage(img, x, y, width, height);
}

/* Draws a given image to the window */
void Output::DrawImage(const image& img, int x, int y, int width, int height) {
	pWind->DrawImage(&img, x, y, width, height);
}

/* Draws a given PNG image to the window */
void Output::DrawPNG(const string& dir, int x, int y) {
	pWind->DrawPNG(dir, x, y);
}

/* Draws the hovered label */
void Output::DrawLabel(int x, int y, const string& label) const {
	int w, h;
	pWind->SetBrush(UI.DarkColor);
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(UI.FontSize, BOLD, BY_NAME, "Arial");
	pWind->GetStringSize(w, h, label);

	pWind->DrawRectangle(x, y, x + w + UI.TextMargin, y + h + UI.TextMargin);
	pWind->DrawString(x + UI.TextMargin / 2, y + UI.TextMargin / 2, label);
}

/* Draws the selection rectangle from the given coordinates */
void Output::DrawSelectionRectangle(int x1, int y1, int x2, int y2) {
	pWind->SetPen(UI.SelectionColor, 2);
	pWind->DrawRectangle(x1, y1, x2, y2, FRAME);
}

/* Draws the move line from a ceratin to a certain coordinates */
void Output::DrawMoveLine(int x1, int y1, int x2, int y2) {
	pWind->SetPen(WHITE, 2);
	pWind->DrawLine(x1, y1, x2, y2);
}

/* Draws AND gate */
void Output::DrawAND(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\and.jpg" : "Images\\components\\active\\and.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws OR gate */
void Output::DrawOR(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\or.jpg" : "Images\\components\\active\\or.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws NOT gate */
void Output::DrawNOT(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\not.jpg" : "Images\\components\\active\\not.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws NAND gate */
void Output::DrawNAND(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\nand.jpg" : "Images\\components\\active\\nand.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws NOR gate */
void Output::DrawNOR(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\nor.jpg" : "Images\\components\\active\\nor.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws XOR gate */
void Output::DrawXOR(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\xor.jpg" : "Images\\components\\active\\xor.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws XNOR gate */
void Output::DrawXNOR(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\xnor.jpg" : "Images\\components\\active\\xnor.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws AND3 gate */
void Output::DrawAND3(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\and3.jpg" : "Images\\components\\active\\and3.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws NOR3 gate */
void Output::DrawNOR3(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\nor3.jpg" : "Images\\components\\active\\nor3.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws XOR3 gate */
void Output::DrawXOR3(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\xor3.jpg" : "Images\\components\\active\\xor3.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws Buffer gate */
void Output::DrawBuffer(const GraphicsInfo& gfxInfo, bool selected) const {
	string dir = (selected ? "Images\\components\\highlighted\\buffer.jpg" : "Images\\components\\active\\buffer.jpg");
	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LogicGateWidth, UI.LogicGateHeight);
}

/* Draws Switch */
void Output::DrawSwitch(const GraphicsInfo& gfxInfo, bool selected, bool on) const {
	string dir;

	if (UI.AppMode == Mode::SIMULATION && on)
		dir = "Images\\components\\active\\switch_on.jpg";
	else
		dir = (selected ? "Images\\components\\highlighted\\switch_off.jpg" : "Images\\components\\active\\switch_off.jpg");

	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.SwitchWidth, UI.SwitchHeight);
}

/* Draws LED */
void Output::DrawLED(const GraphicsInfo& gfxInfo, bool selected, bool on) const {
	string dir;

	if (UI.AppMode == Mode::SIMULATION && on)
		dir = "Images\\components\\active\\led_on.jpg";
	else
		dir = (selected ? "Images\\components\\highlighted\\led_off.jpg" : "Images\\components\\active\\led_off.jpg");

	pWind->DrawImage(dir, gfxInfo.x1, gfxInfo.y1, UI.LedWidth, UI.LedHeight);
}

/* Draws connection */
void Output::DrawConnection(const vector<GraphicsInfo>& path, bool selected, bool on) {
	color c;

	if (UI.AppMode == Mode::SIMULATION)
		c = (on ? UI.ConnectionOnColor : UI.ConnectionColor);
	else
		c = (selected ? UI.SelectionColor : UI.ConnectionColor);

	pWind->SetPen(c, 2);

	for (int i = 0; i < (int)path.size(); i++) {
		pWind->DrawLine(path[i].x1, path[i].y1, path[i].x2, path[i].y2);
	}
}

/* Checks if the given coordinates is within the drawing area */
bool Output::IsDrawingArea(int x, int y) {
	if (x < 0 || x > UI.Width) return false;
	if (y < UI.ToolBarHeight + UI.GateBarHeight || y > UI.Height - UI.StatusBarHeight) return false;
	return true;
}

/* Checks if the given area of pins is empty */
bool Output::IsEmptyArea(const GraphicsInfo& gfxInfo) const {
	int x1 = gfxInfo.x1, y1 = gfxInfo.y1;
	int x2 = gfxInfo.x2, y2 = gfxInfo.y2;
	getPinIndices(x1, y1);
	getPinIndices(x2, y2);

	if (x1 < 0 || x2 > UI.HorPinsCount || y1 < 0 || y2 > UI.VerPinsCount) {
		return false;
	}

	for (int x = x1; x < x2; x++) {
		for (int y = y1; y < y2; y++) {
			if (mPinGrid[x][y].Type == PinType::GATE && !mPinGrid[x][y].Comp->IsSelected()) return false;	// Occupied area
		}
	}

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
	int n = (int)path.size() - 1;

	for (int i = 1; i < n; i++) {
		// Horizontal line
		if (path[i].y1 == path[i].y2) {
			int x1 = path[i].x1 / UI.PinOffset;
			int x2 = path[i].x2 / UI.PinOffset;
			int y = (path[i].y1 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;

			for (int x = x1; x <= x2; x++) {
				mPinGrid[x][y].Type = (mPinGrid[x][y].Type == EMPTY) ? PinType::HOR_CONNECTION : PinType::INTERSECTING_CONNECTIONS;
				mPinGrid[x][y].Comp = comp;
			}
		}
		// Vertical line
		else {
			int y1 = (path[i].y1 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;
			int y2 = (path[i].y2 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;
			int x = path[i].x1 / UI.PinOffset;

			for (int y = y1; y <= y2; y++) {
				mPinGrid[x][y].Type = (mPinGrid[x][y].Type == EMPTY) ? PinType::VER_CONNECTION : PinType::INTERSECTING_CONNECTIONS;
				mPinGrid[x][y].Comp = comp;
			}
		}
	}
}

/* Clears the pins of the connection */
void Output::ClearConnectionPins(const vector<GraphicsInfo>& path) {
	int n = (int)path.size() - 1;

	for (int i = 1; i < n; i++) {
		// Horizontal line
		if (path[i].y1 == path[i].y2) {
			int x1 = path[i].x1 / UI.PinOffset;
			int x2 = path[i].x2 / UI.PinOffset;
			int y = (path[i].y1 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;

			for (int x = x1; x <= x2; x++) {
				mPinGrid[x][y].Type = PinType::EMPTY;
				mPinGrid[x][y].Comp = NULL;
			}
		}
		// Vertical line
		else {
			int y1 = (path[i].y1 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;
			int y2 = (path[i].y2 - UI.ToolBarHeight - UI.GateBarHeight) / UI.PinOffset;
			int x = path[i].x1 / UI.PinOffset;

			for (int y = y1; y <= y2; y++) {
				mPinGrid[x][y].Type = PinType::EMPTY;
				mPinGrid[x][y].Comp = NULL;
			}
		}
	}
}

/* Returns the grid of pins */
Component* Output::GetComponentAtPin(int x, int y) const {
	getPinIndices(x, y);

	if (x < 0 || x >= UI.HorPinsCount || y < 0 || y >= UI.VerPinsCount) {
		return NULL;
	}

	return mPinGrid[x][y].Comp;
}

/* Returns the shortest available path for the connection, null if no path found */
vector<GraphicsInfo>* Output::GetConnectionPath(const GraphicsInfo& gfxInfo) {
	if (!IsDrawingArea(gfxInfo.x1, gfxInfo.y1) || !IsDrawingArea(gfxInfo.x2, gfxInfo.y2)) {
		return NULL;
	}

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

/* Generate the connection path */
vector<GraphicsInfo>* Output::GenerateConnectionPath(Node& src, Node& dst, Node parents[UI.HorPinsCount][UI.VerPinsCount]) {
	vector<GraphicsInfo>* path = new vector<GraphicsInfo>;
	Node prv = dst;
	Node cur = parents[prv.x][prv.y];
	Node nxt;
	int x1, y1, x2, y2;

	x1 = dst.x * UI.PinOffset + UI.PinMargin - 1;
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

	x1 = src.x * UI.PinOffset - 2;
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

/* Visualize debugging */
void Output::Debug() {
	// ---- JUST FOR TESTING ----
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
			int iX = x, iY = y;
			getPinIndices(iX, iY);

			if (mPinGrid[iX][iY].Type == PinType::GATE) {
				pWind->SetBrush(BLUE);
				pWind->DrawRectangle(x - 5, y - 5, x + 5, y + 5);
			}
			else if (mPinGrid[iX][iY].Type == PinType::INTERSECTING_CONNECTIONS) {
				pWind->SetBrush(RED);
				pWind->DrawRectangle(x - 5, y - 5, x + 5, y + 5);
			}
			else if (mPinGrid[iX][iY].Type == PinType::HOR_CONNECTION || mPinGrid[iX][iY].Type == PinType::VER_CONNECTION) {
				pWind->SetBrush(GREEN);
				pWind->DrawRectangle(x - 5, y - 5, x + 5, y + 5);
			}
			else {
				pWind->DrawPixel(x, y);
			}
		}
	}
}

/* Destructor */
Output::~Output() {
	delete pWind;
	for (int x = 0; x < UI.HorPinsCount; x++) delete[] mPinGrid[x];
	delete[] mPinGrid;
}