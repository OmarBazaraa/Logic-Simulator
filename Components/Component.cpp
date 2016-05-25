#include "Component.h"

/* Constructor */
Component::Component() {
	mSelected = false;
	mDeleted = false;
}

/* Constructor */
Component::Component(const GraphicsInfo& gfxInfo) : Component() {
	mGfxInfo = gfxInfo;	
}

/* Sets the selection of the component */
void Component::SetSelected(bool s) {
	mSelected = s;
}

/* Returns whether the component is selected or not */
bool Component::IsSelected() const {
	return mSelected;
}

/* Returns whether the component is deleted or not */
bool Component::IsDeleted() const {
	return mDeleted;
}

/* Sets the label of the component */
void Component::SetLabel(const string& label) {
	if (!label.empty()) {
		mLabel = label;
	}
}

/* Returns the label of the component */
string Component::GetLabel() const {
	return mLabel;
}

/* Returns the bound coordinates of the component */
GraphicsInfo Component::GetGraphicsInfo() const {
	return mGfxInfo;
}

/* Selects the component */
void Component::Select() {
	if (UI.AppMode == Mode::DESIGN) {
		mSelected = !mSelected;
	}
}

/* Destructor, must be virtual */
Component::~Component() {

}