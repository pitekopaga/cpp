// CDLinkedList.cpp : This file contains the implementation file for a circular doubly linked list
// Scott Elliott
// CDLinked List Implementation

#include "CDLinkedList.h"
#include <iostream>
#include <stdexcept>

// Constructor: Initializes an empty list with a dummy header node
// The dummy header simplifies edge cases by ensuring the list always has at least one node
CDLinkedList::CDLinkedList() : traverseCount(0), currentSize(0) {
  // create a new empty dummy header node
  header = new DListNode();
  header->item = -1; // dummy value - never used

  // set up circular structure: header points to itself (empty list)
  header->next = header;
  header->prev = header;

}

// Copy constructor: deep copy of rhs preserving order
// deep cop
CDLinkedList::CDLinkedList(const CDLinkedList& rhs) : traverseCount(0), currentSize(0) {
  // first create new empty list with dummy header
  header = new DListNode();
  header->next = header;
  header->prev = header;

  // traverse source list forward from the beginning to end
  // add elements to the back so the final order matches the source list
  DListNode* cur = rhs.header->next; // start at first real node
  while (cur != rhs.header) { // loop until we return to header
    DListNode* newNode = new DListNode;
    newNode->item = cur->item; // copy the data value
    
    // insert at back (before header) to preserve order
    newNode->prev = header->prev;  // new node's prev points to the current last node
    newNode->next = header;        // new node's next points to header
    header->prev->next = newNode;  // old last node's next points to new node
    header->prev = newNode;        // header's prev points to new node
    currentSize++;                 // increment size counter
    cur = cur->next;               // move to next node in source list (forward direction)
  }
}

// Destructor: cleans up all nodes when object is destroyed
// called automatically when list goes out of scope
CDLinkedList::~CDLinkedList() {
  clear();        // remove all data nodes
  delete header;  // delete dummy header node
}

// returns the number of elements in the list
int CDLinkedList::getCurrentSize() const {
  return currentSize;
}

// returns true if list contains no data nodes (but still has dummy header)
bool CDLinkedList::isEmpty() const {
  return currentSize == 0;
}

// adds newEntry to the front of the list, right after the header
// returns false if newEntry is already present (no duplicates allowed)
bool CDLinkedList::add(int newEntry) {
  // first check if this value already exists in the list
  // the contains() call will increment traverseCount as it searches
  if (contains(newEntry)) {
    return false; // duplicate found, do not add
  }
  // try to allocate a new node
  DListNode* newNode = nullptr;
  try {
    newNode = new DListNode;
    newNode->item = newEntry; // assign item value
  }
  catch (std::bad_alloc&) {
    // if memory allocation fails, return false
    return false;
  }
  // insert new node immediately after header (front). this maintains circular doubly linked structure
  newNode->next = header->next;    // new node 's next points to old first node
  newNode->prev = header;          // new node 's prev points to header
  header->next->prev = newNode;    // old first node 's prev points to new node
  header->next = newNode;          // header's next points to new node
  ++currentSize;                   // increment size counter
  return true;                     // successfully added
}

// removes an element from the list if it still exists
// returns true if removed, false if not found
bool CDLinkedList::remove(int anEntry) {
  // early exit if list is empty
  if (isEmpty()) 
    return false;
  // search for the node containing anEntry
  DListNode* cur = header->next; // start at first real node
  while (cur != header) {  // loop until we return to header
    ++traverseCount;       // count this node examination
    if (cur->item == anEntry) {
      // found item to remove. now unlink this node from the list
      // this is a 2-step process: to maintain doubly linked structure
      cur->prev->next = cur->next;   // previous node 's next skips over cur
      cur->next->prev = cur->prev;   // next node points back to previous node
      delete cur;                    // deallocate the node's memory
      --currentSize;                 // decrement size counter
      return true;                   // successfully removed
    }
    cur = cur->next;                 // move to next node
  }
  return false;                      // not found in list
}

// removes all data nodes, but keeps dummy header
void CDLinkedList::clear() {
  DListNode* cur = header->next;  // start at first real node

  // delete each node one by one until we return to header
  while (cur != header) {       // loop until we return to header
    DListNode* toDelete = cur;  // remember this node to delete
    cur = cur->next;            // move to next node
    delete toDelete;            // now safe to delete the remembered node
  }
  // reset the list to empty state
  header->next = header;        // header points to itself
  header->prev = header;        // header points to itself
  currentSize = 0;              // size is now zero
  // do not reset traverseCount (design choice)
}

// searches for anEntry in the list
// returns true if found, false if not found
// Virtual keyword CRITICAL - allows derived classes to override this method to implement different behaviors
bool CDLinkedList::contains(int anEntry) {
  DListNode* cur = header->next;  // start at first real node
  // sequentially search through the list
  while (cur != header) {   // loop until back at header
    ++traverseCount;        // count each node we examine
    if (cur->item == anEntry) 
      return true;          // found it
    cur = cur->next;        // move to next node
  }
  return false;             // searched entire list, not found
}

// returns current traversal count (used for performance measurement)
int CDLinkedList::getTraverseCount() const {
  return traverseCount;
}

// resets traversal count to zero
// call this before running a performance test to get accurate counts
void CDLinkedList::resetTraverseCount() {
  traverseCount = 0;
}

// retrieve index 0-based (0 is first real node after header)
// returns -1 on invalid index
int CDLinkedList::retrieve(const int index) {
  // bounds check: index must be between 0 and currentSize-1
  if (index < 0 || index >= currentSize)
    return -1; // invalid index
  
  // traverse the list to the desired index
  DListNode* cur = header->next;  // start at first real node
  for (int pos = 0; pos < index; pos++) {
    cur = cur->next;              // move forwrd to next node
    ++traverseCount;              // Increment traverseCount for each node examined
  }
  ++traverseCount;                // Count the node at the index as well
  return cur->item;               // return the data value
}

// Prints all elements in the list from front to back
void CDLinkedList::printList() {
  if (isEmpty()) { // empty list case
    std::cout << "List is empty" << std::endl;
    return;
  }

  DListNode* current = header->next; // start at first real node
  std::cout << "List contents: ";

  // print each node's value
  while (current != header) {  // loop until back at header
    std::cout << current->item;

    // add arrow between elements for clarity
    if (current->next != header) {
      std::cout << " -> ";
    }
    current = current->next; // move to next node
  }

  std::cout << std::endl;
}

