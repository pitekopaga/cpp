// driver.cpp
// Scott Elliott
// 
// Description:
// Main entry point for the Koch Curve Generator program.
// Handles command-line argument parsing, validation, object instantiation, and orchestration
// of the Koch class. The Turtle functionality is now integrated within the Koch class.
// The program outputs Postscript commands to standard output (stdout).
// 
// Usage: ./koch x1 y1 x2 y2 level
//

#include "Koch.h"
#include <iostream>
#include <cstdlib> // For exit()
#include <sstream> // For argument parsing
#include <stdexcept>
#include <cmath>   // For pow() function

// Function: main
// Description: Program entry point. Parses command-line arguments, validates input,
//              initializes the Koch object, and starts the fractal generation.
// Parameters:
//   argc - The number of command-line arguments.
//   argv - An array of C-style strings containing the arguments.
// Return Value: 0 on success, 1 on error.
int main(int argc, char* argv[]) {
  // Check for correct number of arguments (program name + 5 arguments = 6 total)
  if (argc != 6) {
    // Output error message to stderr
    std::cerr << "Error: Incorrect number of arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " x1 y1 x2 y2 level" << std::endl;
    return 1;
  }

  // Variables to hold parsed input
  double x1, y1, x2, y2;
  int level;

  // --- Argument Parsing and Validation ---
  // This block parses the string arguments into their respective numeric types (double/int)
  // and checks for non-numeric input or extra characters after the number.
  try {
    // Use stringstream for robust conversion and error checking
    std::stringstream ss;

    // Parse coordinates (x1, y1, x2, y2) as doubles
    ss.str(argv[1]); ss >> x1; if (ss.fail() || !ss.eof()) throw std::runtime_error("x1"); ss.clear();
    ss.str(argv[2]); ss >> y1; if (ss.fail() || !ss.eof()) throw std::runtime_error("y1"); ss.clear();
    ss.str(argv[3]); ss >> x2; if (ss.fail() || !ss.eof()) throw std::runtime_error("x2"); ss.clear();
    ss.str(argv[4]); ss >> y2; if (ss.fail() || !ss.eof()) throw std::runtime_error("y2"); ss.clear();

    // Parse level as an integer
    ss.str(argv[5]); ss >> level; if (ss.fail() || !ss.eof()) throw std::runtime_error("level"); ss.clear();

  }
  catch (const std::runtime_error& e) {
    // Catch exceptions thrown during stringstream conversion
    std::cerr << "Error: Invalid numeric input for argument '" << e.what() << "'." << std::endl;
    return 1;
  }

  // Validate level
  if (level < 0) {
    // The level must be non-negative, as level 0 is the base case
    std::cerr << "Error: Curve level must be a non-negative integer (>= 0)." << std::endl;
    return 1;
  }

  // --- Max Level Validation ---
  // Define a practical maximum level to prevent excessive computation and output size.
  const int MAX_LEVEL = 10;

  // Validate max level
  if (level > MAX_LEVEL) {
    // Use long long for the power calculation to prevent overflow for large levels
    std::cerr << "Error: Curve level exceeds the maximum practical limit of " << MAX_LEVEL << "." << std::endl;
    std::cerr << "A level of " << level << " would generate over " << (long long)pow(4, level) << " line segments." << std::endl;
    return 1;
  }

  // --- Display Parsed Parameters ---
  std::cerr << "Parameters entered:" << std::endl;
  std::cerr << "  x1 = " << x1 << std::endl;
  std::cerr << "  y1 = " << y1 << std::endl;
  std::cerr << "  x2 = " << x2 << std::endl;
  std::cerr << "  y2 = " << y2 << std::endl;
  std::cerr << "  level = " << level << std::endl;
  std::cerr << std::endl; // Blank line before PostScript output


  // --- Object Instantiation and Orchestration ---

  // 1. Create the Koch object.
  Koch koch;

  // 2. Generate the Koch curve.
  // The Koch object handles the internal Turtle initialization, recursion, and final Postscript output.
  // The output is sent to sdout, which can be redirecte to a file (e.g., ./koch ... > output.ps).
  koch.generateCurve(level, x1, y1, x2, y2);

  return 0; // Exit with success code
}