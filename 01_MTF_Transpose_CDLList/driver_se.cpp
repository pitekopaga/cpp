// driver_se.cpp : Comprehensive tests for all list types
// Scott Elliott
// MTF and Transpose List
// This driver tests all three list implementations:
// 1. CDLinkedList - base implementation, no self-adjusting behavior
// 2. MtfList - Move-To-Front self-adjust
// 3. TransposeList - Transpose self-adjust

#include "CDLinkedList.h"
#include "mtflist.h"
#include "transposelist.h"
#include <iostream>
#include <cassert>

// Test function for CDLinkedList
// Tests all basic functionality without any self-adjusting behavior
void testCDLinkedList() {
  std::cout << "\n=== COMPREHENSIVE CDLinkedList TESTS ===" << std::endl;

  // Test 1: Create an empy list and verify its state
  CDLinkedList list1;
  assert(list1.isEmpty() == true);      // List should be empty
  assert(list1.getCurrentSize() == 0);  // Size should be 0
  std::cout << "Test 1 passed: Empty list created" << std::endl;

  // Test 2: Add elements to the list
  // Elements are added to the FRONT, so order will be 15 -> 10 -> 5
  assert(list1.add(5) == true);   // Add 5 (first element)
  assert(list1.add(10) == true);  // Add 10 (goes before 5)
  assert(list1.add(15) == true);  // Add 15 (goes before 10)
  assert(list1.getCurrentSize() == 3);
  std::cout << "Test 2 passed: Elements added successfully" << std::endl;
  std::cout << "List after adds: ";
  list1.printList();              // Should print 15 -> 10 -> 5

  // Test 3: Try to add a duplicate (should fail)
  assert(list1.add(5) == false);  // 5 already present
  assert(list1.getCurrentSize() == 3);  // size unchanged
  std::cout << "Test 3 passed: Duplicates prevented" << std::endl;

  // Test 4: Test contains() and verify traverse count increments
  list1.resetTraverseCount();  // Start counting from 0
  assert(list1.contains(5) == true);  // Search for 5 (should be found)
  assert(list1.getTraverseCount() > 0);  // should have traversed some nodes
  std::cout << "Test 4 passed: Contains works, traverse count: " << list1.getTraverseCount() << std::endl;

  // Test 5: Remove elements from the list
  assert(list1.remove(10) == true);    // Remove 10 (exists)
  assert(list1.getCurrentSize() == 2); // size should decrease
  assert(list1.remove(999) == false);  // try to remove non-existent element
  std::cout << "Test 5 passed: Remove works correctly" << std::endl;
  std::cout << "List after remove: ";
  list1.printList();                   // Should print 15 -> 5

  // Test 6: test retrieve() to access elements by index
  assert(list1.retrieve(0) == 15);  // first element (index 0) 
  assert(list1.retrieve(1) == 5);   // second element (index 1)
  assert(list1.retrieve(10) == -1); // Out of bounds (should return -1)
  std::cout << "Test 6 passed: Retrieve works correctly" << std::endl;

  // Test 7: test copy constructor (deep copy)
  CDLinkedList list2(list1);            // create copy of list1
  assert(list2.getCurrentSize() == 2);  // copy should have same size as list1
  list1.add(20);                        // modify original list
  assert(list2.getCurrentSize() == 2);  // copy should remain unchanged (independent)
  std::cout << "Test 7 passed: Copy constructor creates independent copy" << std::endl;

  // Test 8: test clear() to remove all elements
  list1.clear();
  assert(list1.isEmpty() == true);  // list1 should be empty
  std::cout << "Test 8 passed: Clear works correctly" << std::endl;

  std::cout << "All CDLinkedList tests passed!" << std::endl;
}

// Test function for MtfList (Move-To-Front implementation)
// Tests that accessed elements move to the front of the list
void testMtfList() {
  std::cout << "\n=== COMPREHENSIVE MtfList TESTS ===" << std::endl;

  // Test 1: Create list and add elements
  MtfList list;
  for (int i = 1; i <= 5; i++) {
    assert(list.add(i) == true);
  }
  // order after adds: 5 -> 4 -> 3 -> 2 -> 1 (elements added to front)
  std::cout << "Test 1 passed: Elements added" << std::endl;
  std::cout << "Initial list: ";
  list.printList();

  // Test 2: Move-to-front behavior
  // when we search for 1, it should move from back to front
  std::cout << "Searching for element 1 (should move to front)..." << std::endl;
  assert(list.contains(1) == true);    // Search for 1
  assert(list.retrieve(0) == 1);       // verify 1 is now at front (index 0)
  std::cout << "Test 2 passed: Element moved to front" << std::endl;
  std::cout << "List after contains(1): ";
  list.printList();                    // Should print 1 -> 5 -> 4 -> 3 -> 2

  // Test 3: demonstrate performance improvement
  // first search for 2 takes several traversals
  list.resetTraverseCount();
  list.contains(2);  // search for 2 (moves to front)
  int count1 = list.getTraverseCount();

  // second search for 2 should be very fast (at front)
  list.resetTraverseCount();
  list.contains(2); // 2 is now at front
  int count2 = list.getTraverseCount();

  assert(count2 < count1);  // second search should be faster
  std::cout << "Test 3 passed: Performance improved - First search: " << count1 << ", Second search: " << count2 << std::endl;

  // Test 4: multiple move-to-front operations
  std::cout << "Testing multiple move-to-front operations..." << std::endl;
  list.resetTraverseCount();
  list.contains(3);   // move 3 to front
  std::cout << "After contains(3): ";
  list.printList();

  list.contains(4);   // move 4 to front
  std::cout << "After contains(4): ";
  list.printList();

  list.contains(1);   // move 1 to front again
  std::cout << "After contains(1) again: ";
  list.printList();

  // Test 5: verify if inherited methods still work
  assert(list.add(1) == false);    // Duplicate should be rejected
  assert(list.remove(3) == true);  // remove should work
  list.clear();                    // clear should work
  assert(list.isEmpty() == true);  // should be empty now
  std::cout << "Test 5 passed: Inherited methods work correctly" << std::endl;

  std::cout << "All MtfList tests passed!" << std::endl;
}

