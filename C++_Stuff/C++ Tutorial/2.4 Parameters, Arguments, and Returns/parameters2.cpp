#include <iostream>
#include <cmath>

using namespace std;

bool check_discrim(double a, double b, double c);
double discrim(double a, double b, double c);

int main() {
    double a, b, c;

    cout << "Enter 3 doubles: " << endl;
    cin >> a >> b >> c;

    if (check_discrim(a, b, c)) {
        cout << "Discriminat = " << discrim(a,b,c) << endl;
    } else {
        cout << "The numbers you gave don't work!" << endl;
    }

    return 0;
}

bool check_discrim(double a, double b, double c) {
    double discrim = pow(b, 2) - (4 * a * c);

    if (discrim >= 0) {
        return true;
    } else {
        return false;
    }
}

double discrim(double a, double b, double c) {
    return pow(b,2) - (4 * a * c);
}