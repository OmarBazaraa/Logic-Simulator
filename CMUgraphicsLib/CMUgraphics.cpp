/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include <string>
#include <iostream>
#include <cstdio>
#include <cmath>

#include "CMUgraphics.h"
#include "error.h"
#include "windowinput.h"

// Keeps track of key and mouse input and redirects it to the
// appropriate window object
windowinput* wipInput = NULL;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	
	switch(msg) {
	  case WM_LBUTTONDOWN:
        if(wipInput != NULL) {
            wipInput->SetMouseState(hwnd, LEFT_BUTTON, BUTTON_DOWN, LOWORD(lParam), HIWORD(lParam));
		}
		SetCapture(hwnd);
 		return 0;

	  case WM_RBUTTONDOWN:
        if(wipInput != NULL) {
            wipInput->SetMouseState(hwnd, RIGHT_BUTTON, BUTTON_DOWN, LOWORD(lParam), HIWORD(lParam));
		}
		SetCapture(hwnd);
 		return 0;	
	
	  case WM_LBUTTONUP:
        if(wipInput != NULL) {
            wipInput->SetMouseState(hwnd, LEFT_BUTTON, BUTTON_UP, LOWORD(lParam), HIWORD(lParam));
            wipInput->SetClickInfo(hwnd, LEFT_CLICK, LOWORD(lParam), HIWORD(lParam));
		}
		ReleaseCapture();
 		return 0;

	  case WM_RBUTTONUP:
        if(wipInput != NULL) {
            wipInput->SetMouseState(hwnd, RIGHT_BUTTON, BUTTON_UP, LOWORD(lParam), HIWORD(lParam));
            wipInput->SetClickInfo(hwnd, RIGHT_CLICK, LOWORD(lParam), HIWORD(lParam));
		}
		ReleaseCapture();
 		return 0;

	  case WM_MOUSEMOVE:
	  
        if(wipInput != NULL) {
            wipInput->SetMouseCoord(hwnd, LOWORD(lParam), HIWORD(lParam));
		}
 		return 0;

	  case WM_KEYDOWN:
	    switch(wParam) {
		  case VK_END:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, ARROW, 1);
			}
			break;

		  case VK_DOWN:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, ARROW, 2);
			}
			break;

		  case VK_NEXT:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, ARROW, 3);
			}
			break;

		  case VK_LEFT:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, ARROW, 4);
			}
			break;

		  case VK_RIGHT:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, ARROW, 6);
			}
			break;

		  case VK_HOME:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, ARROW, 7);
			}
			break;

		  case VK_UP:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, ARROW, 8);
			}
			break;

		  case VK_PRIOR:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, ARROW, 9);
			}
			break;

		  case VK_ESCAPE:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, ESCAPE, 1);
			}
			break;

		  case VK_F1:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 1);
			}
			break;

		  case VK_F2:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 2);
			}
			break;

		  case VK_F3:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 3);
			}
			break;

		  case VK_F4:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 4);
			}
			break;


		  case VK_F5:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 5);
			}
			break;

		  case VK_F6:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 6);
			}
			break;

		  case VK_F7:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 7);
			}
			break;

		  case VK_F8:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 8);
			}
			break;

		  case VK_F9:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 9);
			}
			break;

		  case VK_F10:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 10);
			}
			break;

		  case VK_F11:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 11);
			}
			break;

		  case VK_F12:
            if(wipInput != NULL) {
                wipInput->SetKeyInfo(hwnd, FUNCTION, 12);
			}
			break;
		}
		return 0;

	  case WM_CHAR:
	    if(wipInput != NULL) {
            wipInput->SetKeyInfo(hwnd, ASCII, (char) wParam);
		}
		return 0;
	}
	
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

window::window(const int iWindWidth, const int iWindHeight, const int iWindXPos, const int iWindYPos) :
hInstance(GetModuleHandle(0)), iWindowWidth(iWindWidth), iWindowHeight(iWindHeight) {

	iMouseX = -1;
	iMouseY = -1;

	wndcWindow.style = 0;
	wndcWindow.lpfnWndProc = WindowProc;
	wndcWindow.cbClsExtra = 0;
	wndcWindow.cbWndExtra = 0;
	wndcWindow.hInstance = hInstance;
	wndcWindow.hIcon = NULL;
	wndcWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcWindow.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcWindow.lpszMenuName = NULL;
	wndcWindow.lpszClassName = ccDefWindClassName;
	RegisterClass(&wndcWindow);

	hwndWindow = CreateWindow(ccDefWindClassName, ccDefWindTitle, WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX , iWindXPos, 
		                      iWindYPos, iWindowWidth + GetSystemMetrics(SM_CXEDGE), 
							  iWindowHeight + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYEDGE) - 1, // Not sure why I need to subtract 1
							  HWND_DESKTOP, NULL, hInstance, 0);
							  							  
	if (hwndWindow) {
		ShowWindow(hwndWindow, SW_SHOW);
		dcScreen = GetDC(hwndWindow);
		
        // No doublebuffering yet so dcActive is the same as dcScreen
		dcActive = dcScreen;
	}
	
    penOldObject = penObject = NULL;
	brshOldObject = brshObject = NULL;
	fontOldObject = fontObject = NULL;
	bmapBuffer = NULL;
	
	bsLeft = BUTTON_UP;
	bsRight = BUTTON_UP;
	
	bDoubleBuffer = false;

    SetPen(WHITE, 0);
    SetBrush(WHITE);
    SetFont(10, PLAIN, SWISS);

	if(wipInput == NULL) {
		wipInput = new windowinput(hwndWindow, this);
		if(wipInput == NULL) {
			throw OUT_OF_MEMORY;
		}
    } else {
	    wipInput->AddWindow(hwndWindow, this);	
	}
}

