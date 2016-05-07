/* 
CMUgraphics Library 1.2 
Copyright (c) 1998 and 1999 by Geoff Washburn.  All rights reserved.

Portions of the code in these files may be derived from code written 
by Patrick Doane, Mark Stehlik, and Jim Roberts.

Please send all bug reports via e-mail to Geoff Washburn 
(washburn+@cmu.edu) and Mark Stehlik (mjs@cs.cmu.edu).

Redistribution and the use of this library in source and binary forms, 
with or without modification, is permitted provided that the 
following conditions are met:
 
  1. Redistribution of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistribution in binary form must reproduce the above 
     copyright notice, this list of conditions and the following 
     disclaimer in the documentation and/or other materials 
     provided with the distribution.
  3. When redistributing a modified version of this library it must 
     carry prominent notices stating the name of individual(s) that 
     altered the files, the nature of the modifications, and the 
     date they were performed.
  4. No fee is charged for redistribution or use without prior 
     written permission from the author.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS 
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY 
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;  OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

This code is not yet certified for mission critical applications,
such as navigation and/or control of aircraft.

This file was last modified on 05.16.1999

*/

#ifndef VERSION_H
#define VERSION_H

// Define what platform this is being compiled under
//#define __MW_CODEWARRIOR3__
//#define __MW_CODEWARRIOR4__
#define __MS_VISUALCPP__
//#define __BORLANDCPP__

#ifdef __MW_CODEWARRIOR4__
  #pragma ANSI_strict on 
  #pragma warn_emptydecl on
  #pragma warn_extracomma on
  #pragma warn_hidevirtual on
  #pragma warn_illpragma on 
  #pragma warn_implicitconv on
  #pragma warn_possunwant on
  #pragma warn_structclass on 
  #pragma warn_unusedarg on
  #pragma warn_unusedvar on
  #pragma require_prototypes on
  #pragma extended_errorcheck on
#endif

#endif /*VERSION_H */