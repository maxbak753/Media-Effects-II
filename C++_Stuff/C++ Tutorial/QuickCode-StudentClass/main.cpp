#include <iostream>
#include <map>
#include <vector>
#include "student.hpp" // file must have same name as class!

using namespace std;

int main() {
    Student s1;
    Student s2("Jayn Dough", 69420);

    // [#1] -----
    s1.print_number_of_students();

    s1.identify();
    s2.identify();

    s1.calculate_GPA("ABAACDF");
    s1.identify();

    // [#2] -----
    // Get
    cout << "[Get S1] Name: " << s1.getName();
    cout << ", ID: " << s1.getID();
    cout << ", GPA: " << s1.getGPA() << endl;
    // Set
    s1.setName("Julius Caesar");
    s1.setID(6666666);
    s1.setGPA();
    s1.set_class_schedule();
    s1.setPopularity(9);
    s1.setDorm("Imperial Place (Rome)");
    // Check Set
    cout << "[Get S1] Name: " << s1.getName();
    cout << ", ID: " << s1.getID();
    cout << ", GPA: " << s1.getGPA();
    cout << ", Popularity: " << s1.getPopularity();
    cout << ", Dorm: " << s1.getDorm() << endl;
    s1.print_class_schedule();

    // -------------------------------------------------
    // [#3] -----
    s1.set_class_grades();
    s1.set_assignment_grades();
    cout << "PRINTING" << endl;
    s1.print_class_grades();
    s1.print_class_assignment_grades();

    return 0;
}