// driver_cdlist.cpp : This file contains the driver file for a circular doubly linked list
// Scott Elliott
// Program 1 - MTF and Transpose List
// CSS501 - Fall 2025

#include "CDLinkedList.h"
#include <iostream>
#include <cassert>

void testCDLinkedList() {
   std::cout << "=== Testing CDLinkedList ===" << std::endl;

   // Test 1: Empty list
   CDLinkedList list1;
   assert(list1.isEmpty() == true);
   assert(list1.getCurrentSize() == 0);
   std::cout << "Test 1 passed: Empty list created" << std::endl;

   // Test 2: Add elements
   assert(list1.add(5) == true);
   assert(list1.add(10) == true);
   assert(list1.add(15) == true);
   assert(list1.getCurrentSize() == 3);
   std::cout << "Test 2 passed: Elements added successfully" << std::endl;

   // Test 3: Duplicate prevention
   assert(list1.add(5) == false);
   assert(list1.getCurrentSize() == 3);
   std::cout << "Test 3 passed: Duplicates prevented" << std::endl;

   // Test 4: Contains and traverse count
   list1.resetTraverseCount();
   assert(list1.contains(5) == true);
   assert(list1.getTraverseCount() > 0);
   std::cout << "Test 4 passed: Contains works, traverse count: "
      << list1.getTraverseCount() << std::endl;

   // Test 5: Remove elements
   assert(list1.remove(10) == true);
   assert(list1.getCurrentSize() == 2);
   assert(list1.remove(999) == false); // Non-existent
   std::cout << "Test 5 passed: Remove works correctly" << std::endl;

   // Test 6: Retrieve
   assert(list1.retrieve(0) == 15); // Last added should be first
   assert(list1.retrieve(1) == 5);
   assert(list1.retrieve(10) == -1); // Out of bounds
   std::cout << "Test 6 passed: Retrieve works correctly" << std::endl;

   // Test 7: Copy constructor
   CDLinkedList list2(list1);
   assert(list2.getCurrentSize() == 2);
   list1.add(20);
   assert(list2.getCurrentSize() == 2); // Independent copy
   std::cout << "Test 7 passed: Copy constructor creates independent copy" << std::endl;

   // Test 8: Clear
   list1.clear();
   assert(list1.isEmpty() == true);
   std::cout << "Test 8 passed: Clear works correctly" << std::endl;

   // Test 9: Print list (visual verification)
   list2.printList();

   std::cout << "All CDLinkedList tests passed!" << std::endl << std::endl;
}

/*
int main() {
   testCDLinkedList();
   return 0;
}
*/