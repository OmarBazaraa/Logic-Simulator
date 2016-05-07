
Documentation for the CMUgraphics package is found in Manual.txt.

Release notes for Version 1.2 of the package
--------------------------------------------
Due to some name conflicts, graphics.h has been renamed to CMUgraphics.h
(and graphics.cpp, CMUgraphics.cpp)

Some constants have been renamed (from version 1.1):

	L_CLICK -> LEFT_CLICK
	R_CLICK -> RIGHT_CLICK
	LEFT    -> LEFT_BUTTON
	RIGHT   -> RIGHT_BUTTON

Also, the default destructor behavior of the window object has 
changed.  If a window is the last window object on screen, it 
will now not disappear until the mouse has been clicked in the 
window.  This behavior can be changed using the SetWaitClose 
function described in "Manual.txt".

With this release, the source for each compiler is the same; 
compiler differences are resolved in the file version.h.
An example of the use of this file is if you're using
Metrowerks version 3, you need to uncomment the following #define 
	#define __MW_CODEWARRIOR3__
and comment out this one
	#define __MW_CODEWARRIOR4__


Some other notes on using the package follow:
---------------------------------------

Demo.cpp is included in the source code for the project and exercises
virtually all of the member functions in the CMUgraphics package.  Also
included in the graphics folder is House.cpp which is more emblematic of a
first assignment's solution.  In Metrowerks CodeWarrior, to compile
House.cpp instead of Demo.cpp, drag it into the project window and remove
Demo.cpp from the project.  In Microsoft Visual C++, remove Demo.cpp from
the project and then go to the Project menu and select the "Add to Project"
submenu and finally select files.  Then use the standard file dialog to
locate and add House.cpp.  In Borland, drag House.cpp into the project
window and remove Demo.cpp from the project.

------------------------------------------------------------------------------

The demo makes use of an ostringstream which is fairly new to the C++
Standard and supersedes the older ostrstream.  If your compiler does not
support ostringstreams, e.g., it complains about the #include <sstream>
statement or the declaration of the ostringstream, you should do the following:

replace
        #include <sstream>
with
        #include <strstream.h>

and replace every declaration of output (there are five)
        ostringstream output;
with
        ostrstream output;

------------------------------------------------------------------------------

Notes for Borland users:  the library and include paths are currently set to
c:\bc5\lib and c:\bc5\include.  If your standard libraries are located in a 
different directory, you will have to right-click the top-level project node,
select Edit Local Options and change the paths appropriately.

Once you compile the project, you'll notice many warnings are generated.  All
can be safely ignored; if you figure out how to suppress them, send mail to
mjs@cs.cmu.edu.
