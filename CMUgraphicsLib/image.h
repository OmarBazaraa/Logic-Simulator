/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#ifndef WINDOWS_H
  #define WINDOWS_H
  #include <windows.h>
#endif //WINDOWS_H

#include "version.h"

#ifdef __MS_VISUALCPP__
  using namespace std;
#endif //__MS_VISUALCPP__

// Can currently only handles two image formats
enum imagetype {
	JPEG,     // Only supported file format
	SCREEN    // Format created when grabbing image data from the screen
};

class image {

  private:
    // Height and width of the image
	unsigned short usHeight, usWidth;
	
	// The image data
    unsigned char *ucpImageData;
    
    // Transparent color info -- currently not used
	unsigned char ucTransRed, ucTransGreen, ucTransBlue;
	
	// The file format this image was created from
	imagetype itType;

    // Windows API stuff
	BITMAPINFO *bmiImage;
	HDC dcTempBuffer;
	HBITMAP bmapTempBuffer;

    // Transparency?
	int iTransparent;

    // Allow the window class to get at us
	friend class window;

  public:
  
    image();
	image(string strFileName, imagetype itThisType = JPEG);
    image(const char *cpFileName, imagetype itThisType = JPEG);
	~image();
	
	// Open an image file, currently the only value imagetype is 
	// JPEG
	void Open(string strFileName, imagetype itThisType = JPEG);
	void Open(const char *cpFileName, imagetype itThisType = JPEG);
	
	// Find out the dimensions of our image
	unsigned long GetWidth() { return usWidth; }
	unsigned long GetHeight() { return usHeight; }

    // Copy images 
    void operator=(image &imgOther); 
    
    // Possible, but a bad idea... Maybe use as an example of
    // why passing by value for large data structures is bad.
    image(image &imgOther);


};

#endif  //IMAGE_H