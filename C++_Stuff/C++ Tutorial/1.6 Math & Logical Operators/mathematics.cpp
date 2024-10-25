#include <iostream>
#include <cmath>

using namespace std; // no need to say std:: now

int main() {
    // -------------------------------------
    // built-in (standard library std::)
    cout << "built in" << endl;
    int max_int = max(5, 3);
    double min_doub = min(3.5, 6.7);
    cout << max_int << endl;
    cout << min_doub << endl;
    cout << min(100, 200) << endl;
    // cout << min(3.4, 2) << endl; <-- error (mixed types)

    // ---------------------------
    // cmath
    cout << "\ncmath" << endl;
    cout << pow(3, 2) << endl;
    cout << round(3.14) << endl;
    cout << sqrt(16) << endl;

    // ----------------------------------------
    // Logical Operators: and, or, not equal
    int a, b, c;
    cout << "enter 3 numbers: " << endl;
    cin >> a >> b >> c; // separate answers with spaces or enter each

    if (a > 10 && a < 20) {
        cout << "a is between 10 & 20" << endl;
    }

    if (b > 10 || b < -10) {
        cout << "b is greater than 10 or below -10" << endl;
    }

    if (c != 10) {
        cout << "c is not 10" << endl;
    }

    return 0;
}