window::~window() {

    int iX, iY;

    if(dcScreen != NULL) {
        if(ReleaseDC(hwndWindow, dcScreen) == 0) {
		    cout << "Fatal Error: Failed to release dcScreen in window class destructor!" << endl;        
        }
        if(dcActive == dcScreen) {
          dcActive = NULL;
        }
        dcScreen = NULL;
    }

	if (dcActive != NULL) {
		if(DeleteDC(dcActive) != TRUE) {
		    cout << "Fatal Error: Failed to delete dcActive in window class destructor!" << endl;
		}
	}
	
	if(penObject != NULL) { 
	    if(DeleteObject(penObject) != TRUE) {
	        cout << "Fatal Error: Failed to delete penObject in window class destructor!" << endl;	        	    
	    }
		penObject = NULL; 
	}

	if(brshObject != NULL) { 
	    if(DeleteObject(brshObject) != TRUE) {
	        cout << "Fatal Error: Failed to delete brshObject in window class destructor!" << endl;	        	    	    
	    }
		brshObject = NULL; 
	}

	if(fontObject != NULL) {
	    if(DeleteObject(fontObject) != TRUE) {
	        cout << "Fatal Error: Failed to delete fontObject in window class destructor!" << endl;	        	    	    
	    }
		fontObject = NULL; 
	}

    if(bmapBuffer != NULL) {
    	if(DeleteObject(bmapBuffer) != TRUE) {
	        cout << "Fatal Error: Failed to delete bmapBuffer in window class destructor!" << endl;	        	    
    	}
    	bmapBuffer = NULL;
    }

    if(wipInput->Count() == 1) {
        if(wipInput->bWaitClose == true) {
          FlushMouseQueue();
          // Can't use cout because it's destructor might be called before the 
          // window destructor if the window is in the global scope.
          printf("Click mouse in the graphics window to finish execution.\n");
          WaitMouseClick(iX, iY);
        }
        wipInput->RemoveWindow(hwndWindow);
  	    delete wipInput;
   	    wipInput = NULL;
   	} else {
   	    wipInput->RemoveWindow(hwndWindow);   	
   	}


    DestroyWindow(hwndWindow);

}


inline void window::ProcessMessage() {

    MSG msgStruct;
	
    if(PeekMessage(&msgStruct, hwndWindow, 0, 0, PM_REMOVE)) {
	    TranslateMessage(&msgStruct);
		DispatchMessage(&msgStruct);
	}
}

void window::ChangeDrawStyle(drawstyle dsNewStyle) {

    switch(dsNewStyle) {
      case FILLED:
	    penOldObject = (HPEN) SelectObject(dcActive, penObject);
		brshOldObject = (HBRUSH) SelectObject(dcActive, brshObject);
		SetROP2(dcActive, R2_COPYPEN);
		break;

      case FRAME:
		penOldObject = (HPEN) SelectObject(dcActive, penObject);
		brshOldObject = (HBRUSH) SelectObject(dcActive, GetStockObject(NULL_BRUSH));
		SetROP2(dcActive, R2_COPYPEN);
		break;

      case INVERTED:
		penOldObject = (HPEN) SelectObject(dcActive, GetStockObject(BLACK_PEN));
		brshOldObject = (HBRUSH) SelectObject(dcActive, GetStockObject(BLACK_BRUSH));
		SetROP2(dcActive, R2_NOT);
		break;

      default:
        cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
		break;
  	}

}

void window::RestoreDrawStyle() {

    SelectObject(dcActive, penOldObject);
    SelectObject(dcActive, brshOldObject);

}

bool window::SetWaitClose(const bool bSetting) const {

  bool bReturnVal;
  
  bReturnVal = wipInput->bWaitClose;
  wipInput->bWaitClose = bSetting;

  return bReturnVal;
}

bool window::SetBuffering(const bool bSetting) {

    bool bReturnVal;

	ProcessMessage(); // Kludge

    // Is this changing the setting?
    if(bDoubleBuffer == bSetting) {
        return bDoubleBuffer;
    } else {
        bReturnVal = bDoubleBuffer;
	    bDoubleBuffer = bSetting;
    }
    
	if(bDoubleBuffer == true) {

	    bmapBuffer = CreateDiscardableBitmap(dcActive, iWindowWidth, iWindowHeight);

		dcScreen = dcActive;

        dcActive = CreateCompatibleDC(dcScreen);	
        if(dcActive != NULL) {
            bmapBufferOld = (HBITMAP) SelectObject(dcActive, bmapBuffer);
        }
        
        SetPen(WHITE);
        SetBrush(WHITE);
        DrawRectangle(0, 0, iWindowWidth - 1, iWindowHeight - 1);

	} else {
	
	    SelectObject(dcActive, bmapBufferOld);
	
  	    if(dcActive != NULL) {
		    if(DeleteDC(dcActive) != TRUE) {
		        cout << "Fatal Error: Failed to delete dcActive in SetBuffering!" << endl;
		    }
		    dcActive = NULL;
	    }
	    
	    if(bmapBuffer != NULL) {
	        if(DeleteObject(bmapBuffer) != TRUE) {
	            cout << "Fatal Error: Failed to delete bmapBuffer in SetBuffering!" << endl;	    	            
	        }
	        bmapBuffer = NULL;
	    }
	
		dcActive = dcScreen;

	}
	
	return bReturnVal;
}

void window::UpdateBuffer() {

	ProcessMessage(); // Kludge
		
	if(bDoubleBuffer != false) {
        if(BitBlt(dcScreen, 0, 0, iWindowWidth - 1, iWindowHeight - 1, dcActive, 0, 0, SRCCOPY) != TRUE) {
            cout << "Fatal Error: Failed to BitBlt in UpdateBuffer!" << endl;
        }
	}
}

void window::ChangeTitle(const char* cpNewTitle) {

	ProcessMessage(); // Kludge
    SetWindowText(hwndWindow, cpNewTitle);

}

