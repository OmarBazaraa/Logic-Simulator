/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include <stdlib.h>
#include <stdio.h>
#include "jpeg\jinclude.h"
#include "jpeg\jpeglib.h"
#include "jpegload.h"

int jpegload(const char *cpFileName, unsigned short *uspWidth, unsigned short *uspHeight, unsigned char **ucpImageData) {

  struct jpeg_decompress_struct jdsInfo;
  struct jpeg_error_mgr jemError;

  JSAMPARRAY jsaTmpBuffer;
  unsigned long ulOffset, ulDataWidth;
  unsigned short i;

  FILE *fInput;

  fInput = fopen(cpFileName, "rb");
  if(fInput == NULL) {
 	  return(-1);
  }

  jdsInfo.err = jpeg_std_error(&jemError);
  jpeg_create_decompress(&jdsInfo);
  jpeg_stdio_src(&jdsInfo, fInput);
  jpeg_read_header(&jdsInfo, TRUE);
  jpeg_start_decompress(&jdsInfo);


  *uspWidth = (unsigned short) jdsInfo.output_width;
  *uspHeight = (unsigned short) jdsInfo.output_height;
  ulDataWidth = jdsInfo.output_width * jdsInfo.output_components;

  *ucpImageData = (unsigned char *) malloc(ulDataWidth * (*uspHeight));
  if(ucpImageData == NULL) {
      return(-2);
  }
  
  memset(*ucpImageData, 0, ulDataWidth * (*uspHeight));
  jsaTmpBuffer = (*jdsInfo.mem->alloc_sarray) ((j_common_ptr) &jdsInfo, JPOOL_IMAGE, ulDataWidth, 1);

  for(i = 0, ulOffset = 0; i < (*uspHeight); i++) {
    jpeg_read_scanlines(&jdsInfo, jsaTmpBuffer, 1); 
	memcpy((*ucpImageData + ulOffset), jsaTmpBuffer[0], ulDataWidth);
	ulOffset += ulDataWidth;
  }
  
  jpeg_finish_decompress(&jdsInfo);

  fclose(fInput);

  return(0);
}
