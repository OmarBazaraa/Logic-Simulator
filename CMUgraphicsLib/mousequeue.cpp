/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include "mousequeue.h"

mqueue::mqueue() {

    mqueHead = NULL;
    mqueTail = NULL;

}

mqueue::~mqueue() {

   mqueuenode *mqueTmp;

   mqueTail = NULL;

   while(mqueHead != NULL) {
       mqueTmp = mqueHead;
	   mqueHead = mqueHead->mqueNext;
	   delete mqueTmp;
   }
}
	
void mqueue::Insert(mqueuenode* mqueNode) {

    if(mqueNode == NULL) {
        return;
	} else if(mqueHead == NULL) {
        mqueHead = mqueNode;
		mqueTail = mqueHead;
	} else {
        mqueTail->mqueNext = mqueNode;
	    mqueTail = mqueTail->mqueNext;
	}
}

mqueuenode* mqueue::Remove() {

    mqueuenode* mqueTmp;

	if(mqueHead != NULL) {
        mqueTmp = mqueHead;
	    mqueHead = mqueHead->mqueNext;
	    mqueTmp->mqueNext = NULL;
    } else {
        mqueTmp = NULL;
	}

	return mqueTmp;

}