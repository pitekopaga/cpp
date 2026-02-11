// driver.cpp
// Scott Elliott

// Driver program to test the SortedList template class implementation.
// Tests core functionality, operator overloads, exception handling,
// and the Rule of Five (special member functions for proper resource management).

#include "SortedList.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

using namespace std;

// ============================================================================
// TEST FUNCTION 1: CORE FUNCTIONALITY
// ============================================================================
// Tests basic operations: construction, insertion, access, removal, and clear
// Uses integer type to verify fundamental list behavior
void testCoreFunctionality() {
  cout << "--- Testing Core Functionality (int) ---" << endl;

  // Test default constructor and empty state
  SortedList<int> alist;
  assert(alist.empty() == true);          // Should be empty initially
  assert(alist.size() == 0);              // Size should be 0

  // Test insertion - should maintain sorted order automatically
  alist.insert(3);
  alist.insert(1);
  alist.insert(5);
  alist.insert(2);
  alist.insert(3);                        // Test duplicate insertion
  cout << "List after inserts: " << alist << endl;
  cout << "Size after inserts: " << alist.size() << endl;
  assert(alist.size() == 5);              // Should have 5 elements

  // Test bracket operator access
  assert(alist[0] == 1);                  // First element
  assert(alist[2] == 3);                  // Middle element  
  assert(alist[4] == 5);                  // Last element
  cout << "alist[0]: " << alist[0] << endl;

  // Test removal operation - ADD DEBUGGING
  cout << "Before first remove - Size: " << alist.size() << endl;
  bool remove1 = alist.remove(3);
  cout << "First remove result: " << remove1 << endl;
  cout << "After first remove - Size: " << alist.size() << ", List: " << alist << endl;
  assert(remove1 == true);
  assert(alist.size() == 4);              // Size should decrease

  cout << "Before second remove - Size: " << alist.size() << endl;
  bool remove2 = alist.remove(10);
  cout << "Second remove result: " << remove2 << endl;
  assert(remove2 == false);      // Try to remove non-existent element

  cout << "Before third remove - Size: " << alist.size() << endl;
  bool remove3 = alist.remove(5);
  cout << "Third remove result: " << remove3 << endl;
  cout << "After third remove - Size: " << alist.size() << ", List: " << alist << endl;
  assert(remove3 == true);
  assert(alist.size() == 3);              // Size should be 3 now

  // Test clear operation
  alist.clear();                          // Remove all elements
  assert(alist.empty() == true);          // Should be empty again
  cout << "List after clear: " << alist << endl;  // Should print nothing
  cout << "Core Functionality Test Passed." << endl << endl;
}

// ============================================================================
// TEST FUNCTION 2: OPERATORS AND EXCEPTIONS
// ============================================================================
// Tests operator overloads (+, ==, !=, []) and exception handling
// Verifies that invalid operations throw appropriate exceptions
void testOperatorsAndExceptions() {
  cout << "--- Testing Operators and Exceptions ---" << endl;

  // Create a test list
  SortedList<int> alist;
  alist.insert(1);
  alist.insert(3);

  // Test operator[] exception handling for out-of-bounds access
  try {
    cout << "Attempting to access invalid index [10]..." << endl;
    cout << alist[10] << endl;            // Should throw out_of_range exception
    assert(false);                        // Should never reach here
  }
  catch (const std::out_of_range& oor) {
    // Expected behavior: catch the exception
    cerr << "Caught expected exception: " << oor.what() << endl;
  }

  // Test operator+ (merge two lists)
  SortedList<int> blist;
  blist.insert(2);
  blist.insert(4);
  SortedList<int> clist = alist + blist;  // Merge alist and blist
  assert(clist.size() == 4);              // Result should have 4 elements

  // Verify original lists are unchanged (non-destructive merge)
  cout << "alist: " << alist << endl;     // Should still be: 1, 3
  cout << "blist: " << blist << endl;     // Should still be: 2, 4
  cout << "clist (Merge): " << clist << endl;  // Should be: 1, 2, 3, 4

  // Test operator== and operator!=
  SortedList<int> dlist;
  dlist.insert(1);
  dlist.insert(3);
  assert(alist == dlist);                 // Should be equal (same elements)
  assert(alist != clist);                 // Should be different
  cout << "Equality Test Passed." << endl;
  cout << "Operators and Exceptions Test Passed." << endl << endl;
}

// ============================================================================
// TEST FUNCTION 3: RULE OF FIVE
// ============================================================================
// Tests the five special member functions for proper resource management:
// 1. Copy constructor
// 2. Copy assignment operator
// 3. Move constructor
// 4. Move assignment operator
// 5. Destructor (tested implicitly throughout)
// Uses string type to ensure proper handling of non-trivial types
void testRuleOfFive() {
  cout << "--- Testing Rule of Five ---" << endl;

  // Create original list with strings
  SortedList<string> original;
  original.insert("apple");
  original.insert("zebra");
  original.insert("banana");
  cout << "Original List: " << original << endl;
  // Expected: apple, banana, zebra (alphabetically sorted)

  // TEST 1: Copy Constructor
  // Should create independent deep copy
  SortedList<string> copy = original;     // Invoke copy constructor
  original.remove("apple");               // Modify original
  assert(copy.size() == 3);               // Copy should still have 3 elements
  assert(copy.remove("apple") == true);   // Copy should still contain "apple"
  cout << "Copy List (after original modified): " << copy << endl;

  // TEST 2: Copy Assignment Operator
  // Should perform deep copy via assignment
  SortedList<string> assign;
  assign.insert("x");                     // Add element to be overwritten
  assign = original;                      // Invoke copy assignment
  assert(assign.size() == 2);             // Should match original's current size
  assert(assign[0] == "banana");          // Should have same elements as original
  cout << "Assignment List: " << assign << endl;

  // TEST 3: Move Constructor
  // Should transfer ownership without copying
  SortedList<string> move_cons = std::move(assign);  // Invoke move constructor
  assert(move_cons.size() == 2);          // Should have 2 elements
  assert(assign.empty() == true);         // Source should be empty after move
  cout << "Move Constructed List: " << move_cons << endl;

  // TEST 4: Move Assignment Operator
  // Should transfer ownership via assignment
  SortedList<string> move_assign;
  move_assign.insert("y");                // Add element to be replaced
  move_assign = std::move(move_cons);     // Invoke move assignment
  assert(move_assign.size() == 2);        // Should have 2 elements
  assert(move_cons.empty() == true);      // Source should be empty after move
  cout << "Move Assigned List: " << move_assign << endl;

  cout << "Rule of Five Test Passed." << endl << endl;

  // TEST 5: Destructor
  // Tested implicitly as all local objects go out of scope and are destroyed
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
// Entry point that runs all test suites in sequence
// If all assertions pass, the program completes successfully
int main() {
  testCoreFunctionality();                // Test basic operations
  testOperatorsAndExceptions();           // Test operators and error handling
  testRuleOfFive();                       // Test memory management

  cout << "All tests completed successfully!" << endl;

  return 0;
}