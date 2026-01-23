### **Example Output**
![Example Output](https://github.com/pitekopaga/cpp/blob/main/3_Koch_Fractals/output.pdf)

Compilation Instructions
The program requires a C++ compiler (such as g++) and the C++ standard library.

Step 1: Compile the Source Files
Use this command to compile all source files and link them into a single excecutable named koch:

g++ -std=c++11 -o koch driver.cpp Koch.cpp -lm

•	-std=c++11: Ensures compatibility with modern C++ features.
•	-o koch: Specifies the output executable name as koch.
•	-lm: Links the math library (required for std::sqrt and std::atan2).

Step 2: Verify Compilation
If compilation is successful, an executable file named koch will be created in the current directory.

Execution Instructions
The program takes five command-line arguments: the starting point $(x_1, y_1)$, the ending point $(x_2, y_2)$, and the curve level.

Usage Syntax (add “.exe” after “koch” if in Windows)
./koch x1 y1 x2 y2 level
Example Usage (add “.exe” after “koch” if in Windows)
./koch 25 400 575 400 5

Example Execution (Level 5)
To generate the Level 4 Koch curve from $(25, 400)$ to $(575, 400)$ and save the output to a Postscript file (if using Windows, replace “./koch” with “koch.exe”):

./koch 25 400 575 400 5 > output.ps

On Windows, navigate to the .exe directory, and enter the command prompt: 
koch.exe 25 400 575 400 5 | gswin64c -dNOPAUSE -dBATCH -sDEVICE=pdfwrite -sOutputFile=output.pdf -
