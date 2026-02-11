// UniversityHousingLottery.cpp : This file contains the 'main' function. Program execution begins and ends there.
// University Housing Lottery

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Struct to store student data
struct Student {
    string name;
    int points;
};

// Helper function to validate yes/no input
char getValidYesNoInput(const string& prompt) {
    string input;
    char choice;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) {
            choice = toupper(input[0]); // Convert to uppercase for easier comparison
            if (choice == 'Y' || choice == 'N') {
                return choice;
            }
        }
        cout << "Invalid input. Please enter Y for Yes or N for No.\n\n";
    }
}

// Helper function to validate numeric input within range
int getValidNumberInput(const string& prompt, int minVal, int maxVal) {
    string input;
    int number;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            number = stoi(input);
            if (number >= minVal && number <= maxVal) {
                return number;
            }
            else {
                cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n\n";
            }
        }
        catch (const exception& e) {
            cout << "Invalid input. Please enter a valid number.\n\n";
        }
    }
}

// Helper function to validate boolean input (1/0)
bool getValidBooleanInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input == "1" || input == "0") {
            return (input == "1");
        }
        // accept yes/no for boolean questions
        if (!input.empty()) {
            char firstChar = toupper(input[0]);
            if (firstChar == 'Y') return true;
            if (firstChar == 'N') return false;
        }
        cout << "Invalid input. Please enter 1 for Yes, 0 for No, Y for Yes, or N for No.\n\n";
    }
}

// Safe function to get age with validation
int getValidAge(const string& name) {
	string prompt = "How old is " + name + "?\n(0 - 150)\n";
	int age = getValidNumberInput(prompt, -1, 150); // allow -1 for invalid age
    if (age == -1) {
        cout << "No points will be awarded for age due to invalid input.\n\n";
	}
    return age;
}

// Function prototypes
void classYearPoints(string classYear, int* points);
void agePoints(int age, int* points);
void onProbationPoints(bool onProbation, int* points);
void onSuspensionPoints(bool onSuspension, int* points);
void onDisciplinaryProbationPoints(bool onDisciplinaryProbation, int* points);
void studentTeacherPoints(bool isStudentTeacher, int* points);
// Function implementations are below main()

