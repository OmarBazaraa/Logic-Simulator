/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#ifndef JPEGLOAD_H
#define JPEGLOAD_H

#include "version.h"

/* Load a JPEG image */
int jpegload(const char *cpFileName, unsigned short *uspWidth, unsigned short *uspHeight, unsigned char **ucpImageData);

#endif /*JPEGLOAD_H */
