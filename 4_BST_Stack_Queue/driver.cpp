// BST Test Driver
// Compilation: g++ -std=c++11 -Wall -g driver.cpp -o bst_driver
// Execution: ./bst_driver
// Memory Check: valgrind --leak-check=full ./bst_driver

#include "bst.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// Test BST functionality with integer data type
void testIntegerBST() {
  cout << "\n=== Testing BST with Integers ===" << endl;
  BST<int> int_bst;

  // Test insertion and retrieval
  cout << "Inserting values: 4, 2, 1, 3, 6, 5, 7" << endl;
  int_bst.insert(4);
  int_bst.insert(2);
  int_bst.insert(1);
  int_bst.insert(3);
  int_bst.insert(6);
  int_bst.insert(5);
  int_bst.insert(7);

  // Test duplicate insertion (should be ignored)
  cout << "Testing duplicate insertion (4) - should be ignored" << endl;
  int_bst.insert(4);

  // Test retrieval functionality
  cout << "\nTesting retrieval:" << endl;
  cout << "  retrieve(7): " << (int_bst.retrieve(7) ? "PASS" : "FAIL")
    << " (expected: true)" << endl;
  cout << "  retrieve(8): " << (!int_bst.retrieve(8) ? "PASS" : "FAIL")
    << " (expected: false)" << endl;
  cout << "  retrieve(1): " << (int_bst.retrieve(1) ? "PASS" : "FAIL")
    << " (expected: true)" << endl;
  cout << "  retrieve(4): " << (int_bst.retrieve(4) ? "PASS" : "FAIL")
    << " (expected: true)" << endl;

  // Test traversals from root node (4)
  cout << "\nIn-order traversal from root (4):" << endl;
  queue<int> result = int_bst.in_order_traversal(4);
  cout << "  Result: ";
  while (!result.empty()) {
    cout << result.front() << " ";
    result.pop();
  }
  cout << "\n  Expected: 1 2 3 4 5 6 7" << endl;

  cout << "\nPre-order traversal from root (4):" << endl;
  result = int_bst.pre_order_traversal(4);
  cout << "  Result: ";
  while (!result.empty()) {
    cout << result.front() << " ";
    result.pop();
  }
  cout << "\n  Expected: 4 2 1 3 6 5 7" << endl;

  cout << "\nPost-order traversal from root (4):" << endl;
  result = int_bst.post_order_traversal(4);
  cout << "  Result: ";
  while (!result.empty()) {
    cout << result.front() << " ";
    result.pop();
  }
  cout << "\n  Expected: 1 3 2 5 7 6 4" << endl;

  // Test traversals from subtree root (2)
  cout << "\nTesting subtree traversals from node (2):" << endl;
  cout << "In-order traversal from node (2):" << endl;
  result = int_bst.in_order_traversal(2);
  cout << "  Result: ";
  while (!result.empty()) {
    cout << result.front() << " ";
    result.pop();
  }
  cout << "\n  Expected: 1 2 3" << endl;

  cout << "\nPre-order traversal from node (2):" << endl;
  result = int_bst.pre_order_traversal(2);
  cout << "  Result: ";
  while (!result.empty()) {
    cout << result.front() << " ";
    result.pop();
  }
  cout << "\n  Expected: 2 1 3" << endl;

  // Test traversal of non-existent node
  cout << "\nTesting non-existent node (9):" << endl;
  result = int_bst.in_order_traversal(9);
  cout << "  Result size: " << result.size()
    << " (Expected: 0 - empty queue)" << endl;
  cout << "  Test: " << (result.size() == 0 ? "PASS" : "FAIL") << endl;
}