int main() {
    char choice = 'Y';
    string name;
    string classYear;
    string input;
    int age;
    bool onProbation;
    bool onSuspension;
    bool onDisciplinaryProbation;
    bool isStudentTeacher;
    int points;
    vector<Student> students; // Vector to store multiple students

    cout << "Program 0: A University Housing Lottery\n";
    cout << "**************************************************\n";
    cout << "Welcome to the University Housing Lottery Program!\n\n";

    do {
        // reset points for each user
        points = 0;

        cout << "This program will help a student determine how many points they have for the housing lottery.\n";
        cout << "The more points a student has, the better their chances of getting their preferred housing option.\n\n";

        // Get user information
        while (true) {
            cout << "What is the student's name?\n";
            getline(cin, name); // allows for spaces in name input
            if (!name.empty()) {
                break; // exit loop if name is not empty
            }
            cout << "Name cannot be empty. Please enter a valid name.\n\n";
        }

        cout << "What class year is " << name << "? (Enter 'Freshman', 'Sophomore', 'Junior', or 'Senior')\n";
        getline(cin, classYear);
        classYearPoints(classYear, &points);

        age = getValidAge(name);
        if (age != -1) // if age is valid
            agePoints(age, &points);
       
		onProbation = getValidBooleanInput("Is " + name + " on Academic Probation ? (1 for Yes, 0 for No)\n");
        onProbationPoints(onProbation, &points);

		onSuspension = getValidBooleanInput("Is " + name + " on Possible Academic Suspension ? (1 for Yes, 0 for No)\n");
        onSuspensionPoints(onSuspension, &points);

		onDisciplinaryProbation = getValidBooleanInput("Has " + name + 
                " been on Disciplinary Probation at Any Point during the Academic Year ? (1 for Yes, 0 for No)\n");
        onDisciplinaryProbationPoints(onDisciplinaryProbation, &points);

		isStudentTeacher = getValidBooleanInput("Is " + name + " a Student Teacher ? (1 for Yes, 0 for No)\n");
		studentTeacherPoints(isStudentTeacher, &points);

        cout << name << " has " << points << " housing points.\n\n";

        // Store student data in struct
        Student student;
        student.name = name;
        student.points = points;
        students.push_back(student);

		choice = getValidYesNoInput("Would you like to enter another student? (Y for Yes, N for No)\n");

    } while (choice == 'Y' || choice == 'y');
    if (students.size() > 0) {
        // Sort students by points in descending order
        for (int i = 0; i < students.size() - 1; i++) {
            for (int j = i + 1; j < students.size(); j++) {
                if (students[i].points < students[j].points) {
                    Student temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
    }

	// Display sorted student list
	cout << "\nHousing Lottery Results:\n";
	cout << "**************************\n";
    cout << "Rank Name         Points  \n";
	cout << "--------------------------\n";
    for (int i = 0; i < students.size(); i++) {
		cout << i + 1 << ". " << students[i].name << " has " << students[i].points << " point(s)\n";
	}          
    cout << "********************************************************************\n\n";
    cout << "Thank you for using the University Housing Lottery Program. Goodbye!\n";
    return 0;
}

void classYearPoints(string classYear, int* points) {
    string lowerClassYear = "";
    for (char c : classYear) {
        lowerClassYear += tolower(c);
	}

    if (lowerClassYear == "freshman") {
        cout << "The student earned 1 point because they are a " << classYear << ".\n\n";
        (*points) += 1;
    }
    else if (lowerClassYear == "sophomore") {
        cout << "The student earned 2 points because they are a " << classYear << ".\n\n";
        (*points) += 2;
    }
    else if (lowerClassYear == "junior") {
        cout << "The student earned 3 points because they are a " << classYear << ".\n\n";
        (*points) += 3;
    }
    else if (lowerClassYear == "senior") {
        cout << "The student earned 4 points because they are a " << classYear << ".\n\n";
        (*points) += 4;
    }
    else
        cout << "I didn't recognize the option: " << classYear << ". No points awarded for class year.\n\n";
}

void agePoints(int age, int* points) {
    if (age == -1) {
        // Invalid age, no points awarded
        return;
	}
    cout << "You entered: '" << age << "'\n";
    if (age >= 23 && age < 50) {
        cout << "The student earned 1 point because they are " << age << " years old.\n\n";
		(*points) += 1;
    } else if (age >= 50 && age <= 150) {
		char accommodationChoice = getValidYesNoInput("Does the student require reasonable accomodations? (Y for Yes, N for No)\n");
        if (accommodationChoice == 'Y') {
            cout << "The student earned 2 points because they are " << age << " years old and require reasonable accommodations.\n\n";
            (*points) += 2;
        } else {
            cout << "The student earned 1 point because they are " << age << " years old.\n\n";
            (*points) += 1;
        } 
	} else if (age < 23 && age >= 0) {
		cout << "The student did not earn any points because they are only " << age << " years old.\n\n";
    } else {
        cout << "Invalid age of " << age << " entered. No points awarded for age.\n\n";
    }
}

void onProbationPoints(bool onProbation, int* points) {
    if (onProbation) {
        cout << "You indicated that the student is on probation.\n";
		cout << "The student lost 1 point because they are on probation.\n\n";
        (*points) -= 1;
    }
    else {
        cout << "You indicated that the student is not on probation.\n";
        cout << "The student did not lose any points because they are not on probation.\n\n";
    }
}

void onSuspensionPoints(bool onSuspension, int* points) {
    if (onSuspension) {
        cout << "You indicated that the student is on Possible Academic Suspension.\n";
        cout << "The student lost 2 points because they are on Possible Academic Suspension.\n\n";
        (*points) -= 2;
    }
    else {
        cout << "You indicated that the student is not on Possible Academic Suspension.\n";
        cout << "The student did not lose any points because they are not on Possible Academic Suspension.\n\n";
    }
}

void onDisciplinaryProbationPoints(bool onDisciplinaryProbation, int* points) {
    if (onDisciplinaryProbation) {
        cout << "You indicated that the student has been on Disciplinary Probation at Any Point during the Academic Year.\n";
        cout << "The student lost 3 points because of that.\n\n";
        (*points) -= 3;
    }
    else {
        cout << "You indicated that the student has not been on Disciplinary Probation at Any Point during the Academic Year.\n";
        cout << "The student did not lose any points because of that.\n\n";
    }
}

void studentTeacherPoints(bool isStudentTeacher, int* points) {
    if (isStudentTeacher) {
        cout << "You indicated that the student is a Student Teacher.\n";
        cout << "The student earned 2 points because they are a Student Teacher.\n\n";
        (*points) += 2;
    }
    else {
        cout << "You indicated that the student is not a Student Teacher.\n";
        cout << "The student did not earn any points because they are not a Student Teacher.\n\n";
    }
}