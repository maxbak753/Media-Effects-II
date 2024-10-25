#include <iostream>
#include <cmath>

using namespace std;

// FUNCTION OVERLOADING

double add(double a, double b);
double add(double, double, double); //<-- parameter names are unnecessary in the declaration

int main() {
    cout << add(5.5, 4.3) << endl;
    cout << add(1.1, 5.5, 4.3) << endl;

    return 0;
}

// Two functions definitions for varying parameter amounts
double add(double a, double b) {
    return a + b;
}

double add(double a, double b, double c) {
    return a + b + c;
}