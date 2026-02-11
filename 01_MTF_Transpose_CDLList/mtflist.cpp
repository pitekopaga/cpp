// mtflist.cpp : This file contains the implementation file for a Move-To-Front list
// Scott Elliott
// MTF List Implementation

#include "mtflist.h"

// Constructor: creates an empy move-to-front list by calling base CDLinkedList constructor
MtfList::MtfList() : CDLinkedList() {}

// Ovrride contains to implement move-to-front behavior
// Algorithm:
// 1. Search for anEntry in the list sequentially from front to back
// 2. Increment traverseCount for each node examined
// 3. If found:
  //    a. chck if it's already at the front (if so, do nothing)
  //    b. if not, unlink the node from its current position
  //    c. reinsert the node immediately after the header (at front
// 4. Return true if found, false if not found
bool MtfList::contains(int anEntry) {
  DListNode* cur = header->next; // start at first real node
  while (cur != header) {  // loop continues until we return to header
    ++traverseCount;       // count each node we examine
    if (cur->item == anEntry) {
      // fount it, now implement move-to-front
      // check if already at front (i.e., right after header). if it is, do nothing and just return true
      if (cur == header->next) {
        return true;
      }
      // element is not at front, so we need to move it
      // step 1: unlink cur from its current position
      // this requires updating the prev and next pointers of the neighboring nodes
      cur->prev->next = cur->next;  // previous node 's next skips over cur, pointing to next
      cur->next->prev = cur->prev;  // next node now points back to previous
      // cur is now unlinked from the list but still allocated in memory
      // step 2: insert cur immediately after header (at front of list)
      // we need to update four pointers to maintain the circular doubly linked structure
      cur->next = header->next;     // current node 's next points to old first node
      cur->prev = header;           // current node 's prev points to header
      header->next->prev = cur;     // old first node 's prev points back to cur
      header->next = cur;           // header's next points to cur

      // now cur is at the front of the list
      return true;  // element found and moved to front
    }
    cur = cur->next;
  }
  // if we reach here, anEntry was not found in the list
  return false;  // element not found
}

// Time Complexity:
//   Worst case: O(n) - element could be at the back initially
//   Best case: O(1) - element already at front