void window::ChangeTitle(string strNewTitle) {

	ChangeTitle((char *) strNewTitle.c_str());

}

int window::GetWidth() const {

    return iWindowWidth;

}

int window::GetHeight() const {

    return iWindowHeight;

}

void window::GetWindowSize(int &iX, int &iY) const {

	iX = iWindowWidth;
	iY = iWindowHeight;
}

void window::GetMouseCoord(int &iX, int &iY) {

    ProcessMessage(); // Kludge

	iX = iMouseX;
	iY = iMouseY;
}

buttonstate window::GetButtonState(const button btMouse, int &iX, int &iY) {

    ProcessMessage(); // Kludge

	iX = iMouseX;
	iY = iMouseY;
	
	if(btMouse == LEFT_BUTTON) {
	    return bsLeft;
	} else {
	    return bsRight;
	}
}

clicktype window::GetMouseClick(int &iX, int &iY) {

	mqueuenode* mqueTmp;
    clicktype ctTmp;

    ProcessMessage(); // Kludge

	mqueTmp = mqueInput.Remove();
	if(mqueTmp != NULL) {
		iX = mqueTmp->iX;
		iY = mqueTmp->iY;
        ctTmp = mqueTmp->ctInfo;

		delete mqueTmp;
		return ctTmp;

	} else {
		iX = -1;
		iY = -1;
		return NO_CLICK;
	}
}


keytype window::GetKeyPress(char &cKey) {

	kqueuenode* kqueTmp;
    keytype ktTmp;

    ProcessMessage(); // Kludge

	kqueTmp = kqueInput.Remove();
	if(kqueTmp != NULL) {
		cKey = kqueTmp->cValue;
        ktTmp = kqueTmp->ktInfo;

		delete kqueTmp;
		return ktTmp;

	} else {
		cKey = 0;
		return NO_KEYPRESS;
	}
}

clicktype window::WaitMouseClick(int &iX, int &iY) {

	mqueuenode* mqueTmp;
    clicktype ctTmp;

	while(true) {
        ProcessMessage(); // Kludge

	    mqueTmp = mqueInput.Remove();
	    if(mqueTmp != NULL) {
	        iX = mqueTmp->iX;
		    iY = mqueTmp->iY;
            ctTmp = mqueTmp->ctInfo;

		    delete mqueTmp;
		    return ctTmp;
		}
	}
}

keytype window::WaitKeyPress(char &cKey) {

	kqueuenode* kqueTmp;
    keytype ktTmp;

	while(true) {
        ProcessMessage(); // Kludge

	    kqueTmp = kqueInput.Remove();
	    if(kqueTmp != NULL) {
		    cKey = kqueTmp->cValue;
            ktTmp = kqueTmp->ktInfo;

    		delete kqueTmp;
	    	return ktTmp;
		}
	}
}

void window::FlushKeyQueue() {

    ProcessMessage(); // Kludge
	kqueuenode* kqueTmp;
    while((kqueTmp = kqueInput.Remove()) != NULL) {
		delete kqueTmp;
	}

}

void window::FlushMouseQueue() {

    ProcessMessage(); // Kludge
	mqueuenode* mqueTmp;
    while((mqueTmp = mqueInput.Remove()) != NULL) {
		delete mqueTmp;
	}

}

color window::SetBrush(const double dRed, const double dGreen, const double dBlue) {

	return SetBrush((unsigned char)(dRed * 255), (unsigned char)(dGreen * 255), (unsigned char)(dBlue * 255));

}

color window::SetBrush(const color &colBrush) {

    return SetBrush(colBrush.ucRed, colBrush.ucGreen, colBrush.ucBlue);

}

color window::SetBrush(const unsigned char ucRed, const unsigned char ucGreen, const unsigned char ucBlue) {

    color colReturn;

	ProcessMessage(); // Kludge

    colReturn = colBrsh;

	if (brshObject != NULL) { 
	    if(DeleteObject(brshObject) != TRUE) {
	        cout << "Fatal Error: Failed to delete brshObject in SetBrush!" << endl;	    	    
	    }
		brshObject = NULL; 
	}
	
	colBrsh.ucRed = ucRed;
	colBrsh.ucGreen = ucGreen;
	colBrsh.ucBlue = ucBlue;
	
	brshObject = CreateSolidBrush(RGB(ucRed, ucGreen, ucBlue));

    return colReturn;
}

color window::SetPen(const double dRed, const double dGreen, const double dBlue, const int iWidth) {

	return SetPen((unsigned char)(dRed * 255), (unsigned char)(dGreen * 255), (unsigned char)(dBlue * 255), iWidth);
}

color window::SetPen(const color &colPen, const int iWidth) {

    return SetPen(colPen.ucRed, colPen.ucGreen, colPen.ucBlue, iWidth);

}

color window::SetPen(const unsigned char ucRed, const unsigned char ucGreen, const unsigned char ucBlue, const int iWidth) {

    color colReturn;

	ProcessMessage(); // Kludge

    colReturn = colPen;

	if (penObject != NULL) { 
	    if(DeleteObject(penObject) != TRUE) {
	        cout << "Fatal Error: Failed to delete penObject in SetPen!" << endl;	    
	    }
		penObject = NULL; 
	}

    iPenWidth = iWidth;
    colPen.ucRed = ucRed;
    colPen.ucGreen = ucGreen;
    colPen.ucBlue = ucBlue;

    // Not the best place to put it, but I didn't want to create
    // too many functions to set colors.
    SetTextColor(dcActive, RGB(ucRed, ucGreen, ucBlue));
  
	penObject = CreatePen(PS_INSIDEFRAME, iWidth, RGB(ucRed, ucGreen, ucBlue));
	
	return colReturn;
}

