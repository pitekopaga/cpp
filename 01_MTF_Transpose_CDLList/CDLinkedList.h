// CDLinkedList.h : This file contains the header file for a circular doubly linked list
// Scott Elliott
// CDLinkedList Header

#ifndef CDLINKEDLIST_H
#define CDLINKEDLIST_H

#include <cstddef>

struct DListNode {
  int item;            // The data value stored in this node
  DListNode* prev;     // Pointer to the previous node
  DListNode* next;     // Pointer to the next node

  // Constructor with default parameter
  // If no value is provided, item is initialized to 0
  // Always initializes pointers to nullptr for safety
  DListNode(int val = 0) : item(val), prev(nullptr), next(nullptr) {}
};

// Base class: Circular Doubly Linked List with Dummy Header
// This list maintains a circular structure where the last node connects back to the first node
// A dummy header node simplifies edge cases by ensuring the list always has at least one node
class CDLinkedList {

protected: // protected members accessible by derived classes (e.g., MtfList, TransposeList)
  DListNode* header;        // dummy header node - does not store valid data
  int traverseCount;        // counts node examinations

private:   // private members can only be accessed within this class
  int currentSize;          // number of actual nodes (excluding dummy header)

public:    // public interface - these methods can be called by anyone using the class
  CDLinkedList();           // default constructor - creates empty list
  CDLinkedList(const CDLinkedList& rhs);  // copy constructor - creates a deep copy (all nodes duplicated)
  ~CDLinkedList();          // destructor - cleans up all nodes in derived classes

  // query methods (const since they do not modify the list)
  int getCurrentSize() const; // returns the number of elements in the list
  bool isEmpty() const;       // returns true if list has no elements

  // add newEntry to front if not present; uses contains() to detect duplicates
  // returns true if added, false if duplicate found
  bool add(int newEntry);

  // remove anEntry from the list if present
  // returns true if removed, false if not found
  bool remove(int anEntry);

  // removes all data nodes, but keeps dummy header
  void clear();

  // searches for anEntry in the list
  // returns true if found, false if not found
  // Virtual keyword CRITICAL - allows derived classes to override this method to implement different behaviors
  // move-to-front and transose behaviors will be implemented in derived classes
  virtual bool contains(int anEntry);

  // traverseCount management
  int getTraverseCount() const;  // returns current traversal count
  void resetTraverseCount();     // resets traversal count to zero

  // retrieve index 0-based (0 is first real node after header)
  // returns -1 on invalid index
  int retrieve(const int index); // retrieve the data by index. The first item is at index 0.

  void printList(); // prints all elements in the list from front to back
};
#endif // CDLINKEDLIST_H