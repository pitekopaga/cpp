// SortedList.cpp
// Scott Elliott

// Implementation file for the SortedList template class.
// This file contains the definitions of all methods declared in SortedList.h
// Uses a doubly-linked *linear* list with a dummy header node for simplified
// insertion, deletion, and traversal. The list terminates with nullptr at the tail.

#include "SortedList.h"
#include <stdexcept>
#include <algorithm>

// ============================================================================
// CORE METHODS IMPLEMENTATION
// ============================================================================

// Default Constructor
// Initializes an empty list with a dummy header node whose next and prev are nullptr.
// The header simplifies head insertions/removals by providing a consistent start node.
template <typename Object>
SortedList<Object>::SortedList() : listSize(0) {
  header = new Node();       // Create dummy header node
  header->next = nullptr;
  header->prev = nullptr;
}

// Destructor
// Cleans up all dynamically allocated memory.
// Removes all nodes and then deletes the dummy header.
template <typename Object>
SortedList<Object>::~SortedList() {
  clear();
  delete header;
}

// Clear Method
// Removes all data nodes from the list and resets to an empty state.
template <typename Object>
void SortedList<Object>::clear() {
  Node* current = header->next;
  while (current != nullptr) {
    Node* nextNode = current->next;
    delete current;
    current = nextNode;
  }
  header->next = nullptr;
  listSize = 0;
}

// ============================================================================
// RULE OF FIVE IMPLEMENTATION
// ============================================================================

// Helper method for deep copy
template <typename Object>
void SortedList<Object>::copyFrom(const SortedList& other) {
  Node* current = other.header->next;
  while (current != nullptr) {
    insert(current->data);
    current = current->next;
  }
}

// Copy Constructor
template <typename Object>
SortedList<Object>::SortedList(const SortedList& other) : SortedList() {
  copyFrom(other);
}

// Move Constructor
template <typename Object>
SortedList<Object>::SortedList(SortedList&& other) noexcept
  : header(other.header), listSize(other.listSize) {
  other.header = new Node();  // Give other a new dummy header
  other.header->next = nullptr;
  other.header->prev = nullptr;
  other.listSize = 0;
}

// Copy Assignment Operator
template <typename Object>
SortedList<Object>& SortedList<Object>::operator=(const SortedList& rhs) {
  if (this != &rhs) {
    clear();
    copyFrom(rhs);
  }
  return *this;
}

// Move Assignment Operator
template <typename Object>
SortedList<Object>& SortedList<Object>::operator=(SortedList&& rhs) noexcept {
  if (this != &rhs) {
    // 1. Clear current data nodes
    clear();
    // 2. Delete the current dummy header to prevent leak
    delete header;

    // 3. Steal resources from rhs
    header = rhs.header;
    listSize = rhs.listSize;

    // 4. Put rhs into a valid, empty state
    // Leave rhs with a valid empty list
    rhs.header = new Node();
    rhs.header->next = nullptr;
    rhs.header->prev = nullptr;
    rhs.listSize = 0;
  }
  return *this;
}

// ============================================================================
// HELPER METHODS IMPLEMENTATION
// ============================================================================

// Find Insert Position Helper
// Finds the node *after which* a new item should be inserted to maintain sorted order.
// Returns pointer to first node with data >= item, or nullptr if item is largest.
template <typename Object>
typename SortedList<Object>::Node*
SortedList<Object>::findInsertPosition(const Object& item) const {
  Node* current = header->next;
  while (current != nullptr && current->data < item) {
    current = current->next;
  }
  return current;  // may be nullptr if item is greater than all existing nodes
}

// Remove Node Helper
// Removes a specific node (already located) and updates adjacent pointers.
// Handles the actual pointer manipulation and memory deallocation.
template <typename Object>
void SortedList<Object>::removeNode(Node* p) {
  if (p == nullptr) return;

  // Update previous node's next pointer
  if (p->prev != nullptr) {
    p->prev->next = p->next;
  }
  else {
    // p is the first data node (after header)
    header->next = p->next;
  }

  // Update next node's prev pointer
  if (p->next != nullptr) {
    p->next->prev = p->prev;
  }

  delete p;
  listSize--;
}