void window::SetFont(const int iSize, const unsigned short usStyle, const fontfamily ffFamily, const char *cFontName) {

	LOGFONT lf;

    ProcessMessage(); // Kludge
	
    memset(&lf, 0, sizeof(LOGFONT));
	
	if(fontObject != NULL) { 
	    if(DeleteObject(fontObject) != TRUE) {
            cout << "Fatal Error: Failed to delete fontObject in SetFont!" << endl;	        	    		    	    
	    }
		fontObject = NULL; 
	}
	
	lf.lfHeight = iSize;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;

	if((usStyle & BOLD) == BOLD) {
	    lf.lfWeight = FW_BOLD;
	} else {
	    lf.lfWeight = FW_NORMAL;
	}

	if((usStyle & ITALICIZED) == ITALICIZED) {
	    lf.lfItalic = true;
	} else {
		lf.lfItalic = false;
	}

	if((usStyle & UNDERLINED) == UNDERLINED) {
        lf.lfUnderline = true;
	} else {
        lf.lfUnderline = false;
	}

	if((usStyle & STRIKEOUT) == STRIKEOUT) {
        lf.lfStrikeOut = true;
	} else {
        lf.lfStrikeOut = false;
	}

	lf.lfStrikeOut = FALSE;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	
	switch(ffFamily) {
	  case MODERN: 
	    lf.lfPitchAndFamily = FF_MODERN; 
		break;

	  case ROMAN:  
		lf.lfPitchAndFamily = FF_ROMAN; 
		break;

      case SCRIPT: 
		lf.lfPitchAndFamily = FF_SCRIPT; 
		break;

	  case SWISS:  
		lf.lfPitchAndFamily = FF_SWISS; 
		break;

	  default:	 
	    lf.lfPitchAndFamily = FF_DONTCARE; 
		break;
	}

	lf.lfPitchAndFamily |= DEFAULT_PITCH;
	if(cFontName)
		strcpy(lf.lfFaceName, cFontName);
	
	fontObject = CreateFontIndirect(&lf);

}

void window::SetFontStyle() {

	fontOldObject = (HFONT) SelectObject(dcActive, fontObject);

}

void window::RestoreFontStyle() {

	SelectObject(dcActive, fontOldObject);

}

void window::DrawPixel(const int iX, const int iY) {

    HPEN penTemp;
    
    // Cheap trick to change pen width
    penTemp = penObject;
    penObject = NULL;
   	penObject = CreatePen(PS_INSIDEFRAME, 1, RGB(colPen.ucRed, colPen.ucGreen, colPen.ucBlue));

    DrawLine(iX, iY, iX + 1, iY + 1);
    
	if (penObject != NULL) { 
	    if(DeleteObject(penObject) != TRUE) {
	        cout << "Fatal Error: Failed to delete penObject in SetPen!" << endl;	    
	    }
		penObject = NULL; 
	}    
    
    penObject = penTemp;

}

void window::DrawLine(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle) {

    ProcessMessage(); // Kludge

	switch(dsStyle) {
	  case FRAME:
        ChangeDrawStyle(FRAME);
	    if(MoveToEx(dcActive, iX1, iY1, NULL) != TRUE) {
	        cout << "Fatal Error: Failed to MoveToEx in DrawLine!" << endl;	        	    		    
	    }
	    if(LineTo(dcActive, iX2, iY2) != TRUE) {
            cout << "Fatal Error: Failed to draw in DrawLine!" << endl;	        	    		    
	    }
	    RestoreDrawStyle();
		break;
		
	  default:
		cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
		break;
	}
}

void window::DrawRectangle(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle, const int iWidth, const int iHeight) {

    HRGN rgnTemp;

	ProcessMessage(); // Kludge
	if((iWidth == 0) && (iHeight == 0)) {

	    switch(dsStyle) {

   		  case FILLED:
		    ChangeDrawStyle(FILLED);
	        if(Rectangle(dcActive, iX1, iY1, iX2, iY2) != TRUE) {
                cout << "Fatal Error: Failed to draw filled style in DrawRectangle!" << endl;	        	    		    
	        }
	        RestoreDrawStyle();
	        break;

		  case FRAME:
            ChangeDrawStyle(FRAME);
 	        if(Rectangle(dcActive, iX1, iY1, iX2, iY2) != TRUE) {
                cout << "Fatal Error: Failed to draw frame style in DrawRectangle!" << endl;	        	    		    
 	        }
 	        RestoreDrawStyle();
			break;
		
		  case INVERTED:
  	        ChangeDrawStyle(INVERTED);
			if(Rectangle(dcActive, iX1, iY1, iX2, iY2) != TRUE) {
                cout << "Fatal Error: Failed to draw inverted style in DrawRectangle!" << endl;	        	    		    
			}
			RestoreDrawStyle();
			break;

		  default:
			cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
			break;
		}

	} else {

	    switch(dsStyle) {

  	      case FILLED:
			ChangeDrawStyle(FILLED);	    
	        if(RoundRect(dcActive, iX1, iY1, iX2, iY2, iWidth, iHeight) != TRUE) {
                cout << "Fatal Error: Failed to draw filled style in DrawRectangle (rounded)!" << endl;	        	    		    
	        }
	        RestoreDrawStyle();
			break;

		  case FRAME:
			ChangeDrawStyle(FRAME);
			if(RoundRect(dcActive, iX1, iY1, iX2, iY2, iWidth, iHeight) != TRUE) {
                cout << "Fatal Error: Failed to draw frame style in DrawRectangle (rounded)!" << endl;	        	    		    
			}
			RestoreDrawStyle();
			break;
		
		  case INVERTED:
			rgnTemp = CreateRoundRectRgn(iX1, iY1, iX2, iY2, iWidth, iHeight);
			if(InvertRgn(dcActive,rgnTemp) != TRUE) {
                cout << "Fatal Error: Failed to draw inverted style in DrawRectangle (rounded)!" << endl;	        	    		    			
			}
			DeleteObject(rgnTemp);
			break;

		  default:
			cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
			break;
		}
	}
}

