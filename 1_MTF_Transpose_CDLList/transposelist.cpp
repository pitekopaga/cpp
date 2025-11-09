// transposelist.cpp : This file contains the implementation file for a transpose list
// Scott Elliott
// Transpose List Implementation

#include "transposelist.h"

// Constructor: creates an empy transpose list by calling base CDLinkedList constructor
TransposeList::TransposeList() : CDLinkedList() {}

// Override contains to implement transpose behavior
// Algorithm:
// 1. Search for anEntry in the list sequentially from front to back
// 2. Increment traverseCount for each node examined (for performance measurement)
// 3. If found:
//    a. get a pointer to the predecessor node (the node before cur)
//    b. if predecessor is header (i.e., cur is at front), do nothing and return true
//    c. otherwise, perform a swap:
//       - unlink cur from its current position
//       - reinsert cur before predecessor (effectively swapping their positions)
// 4. Return true if found, false if not found
bool TransposeList::contains(int anEntry) {
  DListNode* cur = header->next;  // start at first real node
  // sequentially search through the list
  while (cur != header) { // loop continues until back at header
    ++traverseCount;      // increment traverseCount for each node examined
    if (cur->item == anEntry) { 
      // found it, now implement transpose (swap with predecessor)
      DListNode* prevNode = cur->prev; // get predecessor node
      // check if predecessor is header (i.e., cur is at front)
      // if predecessor is header, cur is already at front, so do nothing
      if (prevNode == header) { 
        return true;  // already at front, nothing to do
      }
      // element is not at front, so we need to swap with predecessor
      // Step 1: Unlink cur from its current position
      prevNode->next = cur->next;  // predecessor's next skips over cur, pointing to cur's next
      cur->next->prev = prevNode;  // next node's prev points back to predecessor
      // Step 2: Insert cur before its old predecessor
      /// we need to update four pointers to maintain the circular doubly linked structure
      cur->prev = prevNode->prev;  // current node's prev points to predecessor's prev
      cur->next = prevNode;        // current node's next points to predecessor
      prevNode->prev->next = cur;  // predecessor's old prev's next points to cur
      prevNode->prev = cur;        // old predecessor's prev points back to cur
      return true;                 // element found and swapped with predecessor
    }
    cur = cur->next;               // move to next node to continue search
  }
  // if we reach here, anEntry was not found in the list
  return false; // element not found
}
// Time Complexity:
//   Worst case: O(n) - element could be at the back initially
//   Best case: O(1) - element already at front