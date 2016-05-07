/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include <iostream>
#include "image.h"
#include "error.h"

extern "C" {
  #include "jpegload.h"
}

image::image() {

	bmiImage = NULL;
    ucpImageData = NULL;

    usWidth = 0;
    usHeight = 0;    

}  
  
image::image(string strFileName, imagetype itThisType) {

	bmiImage = NULL;
    ucpImageData = NULL;
    
    Open((char *) strFileName.c_str(), itThisType);
    
}

image::image(const char *cpFileName, imagetype itThisType) {

	bmiImage = NULL;
    ucpImageData = NULL;
    
    if(cpFileName == NULL) {
      throw FILE_NOT_FOUND;
    }
    
    Open(cpFileName, itThisType);
    
}

image::~image() {

	if(bmiImage != NULL) {
	    delete [] bmiImage;
	}
     
    if(ucpImageData != NULL) {
        delete [] ucpImageData;
    }
}

void image::Open(string strFileName, imagetype itThisType) {

    Open((char *) strFileName.c_str(), itThisType);

}

void image::Open(const char *cpFileName, imagetype itThisType) {

	unsigned long i, j;
	unsigned char *ucpTmp;
	int iErrorCode;
	
	if(cpFileName == NULL) {
      throw FILE_NOT_FOUND;
    }
    
    itType = itThisType;

	if(bmiImage != NULL) {
	    delete [] bmiImage;
	}

    if(ucpImageData != NULL) {
        delete [] ucpImageData;
    }
 
	bmiImage = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
	if(bmiImage == NULL) {
        throw OUT_OF_MEMORY;
	}

	memset(bmiImage, 0, sizeof(BITMAPINFOHEADER));
	
	bmiImage->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiImage->bmiHeader.biPlanes = 1;
	bmiImage->bmiHeader.biBitCount = 32;
	bmiImage->bmiHeader.biCompression = BI_RGB;
	bmiImage->bmiHeader.biSizeImage = 0;
	bmiImage->bmiHeader.biClrUsed = 0;
	bmiImage->bmiHeader.biClrImportant = 0;

    if(itType == JPEG) {
        iErrorCode = jpegload(cpFileName, &usWidth, &usHeight, &ucpTmp);
        if(iErrorCode == -1) {
            throw FILE_NOT_FOUND;
        } else if(iErrorCode == -2) {
            delete [] bmiImage;
            throw OUT_OF_MEMORY;          
        }

		bmiImage->bmiHeader.biWidth = usWidth;
		bmiImage->bmiHeader.biHeight = -usHeight;
	
		ucpImageData = new unsigned char[(usWidth * 4) * usHeight];
		if(ucpImageData == NULL) {
   		    throw OUT_OF_MEMORY;
		}

        for(i = 0, j = 0; i < ((usWidth * 3) * usHeight); i += 3, j += 4) {
		    ucpImageData[j] = ucpTmp[i + 2];
		    ucpImageData[j + 1] = ucpTmp[i + 1];
			ucpImageData[j + 2] = ucpTmp[i];
			ucpImageData[j + 3] = 0;
		}

		free(ucpTmp);

		ucTransRed = 0;
		ucTransGreen = 0;
		ucTransBlue = 0;

	} else {
	
	    cout << "Fatal Error: Unsupported image type!" << endl;
	
	}

}

void image::operator=(image &imgOther) {

    itType = imgOther.itType;
    
	bmiImage = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
	if(bmiImage == NULL) {
        throw OUT_OF_MEMORY;
	}
	
	memset(bmiImage, 0, sizeof(BITMAPINFOHEADER));	
	
	bmiImage->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiImage->bmiHeader.biPlanes = 1;
	bmiImage->bmiHeader.biBitCount = 32;
	bmiImage->bmiHeader.biCompression = BI_RGB;
	bmiImage->bmiHeader.biSizeImage = 0;
	bmiImage->bmiHeader.biClrUsed = 0;
	bmiImage->bmiHeader.biClrImportant = 0;

    usWidth = imgOther.usWidth;
    usHeight = imgOther.usHeight;

    bmiImage->bmiHeader.biWidth = usWidth;
	bmiImage->bmiHeader.biHeight = -usHeight;

    ucpImageData = new unsigned char[(usWidth * 4) * usHeight]; 
    if(ucpImageData == NULL) {
   	    throw OUT_OF_MEMORY;
	}
    
    memcpy(ucpImageData, imgOther.ucpImageData, (unsigned int) (usWidth * 4) * usHeight);

}

image::image(image &imgOther) {

    itType = imgOther.itType;

	bmiImage = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
	if(bmiImage == NULL) {
        throw OUT_OF_MEMORY;
	}
	
    memset(bmiImage, 0, sizeof(BITMAPINFOHEADER));
	
	bmiImage->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiImage->bmiHeader.biPlanes = 1;
	bmiImage->bmiHeader.biBitCount = 32;
	bmiImage->bmiHeader.biCompression = BI_RGB;
	bmiImage->bmiHeader.biSizeImage = 0;
	bmiImage->bmiHeader.biClrUsed = 0;
	bmiImage->bmiHeader.biClrImportant = 0;

    usWidth = imgOther.usWidth;
    usHeight = imgOther.usHeight;

    bmiImage->bmiHeader.biWidth = usWidth;
	bmiImage->bmiHeader.biHeight = -usHeight;

    ucpImageData = new unsigned char[(usWidth * 4) * usHeight]; 
    if(ucpImageData == NULL) {
   	    throw OUT_OF_MEMORY;
	}
    
    memcpy(ucpImageData, imgOther.ucpImageData, (unsigned int) (usWidth * 4) * usHeight);

}