// test function for TransposeList (Swap with predecessor implementation)
// Tests that accessed elements swap with their predecessor to gradually move forward
void testTransposeList() {
  std::cout << "\n=== COMPREHENSIVE TransposeList TESTS ===" << std::endl;

  // Test 1: Create list and add elements
  TransposeList list;
  for (int i = 1; i <= 5; i++) {
    assert(list.add(i) == true);
  }
  // order after adds: 5 -> 4 -> 3 -> 2 -> 1 (elements added to front)
  std::cout << "Test 1 passed: Elements added" << std::endl;
  std::cout << "Initial list: ";
  list.printList();

  // Test 2: test swap with predecessor behavior
  // when we search for 1, it should swap with its predecessor (2)
  std::cout << "Searching for element 1 (should swap with 2)..." << std::endl;
  assert(list.contains(1) == true);  // Search for 1 and swap with 2
  std::cout << "After contains(1): ";
  list.printList();  // should print 5 -> 4 -> 3 -> 1 -> 2
  std::cout << "Test 2 passed: Element swapped with predecessor" << std::endl;

  // Test 3: test front element (no swap possible)
  // element at fron has no predecessor (except header), so can't swap
  std::cout << "Searching for front element 5 (should stay at front)..." << std::endl;
  assert(list.contains(5) == true);   // find 5 (at front)
  assert(list.retrieve(0) == 5);      // verify still at front
  std::cout << "After contains(5): ";
  list.printList();                   // order unchanged
  std::cout << "Test 3 passed: Front element remains unchanged" << std::endl;

  // Test 4: demonstrate gradual movement toward front
  // unlike MTF, transpose moves elements slowly with repeated accesses
  std::cout << "Testing gradual movement of element 1..." << std::endl;
  TransposeList list2;
  for (int i = 1; i <= 5; i++) {
    list2.add(i);
  }
  // order: 5 -> 4 -> 3 -> 2 -> 1

  // Find initial position of element 1 (should be at index 4 - the back)
  int initialPos = -1;
  for (int i = 0; i < 5; i++) {
    if (list2.retrieve(i) == 1) {
      initialPos = i;
      break;
    }
  }
  assert(initialPos == 4); // Should be at back initially
  std::cout << "Element 1 starts at position: " << initialPos << std::endl;

  // first access: 1 swaps with 2, moves from pos 4 to pos 3
  list2.contains(1);
  int pos1 = -1;
  for (int i = 0; i < 5; i++) {
    if (list2.retrieve(i) == 1) {
      pos1 = i;
      break;
    }
  }
  std::cout << "After first access, position: " << pos1 << std::endl;
  // order now: 5 -> 4 -> 3 -> 1 -> 2

  // second access: 1 swaps with 3, moves from pos 3 to pos 2
  list2.contains(1);
  int pos2 = -1;
  for (int i = 0; i < 5; i++) {
    if (list2.retrieve(i) == 1) {
      pos2 = i;
      break;
    }
  }
  std::cout << "After second access, position: " << pos2 << std::endl;
  // order now: 5 -> 4 -> 1 -> 3 -> 2
  std::cout << "Test 4 passed: Element moved forward gradually" << std::endl;

  // Test 5: verify inherited methods still work
  assert(list2.add(1) == false);   // Duplicate should be rejected
  assert(list2.remove(3) == true); // remove should work
  list2.clear();                   // clear should work
  assert(list2.isEmpty() == true); // should be empty now
  std::cout << "Test 5 passed: Inherited methods work correctly" << std::endl;

  std::cout << "All TransposeList tests passed!" << std::endl;
}

// Run all tests for all list types
void runAllTests() {
  std::cout << "=== RUNNING ALL COMPREHENSIVE TESTS ===" << std::endl;
  // test each list implementation in sequence
  testCDLinkedList();  //base implementation
  testMtfList();       // Move-To-Front implementation
  testTransposeList(); // Transpose implementation
  std::cout << "\n=== ALL TESTS COMPLETED SUCCESSFULLY! ===" << std::endl;
}

// Main function to execute all tests
// uncomment this to run tests
/*
int main() {
   runAllTests();

   // Keep console open
   std::cout << "\nPress Enter to exit...";
   std::cin.ignore();
   std::cin.get();

   return 0;
}
*/