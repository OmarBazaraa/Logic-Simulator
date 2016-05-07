/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#ifndef COLORS_H
#define COLORS_H

#include "version.h"

class color {

  public:

    // Default constructor creates black
    color(unsigned char Red = 0, unsigned char Green = 0, unsigned char Blue = 0) { 
        ucRed = Red;  ucGreen = Green;  ucBlue = Blue; 
    }


    // Color components.  0 = no intensity, 255 = full intensity
    unsigned char ucRed;
    unsigned char ucGreen;
    unsigned char ucBlue;

};

bool operator==(color a, color b);
bool operator!=(color a, color b);

/*

  Predefine some color objects...  Data was liberally borrowed from the
  Open Group's X11 rbg.txt file

  $XConsortium: rgb.txt,v 10.41 94/02/20 18:39:36 rws Exp 

*/

const color SNOW = color(255, 250, 250);
const color GHOSTWHITE = color(248, 248, 255);
const color WHITESMOKE = color(245, 245, 245);
const color GAINSBORO = color(220, 220, 220);
const color FLORALWHITE = color(255, 250, 240);
const color OLDLACE = color(253, 245, 230);
const color LINEN = color(250, 240, 230);
const color ANTIQUEWHITE = color(250, 235, 215);
const color PAPAYAWHIP = color(255, 239, 213);
const color BLANCHEDALMOND = color(255, 235, 205);
const color BISQUE = color(255, 228, 196);
const color PEACHPUFF = color(255, 218, 185);
const color NAVAJOWHITE = color(255, 222, 173);
const color MOCCASIN = color(255, 228, 181);
const color CORNSILK = color(255, 248, 220);
const color IVORY = color(255, 255, 240);
const color LEMONCHIFFON = color(255, 250, 205);
const color SEASHELL = color(255, 245, 238);
const color HONEYDEW = color(240, 255, 240);
const color MINTCREAM = color(245, 255, 250);
const color AZURE = color(240, 255, 255);
const color ALICEBLUE = color(240, 248, 255);
const color LAVENDER = color(230, 230, 250);
const color LAVENDERBLUSH = color(255, 240, 245);
const color MISTYROSE = color(255, 228, 225);
const color WHITE = color(255, 255, 255);
const color BLACK = color(0, 0, 0);
const color DARKSLATEGRAY = color(47, 79, 79);
const color DARKSLATEGREY = color(47, 79, 79);
const color DIMGRAY = color(105, 105, 105);
const color DIMGREY = color(105, 105, 105);
const color SLATEGRAY = color(112, 128, 144);
const color SLATEGREY = color(112, 128, 144);
const color LIGHTSLATEGRAY = color(119, 136, 153);
const color LIGHTSLATEGREY = color(119, 136, 153);
const color GRAY = color(190, 190, 190);
const color GREY = color(190, 190, 190);
const color LIGHTGREY = color(211, 211, 211);
const color LIGHTGRAY = color(211, 211, 211);
const color MIDNIGHTBLUE = color(25, 25, 112);
const color NAVY = color(0, 0, 128);
const color NAVYBLUE = color(0, 0, 128);
const color CORNFLOWERBLUE = color(100, 149, 237);
const color DARKSLATEBLUE = color(72, 61, 139);
const color SLATEBLUE = color(106, 90, 205);
const color MEDIUMSLATEBLUE = color(123, 104, 238);
const color LIGHTSLATEBLUE = color(132, 112, 255);
const color MEDIUMBLUE = color(0, 0, 205);
const color ROYALBLUE = color(65, 105, 225);
const color BLUE = color(0, 0, 255);
const color DODGERBLUE = color(30, 144, 255);
const color DEEPSKYBLUE = color(0, 191, 255);
const color SKYBLUE = color(135, 206, 235);
const color LIGHTSKYBLUE = color(135, 206, 250);
const color STEELBLUE = color(70, 130, 180);
const color LIGHTSTEELBLUE = color(176, 196, 222);
const color LIGHTBLUE = color(173, 216, 230);
const color POWDERBLUE = color(176, 224, 230);
const color PALETURQUOISE = color(175, 238, 238);
const color DARKTURQUOISE = color(0, 206, 209);
const color MEDIUMTURQUOISE = color(72, 209, 204);
const color TURQUOISE = color(64, 224, 208);
const color CYAN = color(0, 255, 255);
const color LIGHTCYAN = color(224, 255, 255);
const color CADETBLUE = color(95, 158, 160);
const color MEDIUMAQUAMARINE = color(102, 205, 170);
const color AQUAMARINE = color(127, 255, 212);
const color DARKGREEN = color(0, 100, 0);
const color DARKOLIVEGREEN = color(85, 107, 47);
const color DARKSEAGREEN = color(143, 188, 143);
const color SEAGREEN = color(46, 139, 87);
const color MEDIUMSEAGREEN = color(60, 179, 113);
const color LIGHTSEAGREEN = color(32, 178, 170);
const color PALEGREEN = color(152, 251, 152);
const color SPRINGGREEN = color(0, 255, 127);
const color LAWNGREEN = color(124, 252, 0);
const color GREEN = color(0, 255, 0);
const color CHARTREUSE = color(127, 255, 0);
const color MEDIUMSPRINGGREEN = color(0, 250, 154);
const color GREENYELLOW = color(173, 255, 47);
const color LIMEGREEN = color(50, 205, 50);
const color YELLOWGREEN = color(154, 205, 50);
const color FORESTGREEN = color(34, 139, 34);
const color OLIVEDRAB = color(107, 142, 35);
const color DARKKHAKI = color(189, 183, 107);
const color KHAKI = color(240, 230, 140);
const color PALEGOLDENROD = color(238, 232, 170);
const color LIGHTGOLDENRODYELLOW = color(250, 250, 210);
const color LIGHTYELLOW = color(255, 255, 224);
const color YELLOW = color(255, 255, 0);
const color GOLD = color(255, 215, 0);
const color LIGHTGOLDENROD = color(238, 221, 130);
const color GOLDENROD = color(218, 165, 32);
const color DARKGOLDENROD = color(184, 134, 11);
const color ROSYBROWN = color(188, 143, 143);
const color INDIAN = color(205, 92, 92);
const color INDIANRED = color(205, 92, 92);
const color SADDLEBROWN = color(139, 69, 19);
const color SIENNA = color(160, 82, 45);
const color PERU = color(205, 133, 63);
const color BURLYWOOD = color(222, 184, 135);
const color BEIGE = color(245, 245, 220);
const color WHEAT = color(245, 222, 179);
const color SANDYBROWN = color(244, 164, 96);
const color TAN = color(210, 180, 140);
const color CHOCOLATE = color(210, 105, 30);
const color FIREBRICK = color(178, 34, 34);
const color BROWN = color(165, 42, 42);
const color DARKSALMON = color(233, 150, 122);
const color SALMON = color(250, 128, 114);
const color LIGHTSALMON = color(255, 160, 122);
const color ORANGE = color(255, 165, 0);
const color DARKORANGE = color(255, 140, 0);
const color CORAL = color(255, 127, 80);
const color LIGHTCORAL = color(240, 128, 128);
const color TOMATO = color(255, 99, 71);
const color ORANGERED = color(255, 69, 0);
const color RED = color(255, 0, 0);
const color HOTPINK = color(255, 105, 180);
const color DEEPPINK = color(255, 20, 147);
const color PINK = color(255, 192, 203);
const color LIGHTPINK = color(255, 182, 193);
const color PALEVIOLETRED = color(219, 112, 147);
const color MAROON = color(176, 48, 96);
const color MEDIUMVIOLETRED = color(199, 21, 133);
const color VIOLETRED = color(208, 32, 144);
const color MAGENTA = color(255, 0, 255);
const color VIOLET = color(238, 130, 238);
const color PLUM = color(221, 160, 221);
const color ORCHID = color(218, 112, 214);
const color MEDIUMORCHID = color(186, 85, 211);
const color DARKORCHID = color(153, 50, 204);
const color DARKVIOLET = color(148, 0, 211);
const color BLUEVIOLET = color(138, 43, 226);
const color PURPLE = color(160, 32, 240);
const color MEDIUMPURPLE = color(147, 112, 219);
const color THISTLE = color(216, 191, 216);
const color DARKGREY = color(169, 169, 169);
const color DARKGRAY = color(169, 169, 169);
const color DARKBLUE = color(0, 0, 139);
const color DARKCYAN = color(0, 139, 139);
const color DARKMAGENTA = color(139, 0, 139);
const color DARKRED = color(139, 0, 0);
const color LIGHTGREEN = color(144, 238, 144);


#endif //COLOR_H
