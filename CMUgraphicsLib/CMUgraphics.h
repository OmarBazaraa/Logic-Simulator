/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#ifndef CMUGRAPHICS_H
#define CMUGRAPHICS_H

#include <string>

#ifndef WINDOWS_H
  #define WINDOWS_H
  #include <windows.h>
#endif //WINDOWS_H

#include "mousequeue.h"
#include "keyqueue.h"
#include "image.h"
#include "colors.h"
#include "version.h"

// Aproximate value of Pi, used in some calculations
const double cdPi = 3.141592653589793238462643383279;

const int ciDefWindWidth = 640;
const int ciDefWindHeight = 480;
const int ciDefWindXPos = CW_USEDEFAULT;
const int ciDefWindYPos = 0;

const char ccDefWindClassName[] = "CMUgraphics Library";
const char ccDefWindTitle[] = "Graphics Window";

const int ciDefBrushSize = 1;

enum drawstyle {
	NONE,
    FILLED,
	FRAME,
	INVERTED,
	TRANSLUCENT,  // Currently Unsupported
	ANTIALIASED   // Ditto
};

// set text style parameters

// Font Styles... Used by logically ORing them together
// so to get bold underlined text you would use
// BOLD | UNDERLINED
const unsigned char PLAIN =      0x00;
const unsigned char BOLD =       0x01;
const unsigned char ITALICIZED = 0x02;
const unsigned char UNDERLINED = 0x04;
const unsigned char STRIKEOUT  = 0x08;

// Generic Font family's
enum fontfamily {
	BY_NAME,	// use font name instead of abstract type
	MODERN,		// monospace with or without serifs
	ROMAN,		// variable width with serifs
	SCRIPT,		// like handwriting
	SWISS		  // variable width without serifs
};

// Units of angluar measure
enum angletype {
	DEGREES,
	RADIANS
};


class window {

  private:
  
    // Various Win32 Data structures
	const HINSTANCE hInstance;
    WNDCLASS wndcWindow;
    HWND hwndWindow;

    // Display Contexts - dcActive is always the DC we draw to
    // dcScreen is the screen, and will be the same as dcActive
    // if we aren't using double buffering
    HDC dcActive;
    HDC dcScreen;

    // Bitmap for double buffering
    HBITMAP bmapBuffer;
    HBITMAP bmapBufferOld;
    
    // Pen, brush, and font objects for drawing stuff
    HPEN penObject;
    HBRUSH brshObject;
	HFONT fontObject;
	
	// To be a good neighboor and store previously selected objects
	HPEN penOldObject;
	HBRUSH brshOldObject;
	HFONT fontOldObject;

    color colBrsh;
    color colPen;
    
    int iPenWidth;

    // Window size information
	const int iWindowWidth, iWindowHeight;

    // True if we're double buffering, false if we're not.
	bool bDoubleBuffer;
	
    // Current mouse position
	int iMouseX, iMouseY;
	  
	// Keyboard and mouse input queues
	mqueue mqueInput;
	kqueue kqueInput;

    // The current state of the left and right buttons
    buttonstate bsLeft;
    buttonstate bsRight;

    // Kludge to solve problems with the stupid way Win32 messaging system works
    inline void ProcessMessage();  

    // Keep track of current drawing state to prevent unneccessay API calls
   	void ChangeDrawStyle(drawstyle dsNewStyle);
   	void SetFontStyle();
    // Function to be a good neighboor and put things back the way they were
   	void RestoreDrawStyle();
   	void RestoreFontStyle();

    // Allow the windowinput class to muck with our data structures (needed to properly
    // handle input)
    friend class windowinput;

    // Prevent inadvertent copying... 
    void operator=(window &); 
    window(window &);
    
  public:
 
    // Create a new window! iWindWidth and iWindHeight will change the size of 
    // the window created. iWindXPos and iWindYPos is the position the window
    // will appear on the screen
    window(const int iWindWidth = ciDefWindWidth, const int iWindHeight = ciDefWindHeight, const int iWindXPos = ciDefWindXPos, const int iWindYPos = ciDefWindYPos);

    // Window destructor
  	~window();

    // If this window is the last window on screen, the default behavior is that in
    // the window destructor the program waits for a mouse click before closing 
    // the window.  This function will allow you to change this behavior.  The 
    // default value is true.  It will return whatever the previous state was.
    bool SetWaitClose(const bool bSetting) const;

