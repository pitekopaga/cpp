// Test program to evaluate linked list performance
// Originally Written 10/4/19 by Michael Stiber
// Modified for MTF vs Transpose comparison on 10/15/25 by Scott Elliott
// LLStats_SE.cpp
// This program measures and compares the performance of different list implementations under two access patterns:
// 1. Uniform distribution: all items are equally likely to be accessed
// 2. Normal distribution: some items are accessed more frequently than others
// The key metrick is average traverse count (how many nodes are examined to find an element

#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <utility> // For std::make_pair  
#include <limits> // For std::numeric_limits
#include "CDLinkedList.h"
#include "mtflist.h"
#include "transposelist.h"

int main() {
  const int numValues = 1000;
  const int numAccesses = 100000;

  // Generators (define once, reseed for each list to ensure fairness)
  std::default_random_engine generator;
  std::uniform_int_distribution<int> uniform(0, numValues - 1);
  std::normal_distribution<double> normal(numValues / 2.0, numValues / 5.0);

  // Helper lambda to run tests for a given list (reduces code duplication)
  auto runTests = [&](auto& list, const std::string& listName, std::default_random_engine& gen) {
    // Reset and populate list
    list.clear();  // Ensure empty
    for (int i = numValues - 1; i >= 0; i--) {
      list.add(i);
    }
    list.resetTraverseCount();

    // Uniform distribution test
    gen.seed(0);  // Reseed for reproducibility
    for (int i = 0; i < numAccesses; i++) {
      int theNumber = uniform(gen);
      assert(list.contains(theNumber));
    }
    double uniformAvg = list.getTraverseCount() / double(numAccesses);
    std::cout << "For " << listName << ": When all items are accessed equally (uniform distribution), "
      << "the average number of nodes checked per search is " << std::fixed << std::setprecision(2) << uniformAvg << "." << std::endl;

    // Reset for normal test
    list.resetTraverseCount();
    gen.seed(0);  // Reseed again
    for (int i = 0; i < numAccesses; i++) {
      int theNumber;
      do {
        theNumber = static_cast<int>(normal(gen));
      } while (theNumber < 0 || theNumber >= numValues);
      assert(list.contains(theNumber));
    }
    double normalAvg = list.getTraverseCount() / double(numAccesses);
    std::cout << "For " << listName << ": When some items are accessed more often (normal distribution), "
      << "the average number of nodes checked per search is " << std::fixed << std::setprecision(2) << normalAvg << "." << std::endl;

    return std::make_pair(uniformAvg, normalAvg);
    };

  // Test MTF
  std::cout << "\n=== Performance Results for Move-To-Front (MTF) List ===\n" << std::endl;
  MtfList mtfList;
  mtfList.resetTraverseCount();
  auto [mtfUniformAvg, mtfNormalAvg] = runTests(mtfList, "MTF", generator);

  // Test Transpose
  std::cout << "\n=== Performance Results for Transpose List ===\n" << std::endl;
  TransposeList transposeList;
  transposeList.resetTraverseCount();
  auto [transUniformAvg, transNormalAvg] = runTests(transposeList, "Transpose", generator);

  // Optional: Test CDLinkedList baseline
  std::cout << "\n=== Performance Results for Standard Circular Doubly Linked List (Baseline) ===\n" << std::endl;
  CDLinkedList baseList;
  baseList.resetTraverseCount();
  auto [baseUniformAvg, baseNormalAvg] = runTests(baseList, "CDLinkedList", generator);

  // Direct comparisons
  std::cout << "\n=== Performance Comparisons ===\n" << std::endl;
  std::cout << "For the MTF list, it checks about " << std::fixed << std::setprecision(2) << (transNormalAvg - mtfNormalAvg)
    << " fewer nodes per search than the Transpose list when some items are accessed more often." << std::endl;
  std::cout << "The MTF list reduces the average number of nodes checked by about " << std::fixed << std::setprecision(2)
    << (baseNormalAvg - mtfNormalAvg) << " compared to the baseline list when some items are accessed more often." << std::endl;
  std::cout << "The Transpose list reduces the average number of nodes checked by about " << std::fixed << std::setprecision(2)
    << (baseNormalAvg - transNormalAvg) << " compared to the baseline list when some items are accessed more often." << std::endl;

  // Pause console (robust for VS debug console)
  std::cout << "\nPress Enter to exit..." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();

  return 0;
}