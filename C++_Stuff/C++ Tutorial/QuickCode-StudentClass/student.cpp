#include <iostream> // print IO stream
#include <string> // strings
#include <map> // maps
#include <vector> // vectors
#include <fstream> // file IO stream
#include "student.hpp" // file must have same name as class!

using namespace std;

int Student::number_of_students = 0;

// Constructor
Student::Student () {
    cout << "You've made a student" << endl; // print
    number_of_students++; // add student

    cout << "[Q] Choose a student data option:\n  1. Load values from 'Student_Data.txt' file\n  -1. Use default values\n[A]: ";
    int student_data_option;
    cin >> student_data_option;
    cout << '\n';

    if (student_data_option >=0) {
        // Load data from Student_Data.txt file
        load_data();
    } else {
        // Defaults:
        name = "Billy Smith"; // name
        id = 12345; // ID
        gpa = 0.0; // GPA
        popularity = 5; // Popularity Score
        dorm = "Bogart Hall"; // Dormitory
    }
}
// Overloaded Constructor
Student::Student (string new_name, int new_id) {
    cout << "You've made a student" << endl; // print
    number_of_students++; // add student
    // Defaults:
    name = new_name; // name
    id = new_id; // ID
    gpa = 0.0; // GPA
}

void Student::print_number_of_students() {
    cout << "There are this many students: " << number_of_students << endl;
}

void Student::identify() {
    cout << "Name: " << name << ", ID: " << id << ", GPA: " << gpa;
    cout << ", \nPopularity Score: " << popularity << ", Dormitory: " << dorm << endl;
}

void Student::calculate_GPA(char array[]) {
    // int ar_len = sizeof(array) / sizeof(array[0]);
    int ar_len = strlen(array);
    double current_num = 0;
    double sum = 0;

    for (int i = 0; i < ar_len; i++) {
        if (array[i] == 'A') {
            // cout << "array[" << i << "] = A = 4" << endl;
            current_num = 4;
        } else if (array[i] == 'B') {
            // cout << "array[" << i << "] = B = 3" << endl;
            current_num = 3;
        } else if (array[i] == 'C') {
            // cout << "array[" << i << "] = C = 2" << endl;
            current_num = 2;
        } else if (array[i] == 'D') {
            // cout << "array[" << i << "] = D = 1" << endl;
            current_num = 1;
        } else if (array[i] == 'F') {
            // cout << "array[" << i << "] = F = 0" << endl;
            current_num = 0;
        }

        // Add grade to sum
        sum += current_num;
    }

    // Set GPA from grade point average
    gpa = sum / ar_len;

    // cout << "Array Length: " << ar_len << endl;
}

// Setters & Getters

void Student::setName(std::string new_name) {
    name = new_name;
}
string Student::getName() {
    return name;
}

void Student::setID(int new_id) {
    id = new_id;
}
int Student::getID() {
    return id;
}

void Student::setGPA() {
    char grades[8];
    cout << "\n[What Are Your Letter Grades In 8 Different Classes?]\n(All caps please. Ex: B)" << endl;
    for (int i = 0; i < 8; i++) {
        cout << "Grade #" << i+1 << ": ";
        std::cin >> grades[i];
    }
    cout << "Calculating GPA... ";
    calculate_GPA(grades);
    cout << "Done." << endl;
}
double Student::getGPA() {
    return gpa;
}

void Student::set_class_schedule() {
    cout << "\n[Choose Your Class Schedule] \n(NO SPACES! Space --> next class)" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "Class #" << i+1 << ": ";
        std::cin >> class_schedule[i];
    }
    cout << "Done." << endl;
}
void Student::print_class_schedule() {
    cout << "\n[PRINTING CLASS SCHEDULE]" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "Class #" << i+1 << ": ";
        cout << class_schedule[i] << endl;
    }
    cout << "Done." << endl;
}

void Student::setPopularity(int new_popularity) {
    popularity = new_popularity;
}
int Student::getPopularity() {
    return popularity;
}

void Student::setDorm(std::string new_dorm) {
    dorm = new_dorm;
}
std::string Student::getDorm() {
    return dorm;
}

void Student::set_class_grades() {
    cout << "\nWhat are your grades for..." << endl;
    for (int i = 0; i < 6; i++) {
        cout << class_schedule[i] << "?: ";
        cin >> class_grades[class_schedule[i]];
    }
    cout << "Done." << endl;
}
void Student::print_class_grades() {
    cout << "\nClass Grades\n";
    for (auto const &pair : class_grades) {
        cout << pair.first << ": grade = " << pair.second << endl;
    }
    cout << "Done.\n";
}

void Student::set_assignment_grades() {
    cout << "\nSet Your Assignment Grades\n(enter a negative number to end)\n";
    double new_grade = 0;
    int i = 0;
    while (new_grade >= 0.0) {
        cout << "Grade #" << i << ": ";
        cin >> new_grade;
        assignment_grades.push_back(new_grade);
        i++;
    }
    assignment_grades.pop_back();
    cout << "Done.\n";
}
void Student::print_class_assignment_grades() {
    cout << "\nPrinting Class assignment grades...\n";
    cout << assignment_grades[0];
    for (int i = 1; i < assignment_grades.size(); i++) {
        cout << ", " << assignment_grades[i];
    }
    cout << "\nDone.\n";
}

// FILE IO ----------------------------------------------------

// Destructor
Student::~Student() {
    cout << "\nCLOSING PROGRAM\nSaving Data to file...";
    save_data();
    cout << "Done." << endl;

}

void Student::save_data() {
    // Create file object from output file stream class
    ofstream data_file;
    // Open the file (creates it if nonexistent)
    data_file.open("Student_Data.txt");
    // check if it actually opened
    if (data_file.is_open()) {
        // Write to the file (will overwrite EVERYTHING in the previous file!)
        //must put endl or \n for newline
        data_file << name << endl;  // LINE 1
        data_file << id << '\n';    // LINE 2
        data_file << gpa << endl;   // LINE 3

        // Space Separated Class Schedule: LINE 4
        for (int i = 0; i < 6; i++) {
            data_file << class_schedule[i] << " ";
        }

    } else {
        cout << "The file didn't open" << endl;
    }
    // Close the file
    data_file.close();
}

void Student::load_data() {
    ifstream data_file;
    data_file.open("Student_Data.txt");

    string new_id;
    string new_gpa;

    if (data_file.is_open()) {
        for (int i = 0; i < 4; i++) {
            switch (i) {
                case 0:
                    getline(data_file, name);
                    cout << "Got name" << endl;
                    break;
                case 1:
                    getline(data_file, new_id);
                    id = stoi(new_id);
                    cout << "Got id" << endl;
                    break;
                case 2:
                    getline(data_file, new_gpa);
                    gpa = stod(new_gpa);
                    cout << "Got gpa" << endl;
                    break;
                case 3:
                    // read each class name into the schedule (space serparated)
                    for (int s = 0; s < 6; s++) {
                        data_file >> class_schedule[s];
                    }
                    cout << "Got class_schedule" << endl;
                    break;
                default:
                    cout << "Wrong index for switch-case in Student::load_data()\ni = " << i << endl;
                    break;
                    
            }

        }
    } else {
        cout << "This file didn't open" << endl;
    }

    data_file.close();
}