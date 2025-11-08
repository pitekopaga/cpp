// driver_mtf.cpp : This file contains the driver file for a Move-To-Front list
// Scott Elliott
// Program 1 - MTF and Transpose List
// CSS501 - Fall 2025

#include "mtflist.h"
#include <iostream>
#include <cassert>

void testMtfList() {
   std::cout << "=== Testing MtfList ===" << std::endl;

   // Test 1: Basic functionality
   MtfList list;
   for (int i = 1; i <= 5; i++) {
      assert(list.add(i) == true);
   }
   std::cout << "Test 1 passed: Elements added" << std::endl;
   list.printList();

   // Test 2: Move-to-front behavior
   assert(list.contains(1) == true);
   assert(list.retrieve(0) == 1); // Should be moved to front
   std::cout << "Test 2 passed: Element moved to front" << std::endl;
   list.printList();

   // Test 3: Performance improvement
   list.resetTraverseCount();
   list.contains(2);
   int count1 = list.getTraverseCount();

   list.resetTraverseCount();
   list.contains(2); // Should be at front now
   int count2 = list.getTraverseCount();

   assert(count2 < count1);
   std::cout << "Test 3 passed: Performance improved - First search: "
      << count1 << ", Second search: " << count2 << std::endl;

   // Test 4: Inherited methods
   assert(list.add(1) == false); // Duplicate
   assert(list.remove(3) == true);
   list.clear();
   assert(list.isEmpty() == true);
   std::cout << "Test 4 passed: Inherited methods work correctly" << std::endl;

   // Test 5: Copy constructor
   MtfList list2;
   list2.add(10);
   MtfList list3(list2);
   assert(list3.getCurrentSize() == 1);
   std::cout << "Test 5 passed: Copy constructor works" << std::endl;

   std::cout << "All MtfList tests passed!" << std::endl << std::endl;
}

/*
int main() {
   testMtfList();
   return 0;
}
*/
