#ifndef BST_CPP
#define BST_CPP

#include "bst.h"

// Private recursive helper to insert a value into the BST
// Uses reference to pointer to modify parent's child pointer
template <typename Object>
void BST<Object>::insert(Node<Object>*& node, const Object& value) {
  if (node == nullptr) {
    // Base case: create new node when we reach insertion point
    node = new Node<Object>(value);
  }
  else if (value < node->data) {
    // Recursive case: value is less than current node, go left
    insert(node->left, value);
  }
  else if (value > node->data) {
    // Recursive case: value is greater than current node, go right
    insert(node->right, value);
  }
  // If value equals node data, do nothing (ignore duplicates)
}

// Private recursive helper to search for a value in the BST
// Returns true if value found, false otherwise
template <typename Object>
bool BST<Object>::retrieve(Node<Object>* node, const Object& value) const {
  if (node == nullptr) {
    // Base case: value not found
    return false;
  }
  else if (value < node->data) {
    // Recursive case: search left subtree
    return retrieve(node->left, value);
  }
  else if (value > node->data) {
    // Recursive case: search right subtree
    return retrieve(node->right, value);
  }
  else {
    // Base case: value found
    return true;
  }
}

// Private recursive helper to find a specific node by value
// Returns pointer to node if found, nullptr otherwise
template <typename Object>
Node<Object>* BST<Object>::findNode(Node<Object>* node,
  const Object& value) const {
  if (node == nullptr) {
    return nullptr;
  }
  else if (value < node->data) {
    return findNode(node->left, value);
  }
  else if (value > node->data) {
    return findNode(node->right, value);
  }
  else {
    return node;
  }
}

// Private recursive helper to deallocate all nodes in the BST
// Uses post-order traversal to safely delete nodes
template <typename Object>
void BST<Object>::clear(Node<Object>* node) {
  if (node != nullptr) {
    clear(node->left);   // Delete left subtree first
    clear(node->right);  // Delete right subtree next
    delete node;         // Delete current node last
  }
}

// Constructor: initializes empty BST with null root
template <typename Object>
BST<Object>::BST() : root(nullptr) {}

// Destructor: cleans up all dynamically allocated nodes
template <typename Object>
BST<Object>::~BST() {
  clear(root);
}

// Public method to insert a value into the BST
// Calls private recursive helper starting from root
template <typename Object>
void BST<Object>::insert(const Object& value) {
  insert(root, value);
}

// Public method to check if a value exists in the BST
// Calls private recursive helper starting from root
template <typename Object>
bool BST<Object>::retrieve(const Object& value) const {
  return retrieve(root, value);
}

// Pre-order traversal: Root -> Left -> Right
// Iterative implementation using stack
template <typename Object>
queue<Object> BST<Object>::pre_order_traversal(const Object& value) const {
  queue<Object> result;
  Node<Object>* startNode = findNode(root, value);

  // Return empty queue if starting node not found
  if (startNode == nullptr) {
    return result;
  }

  stack<Node<Object>*> nodeStack;
  nodeStack.push(startNode);

  while (!nodeStack.empty()) {
    Node<Object>* current = nodeStack.top();
    nodeStack.pop();
    result.push(current->data);

    // Push right child first, then left
    // So left child gets processed next (LIFO)
    if (current->right != nullptr) {
      nodeStack.push(current->right);
    }
    if (current->left != nullptr) {
      nodeStack.push(current->left);
    }
  }

  return result;
}

// In-order traversal: Left -> Root -> Right  
// Iterative implementation using stack
// Produces sorted output for BST
template <typename Object>
queue<Object> BST<Object>::in_order_traversal(const Object& value) const {
  queue<Object> result;
  Node<Object>* startNode = findNode(root, value);

  if (startNode == nullptr) {
    return result;
  }

  stack<Node<Object>*> nodeStack;
  Node<Object>* current = startNode;

  while (current != nullptr || !nodeStack.empty()) {
    // Traverse to the leftmost node of current subtree
    while (current != nullptr) {
      nodeStack.push(current);
      current = current->left;
    }

    // Process the node at top of stack
    current = nodeStack.top();
    nodeStack.pop();
    result.push(current->data);

    // Move to right subtree
    current = current->right;
  }

  return result;
}

// Post-order traversal: Left -> Right -> Root
// Most complex iterative traversal using single stack
template <typename Object>
queue<Object> BST<Object>::post_order_traversal(const Object& value) const {
  queue<Object> result;
  Node<Object>* startNode = findNode(root, value);

  if (startNode == nullptr) {
    return result;
  }

  stack<Node<Object>*> nodeStack;
  Node<Object>* current = startNode;
  Node<Object>* lastVisited = nullptr;

  while (current != nullptr || !nodeStack.empty()) {
    if (current != nullptr) {
      // Go to leftmost node
      nodeStack.push(current);
      current = current->left;
    }
    else {
      Node<Object>* peekNode = nodeStack.top();
      // If right child exists and not visited yet, go right
      if (peekNode->right != nullptr && lastVisited != peekNode->right) {
        current = peekNode->right;
      }
      else {
        // Process the node
        result.push(peekNode->data);
        lastVisited = peekNode;
        nodeStack.pop();
      }
    }
  }

  return result;
}

#endif