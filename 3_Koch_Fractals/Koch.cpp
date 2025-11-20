// Koch.cpp
// Scott Elliott
// 
// Description:
// Implementation of the Koch class and its nested TurtleHelper class.
// This file contains the logic for the fractal generation and the Postscript output.
//

#include "Koch.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

// --- Implementation of TurtleHelper (Nested Class) ---

// Helper function to convert degrees to radians
double Koch::TurtleHelper::degToRad(double degrees) const {
  // Formula: radians = degrees * (pi / 180)
  return degrees * M_PI / 180.0;
}

// Constructor
Koch::TurtleHelper::TurtleHelper(double x, double y, double angle) : currentX(x), currentY(y), currentAngle(angle) {
  // Set output precision for floating-point coordinates to ensure Postscript readability
  std::cout << std::fixed << std::setprecision(3);

  // Output Postscript Header and Bounding Box
  std::cout << "%!PS-Adobe-2.0" << std::endl;
  std::cout << "%%BoundingBox: 0 0 600 600" << std::endl;  // Define canvas size

  // Output initial moveto command to set the starting point of the path
  std::cout << currentX << " " << currentY << " moveto" << std::endl;
}

// Changes the currentAngle by the specified number of degrees.
void Koch::TurtleHelper::turn(double degrees) {
  currentAngle += degrees;
  // Normalize angle to keep it within the range [0, 360)
  if (currentAngle >= 360.0) {
    currentAngle -= 360.0;
  }
  else if (currentAngle < 0.0) {
    currentAngle += 360.0;
  }
}

// Calculates the displacement (dx, dy) based on currentAngle and length.
// Updates currentX and currentY. Outputs the 'rlineto' Postscript command.
void Koch::TurtleHelper::drawLine(double length) {
  // Convert current angle to radians for trigonometric functions
  double angleRad = degToRad(currentAngle);

  // Calculate displacement using trigonometric functions (SOH CAH TOA)
  double dx = length * std::cos(angleRad);
  double dy = length * std::sin(angleRad);

  // Update current position
  currentX += dx;
  currentY += dy;

  // Output rlineto command (relative line to) to Postscript output
  std::cout << dx << " " << dy << " rlineto" << std::endl;
}

// Outputs the 'stroke' Postscript command to render the path.
void Koch::TurtleHelper::outputStroke() {
  // Renders the path defined by moveto/rlineto commands
  std::cout << "stroke" << std::endl;
}

// Outputs the 'showpage' Postscript command to display the page.
void Koch::TurtleHelper::outputShowpage() {
  // Finalizes the Postscript output and displays the page
  std::cout << "showpage" << std::endl;
}

// --- Implementation of Koch Class ---

// Constructor
Koch::Koch() : turtle(nullptr) {
 // Initialize turtle pointer to nullptr. The actual TurtleHelper object
 // is dynamically created and managed within generateCurve
}
// Destructor   
Koch::~Koch() {
  // Clean up the dynamically allocated turtle object if it exists
  delete turtle;
}

// Recursive Helper Function.
// Implements the core Koch curve logic.
void Koch::drawKoch(int level, double length) {
  // Base Case: If level is 0, draw a single straight line segment.
  if (level == 0) {
    // The recursion terminates, and the Turtle draws the final line segment.
    turtle->drawLine(length);
  }
  else {
    // Recursive Step: Replace the segment with four smaller segments.
    double newLength = length / 3.0;

    // 1. Draw first segment (no turn)
    drawKoch(level - 1, newLength);

    // 2. Turn 60 degrees left and draw second segment
    turtle->turn(60.0);
    drawKoch(level - 1, newLength);

    // 3. Turn 120 degrees right (or -120 degrees) and draw third segment
    turtle->turn(-120.0);
    drawKoch(level - 1, newLength);

    // 4. Turn 60 degrees left and draw fourth segment (return to original direction)
    turtle->turn(60.0);
    drawKoch(level - 1, newLength);
  }
}

// Main public method to generate the curve.
void Koch::generateCurve(int level, double x1, double y1, double x2, double y2) {
  // 1. Calculate initial angle (in degrees) of the level 0 segment using atan2
  double dx = x2 - x1;
  double dy = y2 - y1;
  // atan2 calculates the angle in radians between the positive x-axis and the point (dx, dy)
  double initialAngleRad = std::atan2(dy, dx);
  double initialAngleDeg = initialAngleRad * 180.0 / M_PI;

  // 2. Calculate initial length (d) using Euclidean distance: d = sqrt((x2-x1)^2 + (y2-y1)^2)
  double initialLength = std::sqrt(dx * dx + dy * dy);

  // 3. Initialize the TurtleHelper object.
  // The constructor outputs the Postscript header and 'moveto' command.
  // Clean up any existing turtle object before creating a new one.
  if (turtle) delete turtle;
  turtle = new TurtleHelper(x1, y1, initialAngleDeg);

  try {
    // 4. Start the recursion with the desired level and the total length of the base segment.
    drawKoch(level, initialLength);
    // 5. Output final Postscript commands to render the path.  
    turtle->outputStroke();
    turtle->outputShowpage();
  }
  catch (...) {
    // 6. Exception Safetey: If recursion fails, ensure the dynamically allocated memory is cleaned up.
    delete turtle;
    turtle = nullptr;
    throw; // Re-throw the exception to notify the caller (driver.cpp)  
  }

  // 7. Clean up the dynamically allocated turtle object on successful completion.
  // This ensures the memory is freed after the function completes.
  delete turtle;
  turtle = nullptr;
}