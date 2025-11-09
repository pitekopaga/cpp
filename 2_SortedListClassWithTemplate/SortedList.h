// SortedList.h
// Scott Elliott


// This header file defines a Sorted List Class with Template that maintains
// elements in sorted order. It implements a linear doubly-linked list with
// a dummy header node to simplify insertion and deletion operations.
// The list terminates with nullptr pointers at both ends.

#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

template <typename Object>
class SortedList {
private:
  // Node structure for the doubly-linked linear list
  // Each node contains data and pointers to both next and previous nodes.
  struct Node {
    Object data;        // The stored element
    Node* next;         // Pointer to the next node in the list
    Node* prev;         // Pointer to the previous node in the list

    // Node constructor with default parameters
    Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr)
      : data{ d }, prev{ p }, next{ n } {
    }
  };

  Node* header;         // Dummy header node (simplifies head insertion/removal)
  int listSize;         // Current number of elements in the list

  // Helper method to find correct insertion position to maintain sorted order
  // Returns a pointer to the node before which the new item should be inserted
  Node* findInsertPosition(const Object& item) const;

  // Helper method for deep copy
  void copyFrom(const SortedList& other);

  // Helper method to remove a specific node (already located)
  // Handles pointer updates and memory deallocation for a given node
  void removeNode(Node* p);

public:
  // --- Core Methods ---

  // Default constructor: Creates an empty sorted list with a dummy header.
  SortedList();

  // Destructor: Cleans up all dynamically allocated memory.
  ~SortedList();

  // Removes all elements from the list and resets to empty state.
  void clear();

  // --- Rule of Five ---
  SortedList(const SortedList& other);         // Copy constructor
  SortedList(SortedList&& other) noexcept;              // Move constructor
  SortedList& operator=(const SortedList& rhs);// Copy assignment
  SortedList& operator=(SortedList&& rhs) noexcept;     // Move assignment

  // --- Accessors ---
  int size() const { return listSize; }        // Returns number of elements
  bool empty() const { return size() == 0; }   // Returns true if list is empty

  // --- Mutators ---
  bool insert(const Object& item);             // Insert item in sorted order
  bool remove(const Object& item);             // Remove first occurrence of item

  // --- Operators ---
  Object& operator[](int index); // Non-const access element by index
  const Object& operator[](int index) const; // Const access element by index
  SortedList operator+(const SortedList& rhs) const; // Merge two lists
  bool operator==(const SortedList& sl) const; // Equality comparison
  bool operator!=(const SortedList& sl) const { return !(*this == sl); }

  // --- Friend Functions ---
  template <typename T>
  friend std::ostream& operator<<(std::ostream& os, const SortedList<T>& sl);
};

#endif // SORTEDLIST_H