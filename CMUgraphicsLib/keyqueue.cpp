/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include "keyqueue.h"

kqueue::kqueue() {

    kqueHead = NULL;
    kqueTail = NULL;

}

kqueue::~kqueue() {

   kqueuenode *kqueTmp;

   kqueTail = NULL;

   while(kqueHead != NULL) {
       kqueTmp = kqueHead;
	   kqueHead = kqueHead->kqueNext;
	   delete kqueTmp;
   }
}
	
void kqueue::Insert(kqueuenode* kqueNode) {

    if(kqueNode == NULL) {
        return;
	} else if(kqueHead == NULL) {
        kqueHead = kqueNode;
		kqueTail = kqueHead;
	} else {
        kqueTail->kqueNext = kqueNode;
	    kqueTail = kqueTail->kqueNext;
	}
}

kqueuenode* kqueue::Remove() {

    kqueuenode* kqueTmp;

	if(kqueHead != NULL) {
        kqueTmp = kqueHead;
	    kqueHead = kqueHead->kqueNext;
	    kqueTmp->kqueNext = NULL;
    } else {
        kqueTmp = NULL;
	}

	return kqueTmp;

}