    // Turn double buffering on or off.  The way things currently work the background
    // color of the double buffer defaults to black, whereas the normal screen defaults
    // to white.  Returns the old state.
	bool SetBuffering(const bool bSetting);
	  
	// When double buffering is turned on this will copy the offscreen buffer to 
	// the screen 
	void UpdateBuffer();

    // Allows the user to change what the title of the window.  Accepts string
    // or C-strings for input
    void ChangeTitle(const char *cpNewTitle);
    void ChangeTitle(const string strNewTitle);

    // Functions to get information about the size of the window
    int GetWidth() const;
    int GetHeight() const;
    void GetWindowSize(int &iX, int &iY) const;

    // Get information on the current state of the mouse buttons and it's position
    buttonstate GetButtonState(const button btMouse, int &iX, int &iY);
 
    // Gets the current mouse coordinates
    void GetMouseCoord(int &iX, int &iY);
    
    // Removes the next mouse click event from the queue
    // iX and iY will contain the location of the click
    // and the clicktype return willed allow the user to 
    // determine which mouse button was clicked, and 
    // if the click was a double click 
    // (see the clicktype enum in mousequeue.h)
 	clicktype GetMouseClick(int &iX, int &iY);

    // WaitMouseClick works the same as above but will only return 
    // if there is a mouse click event in the queue, otherwise
    // it will wait for one
	clicktype WaitMouseClick(int &iX, int &iY);
 	  
    // Removes the next keyboard event from the queue
    // stuffs the key value into ucKey, and returns the
    // type of key that was pressed    
    // (see the keytype enum in keyqueue.h)
	keytype GetKeyPress(char &cKey);
	 
	// Same as above, but won't return unless there is a key
	// event in the queue.  As a result it will wait until
	// there is one
	keytype WaitKeyPress(char &cKey);

    // These two functions flush all waiting input out of the
    // mouse and keyboard input queues.  This is necessary
    // because if someone accidentally hits a key or clicks 
    // the mouse that event will stay in the buffer until it
    // is removed, which may be at a time that input would not
    // be wanted by the user
    void FlushKeyQueue();
    void FlushMouseQueue();

    // Sets the color of the current brush, which is used when drawing with
    // the FILLED style.  Returns the last selected color.
	color SetBrush(const double dRed, const double dGreen, const double dBlue);
	  
	// Same as above, but allows you to use characters instead of doubles,
	// which is faster.  Returns the last selected color.
  	color SetBrush(const unsigned char ucRed, const unsigned char ucGreen, const unsigned char ucBlue);

	// Set the brush color using a color object.  Returns the last selected color.
  	color SetBrush(const color &colBrush);
  	
  	// Set the color and size (if you specify the size) of the current pen, which
  	// is used with drawing with the FRAME style and outlines entities drawing in
  	// the FILLED style.  Returns the last selected color.
	color SetPen(const double dRed, const double dGreen, const double dBlue, const int iWidth = ciDefBrushSize);
	  
	// Same as above, just allowing the use of characters instead of doubles
	// for speed.  Returns the last selected color.   
	color SetPen(const unsigned char ucRed, const unsigned char ucGreen, const unsigned char ucBlue, const int iWidth = ciDefBrushSize);

    // Set the pen color and size using a color object.  Returns the last selected color.
	color SetPen(const color &colPen, const int iWidth = ciDefBrushSize);

    // Sets the current font.  See the enums at the top of this file for info on 
    // the fontstyle and fontfamily types.  C-String and String versions
  	void SetFont(const int iSize, const unsigned short usStyle, const fontfamily ffFamily, const char* cpFontName = NULL);

    // Draws a pixel at (iX, iY) in the current color
    void DrawPixel(const int iX, const int iY);

    // Draws a line from (iX1, iY1) to (iX2 - 1, iY2 - 1), because the Win32 API is 
    // wierd.  This actually sort of makes sense, if you think about it, and I decided
    // not to hardcode in +1's to make up for this fact.  Currently the only valid
    // drawstyle is FRAME.  If you try to use any of the others it will quit with 
    // a fatal error
  	void DrawLine(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle = FRAME);
  	
