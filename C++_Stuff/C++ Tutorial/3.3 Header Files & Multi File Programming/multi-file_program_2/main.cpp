#include <iostream>
#include "myclass.hpp"

using namespace std;

int main() {
    Rectangle rect1 (3,5);
    Rectangle rect2 (10.5, 15.1);

    cout << "Rect1 Area: " << rect1.area() << endl;
    cout << "Rect2 Area: " << rect2.area() << endl;

    cout << "Rect1 Perimeter: " << rect1.perimeter() << endl;
    cout << "Rect2 Perimeter: " << rect2.perimeter() << endl;

    return 0;
}

/* TO RUN PROGRAM:
  > g++ main.cpp myclass.cpp -o program
  > program
*/