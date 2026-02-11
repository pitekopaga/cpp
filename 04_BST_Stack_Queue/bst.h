#ifndef BST_H
#define BST_H

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// Node structure for Binary Search Tree
// Each node contains data and pointers to left and right children
template <typename Object>
struct Node {
  Object data;           // The data stored in this node
  Node* left;            // Pointer to left child node
  Node* right;           // Pointer to right child node

  // Constructor: initializes node with value and null children
  Node(const Object& value) : data(value), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class template
// Supports insertion, retrieval, and three types of tree traversals
template <typename Object>
class BST {
private:
  Node<Object>* root;    // Root pointer of the BST

  // Private recursive helper methods
  void insert(Node<Object>*& node, const Object& value);
  bool retrieve(Node<Object>* node, const Object& value) const;
  Node<Object>* findNode(Node<Object>* node, const Object& value) const;
  void clear(Node<Object>* node);

public:
  BST();      // Constructor
  ~BST();     // Destructor

  // Public interface methods
  void insert(const Object& value);           // Insert value into BST
  bool retrieve(const Object& value) const;   // Check if value exists

  // Traversal methods that return queues of values
  queue<Object> pre_order_traversal(const Object& value) const; // Root->L->R
  queue<Object> in_order_traversal(const Object& value) const;  // L->Root->R 
  queue<Object> post_order_traversal(const Object& value) const;// L->R->Root
};

// Include the implementation for template class
#include "bst.cpp"

#endif