// ============================================================================
// MUTATORS IMPLEMENTATION
// ============================================================================

// Remove Method
// Searches for the first occurrence of an item and removes it if found.
// Returns true if item was found and removed, false otherwise.
template <typename Object>
bool SortedList<Object>::remove(const Object& item) {
  Node* current = header->next;
  while (current != nullptr) {
    if (current->data == item) {
      // Found the node to remove
      removeNode(current);
      return true;
    }
    current = current->next;
  }
  return false;
}

// Insert Method
// Inserts an item into the list while maintaining sorted order.
template <typename Object>
bool SortedList<Object>::insert(const Object& item) {
  try {
    Node* newNode = new Node(item);

    // Case 1: Empty list
    if (header->next == nullptr) {
      header->next = newNode;
      newNode->prev = nullptr;
      listSize++;
      return true;
    }

    // Case 2: Insert at beginning (new item is smallest)
    if (item < header->next->data) {
      newNode->next = header->next;
      newNode->prev = nullptr;
      header->next->prev = newNode;
      header->next = newNode;
      listSize++;
      return true;
    }

    // Case 3: Insert in middle or at end
    Node* current = header->next;
    while (current->next != nullptr && current->next->data < item) {
      current = current->next;
    }

    // Insert after current
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != nullptr) {
      current->next->prev = newNode;
    }
    current->next = newNode;

    listSize++;
    return true;
  }
  catch (const std::bad_alloc&) {
    return false;
  }
}

// ============================================================================
// OPERATORS IMPLEMENTATION
// ============================================================================

// Bracket Operator (Subscript)
template <typename Object>
const Object& SortedList<Object>::operator[](int index) const {
  if (index < 0 || index >= listSize)
    throw std::out_of_range("Index out of bounds in SortedList::operator[]");

  Node* current = header->next;
  for (int i = 0; i < index; ++i)
    current = current->next;

  return current->data;
}

// Bracket Operator (Subscript) - Non-const
template <typename Object>
Object& SortedList<Object>::operator[](int index) {
  if (index < 0 || index >= listSize)
    throw std::out_of_range("Index out of bounds in SortedList::operator[]");

  Node* current = header->next;
  for (int i = 0; i < index; ++i)
    current = current->next;

  return current->data;
}

// Addition Operator (Merge)
template <typename Object>
SortedList<Object> SortedList<Object>::operator+(const SortedList& rhs) const {
  SortedList<Object> result = *this;
  Node* current = rhs.header->next;
  while (current != nullptr) {
    result.insert(current->data);
    current = current->next;
  }
  return result;
}

// Equality Operator
template <typename Object>
bool SortedList<Object>::operator==(const SortedList& sl) const {
  if (listSize != sl.listSize)
    return false;

  Node* currentThis = header->next;
  Node* currentSl = sl.header->next;
  while (currentThis != nullptr && currentSl != nullptr) {
    if (!(currentThis->data == currentSl->data))
      return false;
    currentThis = currentThis->next;
    currentSl = currentSl->next;
  }

  return currentThis == nullptr && currentSl == nullptr;
}

// ============================================================================
// FRIEND FUNCTION IMPLEMENTATION
// ============================================================================

template <typename T>
std::ostream& operator<<(std::ostream& os, const SortedList<T>& sl) {
  typename SortedList<T>::Node* current = sl.header->next;
  bool first = true;
  while (current != nullptr) {
    if (!first) os << ", ";
    os << current->data;
    first = false;
    current = current->next;

    // Safety check for infinite loops
    if (first == false && current == sl.header->next) {
      os << " [CYCLE DETECTED!]";
      break;
    }
  }
  return os;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template class SortedList<int>;
template class SortedList<std::string>;
template std::ostream& operator<<(std::ostream& os, const SortedList<int>& sl);
template std::ostream& operator<<(std::ostream& os, const SortedList<std::string>& sl);