void window::DrawTriangle(const int iX1, const int iY1, const int iX2, const int iY2, const int iX3, const int iY3, const drawstyle dsStyle) {

	HRGN rgnTemp;
    POINT ptVertices[3] = {{iX1, iY1}, {iX2, iY2}, {iX3, iY3}};

	ProcessMessage(); // Kludge
    switch(dsStyle) {
      case FILLED:
		ChangeDrawStyle(FILLED);	    
 	    if(Polygon(dcActive, ptVertices, 3) != TRUE) {
            cout << "Fatal Error: Failed to draw filled style in DrawTriangle!" << endl;	        	    		    
 	    }
 	    RestoreDrawStyle();
		break;

	  case FRAME:
		ChangeDrawStyle(FRAME);
 	    if(Polygon(dcActive, ptVertices, 3) != TRUE) {
            cout << "Fatal Error: Failed to draw frame style in DrawTriangle!" << endl;	        	    		    
 	    }
 	    RestoreDrawStyle();
		break;
		
	  case INVERTED:
		rgnTemp = CreatePolygonRgn(ptVertices, 3, WINDING);
 	    if(InvertRgn(dcActive, rgnTemp) != TRUE) {
            cout << "Fatal Error: Failed to draw inverted style in DrawTriangle!" << endl;	        	    		     	    
 	    }
		DeleteObject(rgnTemp);
		break;

	  default:
	    cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
		break;
	}
	
}

void window::DrawPolygon(const int* ipX, const int* ipY, const int iVertices, const drawstyle dsStyle) {

	HRGN rgnTemp;
	POINT *ptVertices;
	unsigned short i;

	ptVertices = new POINT[iVertices];
    if(ptVertices == NULL) {
		throw OUT_OF_MEMORY;
	}

	for(i = 0; i < iVertices; i++) {
		ptVertices[i].x = ipX[i];
		ptVertices[i].y = ipY[i];
	}

	ProcessMessage(); // Kludge
    switch(dsStyle) {
      case FILLED:
		ChangeDrawStyle(FILLED);	    
 	    if(Polygon(dcActive, ptVertices, iVertices) != TRUE) {
            cout << "Fatal Error: Failed to draw filled style in DrawPolygon!" << endl;	        	    		    
 	    }
 	    RestoreDrawStyle();
		break;

	  case FRAME:
		ChangeDrawStyle(FRAME);
 	    if(Polygon(dcActive, ptVertices, iVertices) != TRUE) {
            cout << "Fatal Error: Failed to draw frame style in DrawPolygon!" << endl;	        	    		     	    
 	    }
 	    RestoreDrawStyle();
		break;
		
	  case INVERTED:
		rgnTemp = CreatePolygonRgn(ptVertices, iVertices, WINDING);
	    if(InvertRgn(dcActive, rgnTemp) != TRUE) {
            cout << "Fatal Error: Failed to draw inverted style in DrawPolygon!" << endl;	        	    		    
	    }
		DeleteObject(rgnTemp);
		break;

	  default:
		delete ptVertices;
	    cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
		break;
	}

	delete ptVertices;
}

void window::DrawCircle(const int iX, const int iY, const int iRadius, const drawstyle dsStyle) {

    HRGN rgnTemp;

	ProcessMessage(); // Kludge
    switch(dsStyle) {
      case FILLED:
		ChangeDrawStyle(FILLED);	    
 	    if(Ellipse(dcActive, (iX - iRadius), (iY - iRadius), (iX + iRadius), (iY + iRadius)) != TRUE) {
            cout << "Fatal Error: Failed to draw filled style in DrawCircle!" << endl;	        	    		     	    
 	    }
 	    RestoreDrawStyle();
		break;

	  case FRAME:
		ChangeDrawStyle(FRAME);
 	    if(Ellipse(dcActive, (iX - iRadius), (iY - iRadius), (iX + iRadius), (iY + iRadius)) != TRUE) {
 	        cout << "Fatal Error: Failed to draw frame style in DrawCircle!" << endl;	        	    		    
	    }
 	    RestoreDrawStyle();
		break;
		
	  case INVERTED:
		rgnTemp = CreateEllipticRgn((iX - iRadius), (iY - iRadius), (iX + iRadius), (iY + iRadius));
 	    if(InvertRgn(dcActive, rgnTemp) != TRUE) {
            cout << "Fatal Error: Failed to draw inverted style in DrawCircle!" << endl;	        	    		     	    
 	    }
		DeleteObject(rgnTemp);
		break;

	  default:
		cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
		break;
	}
}

void window::DrawEllipse(const int iX1, const int iY1, const int iX2, const int iY2, const drawstyle dsStyle) {

	HRGN rgnTemp;

	ProcessMessage(); // Kludge
	switch(dsStyle) {
      case FILLED:
		ChangeDrawStyle(FILLED);
		if(Ellipse(dcActive, iX1, iY1, iX2, iY2) != TRUE) {
            cout << "Fatal Error: Failed to draw filled style in DrawEllipse!" << endl;	        	    		    
		}
		RestoreDrawStyle();
		break;

	  case FRAME:
		ChangeDrawStyle(FRAME);
 	    if(Ellipse(dcActive, iX1, iY1, iX2, iY2) != TRUE) {
            cout << "Fatal Error: Failed to draw frame style in DrawEllipse!" << endl;	        	    		     	    
 	    }
 	    RestoreDrawStyle();
		break;
		
	  case INVERTED:
	    rgnTemp = CreateEllipticRgn(iX1, iY1, iX2, iY2);
 	    if(InvertRgn(dcActive, rgnTemp) != TRUE) {
            cout << "Fatal Error: Failed to draw inverted style in DrawEllipse!" << endl;	        	    		     	    
 	    }
		DeleteObject(rgnTemp);
		break;

	  default:
		cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
		break;
	}

}

