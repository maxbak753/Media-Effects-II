#include <iostream>

using namespace std;

void increment(int x);
void print(int a, double b, string c);

int main() {
    // int x = 10;
    // increment(x);
    // cout << x << endl;

    print(3, 3.14, "Hello"); // <- arguments


    return 0;
}

void print(int a, double b, string c) { // <- parameters
    cout << "int: " << a << endl;
    cout << "double: " << b << endl;
    cout << "string: " << c << endl;
}

void increment(int x) {
    x++;
}