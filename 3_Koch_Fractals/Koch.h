// Koch.h
// Scott Elliott
// 
// Description:
// Defines the Koch class, which encapsulates the recursive algorithm for generating the Koch curve.
// It includes a private nested class, TurtleHelper, to manage the drawing state and Postscript output.
//

#ifndef KOCH_H
#define KOCH_H

#include <iostream>
#include <cmath>
#include <iomanip>

// Define PI for angle calculations
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Koch {
private:
  // --- Private Nested Class: TurtleHelper ---
  // Description: Manages the virtual drawing pen's state (position and angle)
  // and translates drawing actions into Postscript commands printed to standard output.
  class TurtleHelper {
  private:
    double currentX;      // Current X-coordinate of the turtle.
    double currentY;      // Current Y-coordinate of the turtle.
    double currentAngle;  // Current direction (angle in degrees).

    // Helper function to convert degrees to radians
    double degToRad(double degrees) const;

  public:
    // Constructor: Initializes position and angle. Outputs Postscript header and 'moveto'.
    TurtleHelper(double x, double y, double angle);

    // Changes the currentAngle by the specified number of degrees.
    void turn(double degrees);

    // Calculates displacement, updates position, and outputs 'rlineto'.
    void drawLine(double length);

    // Outputs the 'stroke' Postscript command.
    void outputStroke();

    // Outputs the 'showpage' Postscript command.
    void outputShowpage();
  };

  // --- Koch Class Members ---
  TurtleHelper* turtle; // Pointer to the TurtleHelper object.
  // Prevent copying of the Koch object   
  Koch(const Koch&) = delete;
  Koch& operator=(const Koch&) = delete;

  // Recursive Helper Function.
  // Implements the core Koch curve logic.
  void drawKoch(int level, double length);

public:
  // Destructor for manual cleanup   
  ~Koch();

  // Constructor: Initializes the Koch object.
  Koch();

  // Main public method to generate the curve.
  // x1, y1: Start point of the level 0 segment.
  // x2, y2: End point of the level 0 segment.
  // level: The desired level of the Koch curve iteration.
  void generateCurve(int level, double x1, double y1, double x2, double y2);
};

#endif // KOCH_H