// Test BST functionality with string data type
void testStringBST() {
  cout << "\n=== Testing BST with Strings ===" << endl;
  BST<string> string_bst;

  // Test insertion with strings
  cout << "Inserting strings: D, B, A, C, F, E, G" << endl;
  string_bst.insert("D");
  string_bst.insert("B");
  string_bst.insert("A");
  string_bst.insert("C");
  string_bst.insert("F");
  string_bst.insert("E");
  string_bst.insert("G");

  // Test string retrieval
  cout << "\nTesting string retrieval:" << endl;
  cout << "  retrieve('G'): " << (string_bst.retrieve("G") ? "PASS" : "FAIL")
    << " (expected: true)" << endl;
  cout << "  retrieve('H'): " << (!string_bst.retrieve("H") ? "PASS" : "FAIL")
    << " (expected: false)" << endl;

  // Test inorder traversal (should produce sorted order)
  cout << "\nIn-order traversal with strings:" << endl;
  queue<string> result = string_bst.in_order_traversal("D");
  cout << "  Result: ";
  while (!result.empty()) {
    cout << result.front() << " ";
    result.pop();
  }
  cout << "\n  Expected: A B C D E F G" << endl;
}

// Test edge cases and boundary conditions
void testEdgeCases() {
  cout << "\n=== Testing Edge Cases ===" << endl;

  // Test empty tree operations
  cout << "Testing empty tree:" << endl;
  BST<int> empty_bst;
  cout << "  retrieve(5) on empty tree: "
    << (!empty_bst.retrieve(5) ? "PASS" : "FAIL")
    << " (expected: false)" << endl;
  queue<int> result = empty_bst.in_order_traversal(5);
  cout << "  Traversal of non-existent node in empty tree - size: "
    << result.size() << " (expected: 0)" << endl;
  cout << "  Test: " << (result.size() == 0 ? "PASS" : "FAIL") << endl;

  // Test single node tree
  cout << "\nTesting single node tree:" << endl;
  BST<int> single_bst;
  single_bst.insert(10);
  cout << "  retrieve(10): " << (single_bst.retrieve(10) ? "PASS" : "FAIL")
    << " (expected: true)" << endl;
  result = single_bst.in_order_traversal(10);
  if (!result.empty()) {
    cout << "  In-order of single node: " << result.front()
      << " (expected: 10)" << endl;
    cout << "  Test: " << (result.front() == 10 ? "PASS" : "FAIL") << endl;
  }

  // Test right-skewed tree (degenerate case)
  cout << "\nTesting right-skewed tree:" << endl;
  BST<int> skewed_bst;
  skewed_bst.insert(1);
  skewed_bst.insert(2);
  skewed_bst.insert(3);
  skewed_bst.insert(4);
  skewed_bst.insert(5);

  cout << "In-order traversal of skewed tree:" << endl;
  result = skewed_bst.in_order_traversal(1);
  cout << "  Result: ";
  while (!result.empty()) {
    cout << result.front() << " ";
    result.pop();
  }
  cout << "\n  Expected: 1 2 3 4 5" << endl;
}

void testConstCorrectness() {
  cout << "\n=== Testing Const Correctness ===" << endl;
  BST<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);

  const BST<int>& const_tree = tree;

  cout << "Testing const traversal from root (5):" << endl;
  queue<int> result = const_tree.in_order_traversal(5);
  cout << "  Result: ";
  while (!result.empty()) {
    cout << result.front() << " ";
    result.pop();
  }
  cout << "\n  Expected: 3 5 7" << endl;
  cout << "  Test: " << ((result.size() == 0) ? "PASS" : "FAIL") << endl;
}

int main() {
  cout << "========================================" << endl;
  cout << "  BST Implementation Test Driver" << endl;
  cout << "========================================" << endl;

  // Run all test suites
  testIntegerBST();
  testStringBST();
  testEdgeCases();
  testConstCorrectness();

  cout << "\n========================================" << endl;
  cout << "  All tests completed" << endl;
  cout << "========================================" << endl;
  cout << "\nTo verify memory management, run:" << endl;
  cout << "  valgrind --leak-check=full ./bst_driver" << endl;
  cout << "\n";

  return 0;
}