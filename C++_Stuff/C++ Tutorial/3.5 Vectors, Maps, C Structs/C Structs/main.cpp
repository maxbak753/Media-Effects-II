#include <iostream>

using namespace std;

int main() {
    // Structure Declaration
    struct Student{
        string name;
        double gpa;
    };

    // Initialize structures 
    struct Student s1;
    struct Student s2;
    // Set variables
    s1.name = "Max";
    s2.name = "Emma";

    cout << s1.name << endl;
    cout << s2.name << endl;

    return 0;
}