void window::DrawArc(const int iX1, const int iY1, const int iX2, const int iY2, double dStartAngle, double dEndAngle, const drawstyle dsStyle, const angletype atInfo){

	int iWidth, iHeight; // x-axis, y-axis dimensions
	int iCenterX,iCenterY; // center pixel
	int iStartX, iStartY; // start pixel
	int iEndX, iEndY; // end pixel

	ProcessMessage(); // Kludge
	
	iWidth = (iX2 - iX1) / 2;
	iHeight = (iY2 - iY1) / 2;

	iCenterX = (iX2 + iX1) / 2;
	iCenterY = (iY2 + iY1) / 2;
	
	if(atInfo != RADIANS) {
	    dStartAngle = dStartAngle * (cdPi / 180);
	    dEndAngle = dEndAngle * (cdPi / 180);
	}

	iStartX = iCenterX + int(iWidth * cos(dStartAngle));
	iStartY = iCenterY - int(iHeight * sin(dStartAngle));
	iEndX = iCenterX + int(iWidth * cos(dEndAngle));
	iEndY = iCenterY - int(iHeight * sin(dEndAngle));

	switch(dsStyle) {
	  case FILLED:
        ChangeDrawStyle(FILLED);
	    if(Pie(dcActive, iX1, iY1, iX2, iY2, iStartX, iStartY, iEndX, iEndY) != TRUE) {
            cout << "Fatal Error: Failed to draw filled style in DrawArc!" << endl;	        	    		    
	    }
	    RestoreDrawStyle();
		break;

	  case FRAME:
        ChangeDrawStyle(FRAME);
	    if(Arc(dcActive, iX1, iY1, iX2, iY2, iStartX, iStartY, iEndX, iEndY) != TRUE) {
            cout << "Fatal Error: Failed to draw frame style in DrawArc!" << endl;	        	    		    
	    }
	    RestoreDrawStyle();
		break;

	  case INVERTED:
        ChangeDrawStyle(INVERTED);
	    if(Pie(dcActive, iX1, iY1, iX2, iY2, iStartX, iStartY, iEndX, iEndY) != TRUE) {
            cout << "Fatal Error: Failed to draw inverted style in DrawArc!" << endl;	        	    		    
	    }
	    RestoreDrawStyle();
		break;

	  default:
	    cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
		break;
	}
}

void window::DrawBezier(const int iX1, const int iY1, const int iX2, const int iY2, const int iX3, const int iY3, const int iX4, const int iY4, const drawstyle dsStyle) {

    POINT ptControlPts[4] = {{iX1, iY1}, {iX2, iY2}, {iX3, iY3}, {iX4, iY4}};

	ProcessMessage(); // Kludge

	switch(dsStyle) {
	  case FRAME:
        ChangeDrawStyle(FRAME);
	    if(PolyBezier(dcActive, ptControlPts, 4) != TRUE) {
            cout << "Fatal Error: Failed to draw in DrawBezier!" << endl;	        	    		  
	    }
	    RestoreDrawStyle();
		break;

	  default:
	    cout << "Fatal Error: You have tried to use an invalid or unimplemented drawstyle!" << endl;
		break;
	}

}

void window::DrawString(const int iX, const int iY, const char *cpText) {

    if (cpText == NULL) {
	    // Throw an exception here?
		return;
	}

    ProcessMessage(); // Kludge1

	SetFontStyle();
	    
	if(SetBkMode(dcActive, TRANSPARENT) == 0) {
        cout << "Fatal Error: Failed to SetBkMode in DrawString!" << endl;	        	    	
	}
	if(SetTextAlign(dcActive, TA_UPDATECP) == GDI_ERROR) {
        cout << "Fatal Error: Failed to SetTextAlign in DrawString!" << endl;   
	}
	
	if(MoveToEx(dcActive, iX, iY, NULL) != TRUE) {
        cout << "Fatal Error: Failed to MoveToEx in DrawString!" << endl;	        	    	
    }

	if(TextOut(dcActive, iX, iY, cpText, (int) strlen(cpText)) == 0) {
        cout << "Fatal Error: Failed to TextOut in DrawString!" << endl;	        	    	
	}
	RestoreFontStyle();

}

void window::DrawString(const int iX, const int iY, const string strText) {

    DrawString(iX, iY, (char *)strText.c_str());

}

void window::DrawInteger(const int iX, const int iY, const long lNumber) {
    
	char cTmpStorage[128];
	sprintf(cTmpStorage, "%d", lNumber);
    DrawString(iX, iY, cTmpStorage);
}

void window::DrawDouble(const int iX, const int iY, const double dNumber) {

	char cTmpStorage[128];
	sprintf(cTmpStorage, "%f", dNumber);
	
    DrawString(iX, iY, cTmpStorage);
}

void window::GetStringSize(int &iWidth, int &iHeight, const char* cpText) {

    SIZE szTemp;

    ProcessMessage(); // Kludge

    SetFontStyle();
    if(GetTextExtentPoint32(dcActive, cpText, (int) strlen(cpText), &szTemp) != TRUE) {
        cout << "Fatal Error: Failed to GetTextExtentPoint32 in GetStringSize!" << endl;	        	    
    }
    RestoreFontStyle();

    iWidth = szTemp.cx;
    iHeight = szTemp.cy;

}

void window::GetStringSize(int &iWidth, int &iHeight, const string strText) {

    GetStringSize(iWidth, iHeight, (char *)strText.c_str());

}

void window::GetIntegerSize(int &iWidth, int &iHeight, const long lNumber) {

	char cTmpStorage[128];
	sprintf(cTmpStorage, "%d", lNumber);
    GetStringSize(iWidth, iHeight, cTmpStorage);

}

