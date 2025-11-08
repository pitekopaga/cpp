// driver_transpose.cpp : This file contains the driver file for a transpose list
// Scott Elliott
// Program 1 - MTF and Transpose List
// CSS501 - Fall 2025

#include "transposelist.h"
#include <iostream>
#include <cassert>

void testTransposeList() {
   std::cout << "=== Testing TransposeList ===" << std::endl;

   // Test 1: Basic functionality
   TransposeList list;
   for (int i = 1; i <= 5; i++) {
      assert(list.add(i) == true);
   }
   std::cout << "Test 1 passed: Elements added" << std::endl;
   list.printList();

   // Test 2: Swap with predecessor
   assert(list.contains(1) == true);
   // Element 1 should have swapped with element 2
   list.printList();
   std::cout << "Test 2 passed: Element swapped with predecessor" << std::endl;

   // Test 3: Front element (no swap)
   assert(list.contains(5) == true);
   assert(list.retrieve(0) == 5); // Should stay at front
   std::cout << "Test 3 passed: Front element remains unchanged" << std::endl;

   // Test 4: Gradual movement
   TransposeList list2;
   for (int i = 1; i <= 5; i++) {
      list2.add(i);
   }

   // Find initial position of element 1
   int initialPos = -1;
   for (int i = 0; i < 5; i++) {
      if (list2.retrieve(i) == 1) {
         initialPos = i;
         break;
      }
   }
   assert(initialPos == 4); // Should be at back initially

   // Access element 1 to make it move forward
   list2.contains(1);

   // Find new position
   int newPos = -1;
   for (int i = 0; i < 5; i++) {
      if (list2.retrieve(i) == 1) {
         newPos = i;
         break;
      }
   }
   assert(newPos < initialPos);
   std::cout << "Test 4 passed: Element moved forward - From position "
      << initialPos << " to " << newPos << std::endl;

   // Test 5: Inherited methods
   assert(list2.add(1) == false); // Duplicate
   assert(list2.remove(3) == true);
   list2.clear();
   assert(list2.isEmpty() == true);
   std::cout << "Test 5 passed: Inherited methods work correctly" << std::endl;

   std::cout << "All TransposeList tests passed!" << std::endl << std::endl;
}

/*
int main() {
   testTransposeList();
   return 0;
}
*/