  	// Draws a rectangle from with the same sort of off by one as DrawLine
  	// Valid drawstyles are FRAME, FILLED, and INVERTED.  Default drawing style
  	// is FILLED.  If you want a rounded rectangle, use the last two parameters, 
  	// iWidth and iHeight, to adjust the size of the fillets
  	void DrawRectangle(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle = FILLED, const int iWidth = 0, const int iHeight = 0);

    // Draws a triangle with vertices (iX1, iY1), (iX2, iY2), and (iX3, iY3)
    // Valid drawstyles are FRAME, FILLED, and INVERTED.
  	void DrawTriangle(const int iX1, const int iY1, const int iX2, const int iY2, const int iX3, const int iY3, const drawstyle dsStyle = FILLED);
  	
  	// Works the same as DrawTriangle, but takes a pointer (or an array) of X and Y values
  	// The number of elements in ipX and ipY must be the same, and iVertices must be 
  	// no greater than the number of elements in the two arrays, or your program may
  	// very well crash.  There is no way I can really guard against this problem
    void DrawPolygon(const int* ipX, const int* ipY, const int iVertices, const drawstyle dsStyle = FILLED);

    // Draws a circle centered at (iX, iY) with a radius of iRadius.  Valid drawstyles 
    // are FRAME, FILLED, and INVERTED.
    void DrawCircle(const int iX, const int iY, const int iRadius, const drawstyle dsStyle = FILLED);

    // Draws an ellipse inside the rectangle bounded by (iX1, iY1) and (iX2, iY2)
    // Valid drawstyles are FRAME, FILLED, and INVERTED
	void DrawEllipse(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle = FILLED); 

    // Draws a section of and ellipse inside the rectangle bounded by (iX1, iY1) and (iX2, iY2), from
    // dStartAngle to dEndAngle.  atInfo may be set to RADIANS for those who perfer to use that system
    // over DEGREES. Valid drawstyles are FRAME, FILLED, and INVERTED
	void DrawArc(const int iX1, const int iY1, const int iX2, const int iY2, double dStartAngle, double dEndAngle, const drawstyle dsStyle = FRAME, const angletype atInfo = DEGREES);

    // Draws a Bezier curve.  The start and end points are specified by (iX1, iY1) and (iX4, iY4). 
    // (iX2,iY2) and (iX3, iY3) specify control points that affect the shape of the curve.
    // The only valid drawstyle currently is FRAME
	void DrawBezier(const int iX1, const int iY1, const int iX2, const int iY2, const int iX3, const int iY3, const int iX4, const int iY4, const drawstyle dsStyle = FRAME);

    // Draws a string starting at the location given by (iX, iY) using the font set by SetFont(..)
	void DrawString(const int iX, const int iY, const char* cpText);
	void DrawString(const int iX, const int iY, const string strText);

    // Draws an integer or double starting at the location given by (iX, iY) using the font set by SetFont(..)
	void DrawInteger(const int iX, const int iY, const long lNumber);
	void DrawDouble(const int iX, const int iY, const double dNumber);

    // Returns the width and height of a string drawn using the current
    // font
	void GetStringSize(int &iWidth, int &iHeight, const char* cpText);
	void GetStringSize(int &iWidth, int &iHeight, const string strText);

    // Returns the width and height of a number drawn using the current
    // font    
    void GetIntegerSize(int &iWidth, int &iHeight, const long lNumber);
    void GetDoubleSize(int &iWidth, int &iHeight, const double dNumber);

    // Draws an image at the location specified by (iX, iY).  The iWidth and iHeight Parameters can be used to 
    // scale an image.  Transparent images will not scale, and won't be affected by the iWidth and iHeight
    // parameters
	void DrawImage(const image *imgThis, const int iX, const int iY, const int iWidth = -1, const int iHeight = -1);
	void DrawImage(const image &imgThis, const int iX, const int iY, const int iWidth = -1, const int iHeight = -1);

    // Get the color of the pixel at location (iX, iY)
    color GetColor(const int iX, const int iY);

    void GetColor(const int iX, const int iY, double &dRed, double &dGreen, double &dBlue);

    double GetRed(const int iX, const int iY);
    double GetGreen(const int iX, const int iY);
    double GetBlue(const int iX, const int iY);
    
    // Grabs a section of the section of the screen starting at (iX, iY) iWidth wide and iHeight tall
    // and stores it in an image object 
	void StoreImage(image *imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight);
	void StoreImage(image &imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight);

    // Prints the contents of the window
    void Print();
   
};

#endif  //CMUGRAPHICS_H