void window::GetDoubleSize(int &iWidth, int &iHeight, const double dNumber) {

	char cTmpStorage[128];
	sprintf(cTmpStorage, "%f", dNumber);
	
    GetStringSize(iWidth, iHeight, cTmpStorage);

}


void window::DrawImage(const image *imgThis, const int iX, const int iY, const int iWidth, const int iHeight) {

    ProcessMessage(); // Kludge
    
    if(imgThis->usWidth != 0 && imgThis->usHeight != 0) {
	  if((imgThis->itType == JPEG) || (imgThis->itType == SCREEN)) {

		if((iWidth != -1) && (iHeight != -1)) {
			if(StretchDIBits(dcActive, iX, iY, iWidth, iHeight, 0, 0, imgThis->usWidth, imgThis->usHeight, imgThis->ucpImageData, imgThis->bmiImage, DIB_RGB_COLORS, SRCCOPY) == GDI_ERROR) {
 	            cout << "Fatal Error: Failed to StretchDIBits in DrawImage!" << endl;
			}
		} else {
	        if(SetDIBitsToDevice(dcActive, iX, iY, imgThis->usWidth, imgThis->usHeight, 0, 0, 0, imgThis->usHeight, imgThis->ucpImageData, imgThis->bmiImage, DIB_RGB_COLORS) == 0) {
 	            cout << "Fatal Error: Failed to SetDIBitsToDevice in DrawImage!" << endl;
	        }
		}

	  } else {
	
        cout << "Fatal Error: Unsupported image type!" << endl;
	
	  }
	}
}

void window::DrawImage(const image &imgThis, const int iX, const int iY, const int iWidth, const int iHeight) {

  DrawImage(&imgThis, iX, iY, iWidth, iHeight);

}

color window::GetColor(const int iX, const int iY) {

    HDC dcTempBuffer;
    HBITMAP bmapTempBuffer;
    HBITMAP bmapOld;
    BITMAPINFO *bmiImage;
    char caImageData[4];
    color colTemp;

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
	bmiImage->bmiHeader.biWidth = 1;
	bmiImage->bmiHeader.biHeight = -1;

    dcTempBuffer = CreateCompatibleDC(dcActive);
	bmapTempBuffer = CreateCompatibleBitmap(dcActive, 1, 1);

    bmapOld = (HBITMAP) SelectObject(dcTempBuffer, bmapTempBuffer);

    ProcessMessage(); // Kludge
    
	if(BitBlt(dcTempBuffer, 0, 0, 1, 1, dcActive, iX, iY, SRCCOPY) != TRUE) {
	    cout << "Fatal Error: Failed to BltBit in GetColor!" << endl;
    }

	if(GetDIBits(dcActive, bmapTempBuffer, 0, 1, caImageData, bmiImage, DIB_RGB_COLORS) == 0) {
        cout << "Fatal Error: Failed to GetDIBits in GetColor!" << endl;	    
	}
  
    colTemp.ucRed = (unsigned char) caImageData[2];
    colTemp.ucGreen = (unsigned char) caImageData[1];
    colTemp.ucBlue = (unsigned char) caImageData[0];

    SelectObject(dcTempBuffer, bmapOld);
    if(DeleteObject(bmapTempBuffer) != TRUE) {
	    cout << "Fatal Error: Failed to delete bmapTempBuffer in GetColor!" << endl;
    }
	if(DeleteDC(dcTempBuffer) != TRUE) {
	    cout << "Fatal Error: Failed to delete dcTempBuffer in GetColor!" << endl;
	}
	delete [] bmiImage;
	
	return colTemp;

}


void window::GetColor(const int iX, const int iY, double &dRed, double &dGreen, double &dBlue) {

  color colTemp;
  
  colTemp = GetColor(iX, iY);
  
  dRed = (colTemp.ucRed / 255.0);
  dGreen = (colTemp.ucGreen / 255.0);
  dBlue = (colTemp.ucBlue / 255.0);

}


double window::GetRed(const int iX, const int iY) {

  color colTemp;
  
  colTemp = GetColor(iX, iY);
  
  return (colTemp.ucRed / 255.0);
  
}

double window::GetGreen(const int iX, const int iY) {

  color colTemp;
  
  colTemp = GetColor(iX, iY);
  
  return (colTemp.ucGreen / 255.0);

}

double window::GetBlue(const int iX, const int iY) {

  color colTemp;
  
  colTemp = GetColor(iX, iY);
  
  return (colTemp.ucBlue / 255.0);

}


