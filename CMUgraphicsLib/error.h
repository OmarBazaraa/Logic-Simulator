/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#ifndef ERROR_H
#define ERROR_H

#include "version.h"

// Types of errors when exceptions are raised
enum error {
	OUT_OF_MEMORY,  // Procedure was unable to allocated enough memory
	FILE_NOT_FOUND  // Procedure could not open the requested file
};

#endif
