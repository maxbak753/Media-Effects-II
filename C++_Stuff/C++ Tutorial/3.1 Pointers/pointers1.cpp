#include <iostream>

// Pointers!

using namespace std;

void update(int *, int);

int main() {
    int points = 24; // variable
    int *points_ptr = &points; // pointer: point to the address of this variable
    // value of variable
    cout << "My points:  " << points << endl;
    // Get memory location (& - address of operator) from original variable
    cout << "My points is stored here in memory: " << &points << endl;
    // Point to the memory location in a pointer
    cout << "My points_ptr is: " << points_ptr << endl;
    // De-reference (* de-referencing operator) the pointer to get the value at the memory location
    cout << "My points from the ptr is: " << *points_ptr << endl;

    int points_to_add = 5;
    update(points_ptr, points_to_add);
    cout << "Previous points + "<< points_to_add << " = " << points << " (stored in the original variable with a pointer & function)"<< endl;
}

void update(int *points, int pts) {
    *points += pts; // de-reference variable (*) to modify value
}