void window::StoreImage(image *imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight) {

    ProcessMessage(); // Kludge    

    HBITMAP bmapOld;

    if((usX + usWidth > iWindowWidth) || (usY + usHeight > iWindowHeight)) {
        cout << "Fatal Error: StoreImage selection extends outside the window!" << endl;
        return;
    }
    
    imgThis->usWidth = usWidth;
	imgThis->usHeight = usHeight;

    if(imgThis->bmiImage != NULL) {
        delete [] imgThis->bmiImage;
    }
    
    imgThis->bmiImage = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
	if(imgThis->bmiImage == NULL) {
        throw OUT_OF_MEMORY;
	}

    memset(imgThis->bmiImage, 0, sizeof(BITMAPINFOHEADER));
    
    imgThis->itType = SCREEN;
    
    imgThis->bmiImage->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	imgThis->bmiImage->bmiHeader.biPlanes = 1;
	imgThis->bmiImage->bmiHeader.biBitCount = 32;
	imgThis->bmiImage->bmiHeader.biCompression = BI_RGB;
	imgThis->bmiImage->bmiHeader.biSizeImage = 0;
	imgThis->bmiImage->bmiHeader.biClrUsed = 0;
	imgThis->bmiImage->bmiHeader.biClrImportant = 0;
	imgThis->bmiImage->bmiHeader.biWidth = usWidth;
	imgThis->bmiImage->bmiHeader.biHeight = -usHeight;

	if(imgThis->ucpImageData != NULL) {
		delete [] imgThis->ucpImageData;
	}

	imgThis->ucpImageData = new unsigned char[(usWidth * 4) * usHeight];
    if(imgThis->ucpImageData == NULL) {
        throw OUT_OF_MEMORY;
    }

    imgThis->dcTempBuffer = CreateCompatibleDC(dcActive);
	imgThis->bmapTempBuffer = CreateCompatibleBitmap(dcActive, usWidth, usHeight);

    bmapOld = (HBITMAP) SelectObject(imgThis->dcTempBuffer, imgThis->bmapTempBuffer);

	if(BitBlt(imgThis->dcTempBuffer, 0, 0, (int) usWidth, (int) usHeight, dcActive, (int) usX, (int) usY, SRCCOPY) != TRUE) {
        cout << "Fatal Error: Failed to BitBlt in StoreImage!" << endl;	
	}

	if(GetDIBits(dcActive, imgThis->bmapTempBuffer, 0, usHeight, imgThis->ucpImageData, imgThis->bmiImage, DIB_RGB_COLORS) == 0) {
        cout << "Fatal Error: Failed to GetDIBits in StoreImage!" << endl;
	}

    SelectObject(imgThis->dcTempBuffer, bmapOld);
    if(DeleteObject(imgThis->bmapTempBuffer) != TRUE) {
	    cout << "Fatal Error: Failed to delete imgThis->bmapTempBuffer in StoreImage!" << endl;    
    }
	if(DeleteDC(imgThis->dcTempBuffer) != TRUE) {
	    cout << "Fatal Error: Failed to delete imgThis->dcTempBuffer in StoreImage!" << endl;
	}

}

void window::StoreImage(image &imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight) {

	StoreImage(&imgThis, usX, usY, usWidth, usHeight);

}

void window::Print() {

    PRINTDLG  pdlgInfo;
    DOCINFO diStuff = { sizeof(DOCINFO), NULL, NULL };
    HDC dcPrinter;
    
    int iPrinterWidth, iPrinterHeight;
    int iXPos, iYPos;

    ProcessMessage(); // Kludge
    
    if(bDoubleBuffer != true) {
        MessageBox(hwndWindow, "Double-buffering must be enabled for printing to work.  Sorry.", "Graphics Library", MB_ICONEXCLAMATION | MB_OK);
    }
    
    memset(&pdlgInfo, 0, sizeof(PRINTDLG));
    
    pdlgInfo.lStructSize = sizeof(PRINTDLG);
    pdlgInfo.hwndOwner = hwndWindow;
    pdlgInfo.hDevMode = NULL;
    pdlgInfo.hDevNames = NULL;
    
    pdlgInfo.Flags = PD_NOPAGENUMS | PD_NOSELECTION | PD_RETURNDC | PD_USEDEVMODECOPIESANDCOLLATE;

    if(PrintDlg(&pdlgInfo) == false) {
        return;
    }

    dcPrinter = pdlgInfo.hDC;
    
    if((GetDeviceCaps(dcPrinter, RASTERCAPS) & RC_BITBLT) != RC_BITBLT) {
        MessageBox(hwndWindow, "Your printer does not support bitblts.  Sorry", "Graphics Library", MB_ICONEXCLAMATION | MB_OK);
        return;
    }
    
    if((GetDeviceCaps(dcPrinter, RASTERCAPS) & RC_BITMAP64) != RC_BITMAP64) {
        MessageBox(hwndWindow, "Your printer does not support bitmaps larger than 64K.  Sorry.", "Graphics Library", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    if(StartDoc(dcPrinter, &diStuff) <= 0) {
        cout << "Fatal Error: Failed to StartDoc in Print!" << endl;
    }    
    
    if(StartPage(dcPrinter) <= 0) {
        cout << "Fatal Error: Failed to StartPage in Print!" << endl;
    }  
      
    if((GetDeviceCaps(dcPrinter, RASTERCAPS) & RC_STRETCHBLT) != RC_STRETCHBLT) {
    
        // Center the image horizontally
        iXPos = (GetDeviceCaps(dcPrinter, HORZRES) - iWindowWidth) >> 1;
        // Center the image vertically
        iYPos = (GetDeviceCaps(dcPrinter, VERTRES) - iWindowHeight) >> 1;


        if(BitBlt(dcPrinter, iXPos, iYPos, iWindowWidth, iWindowHeight, dcActive, 0, 0, SRCCOPY) != TRUE) {
            cout << "Fatal Error: Failed to BitBlt in Print!" << endl;   
        }

    } else {
        iPrinterWidth = GetDeviceCaps(dcPrinter, HORZRES);
        iPrinterHeight = int(double(iPrinterWidth) * double(iWindowHeight) / double(iWindowWidth));

        // Center the image vertically
        iYPos = (GetDeviceCaps(dcPrinter, VERTRES) - iPrinterHeight) >> 1;

        if(StretchBlt(dcPrinter, 0, iYPos, iPrinterWidth, iPrinterHeight, dcActive, 0, 0, iWindowWidth, iWindowHeight, SRCCOPY) != TRUE) {
            cout << "Fatal Error: Failed to StretchBlt in Print!" << endl;
        }
        
    }
    
    if(EndPage(dcPrinter) <= 0) {
        cout << "Fatal Error: Failed to EndPage in Print!" << endl;
    }    
    
    if(EndDoc(dcPrinter) <= 0) {
        cout << "Fatal Error: Failed to EndDoc in Print!" << endl;
    }    
    
  	if(DeleteDC(dcPrinter) != TRUE) {
  	    cout << "Fatal Error: Failed to delete dcPrinter in Print!" << endl;
  	}
}
