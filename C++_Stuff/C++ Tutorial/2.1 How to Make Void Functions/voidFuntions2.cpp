#include <iostream>

// [FUCNTION SCOPE & GLOBAL VARIABLES] n stuff like that

using namespace std;

void f1();
void f2();
void f3();

int x = 3;

int main() {
    int x = 12;
    cout << "main (global): " << ::x << endl;
    cout << "main (local): " << x << endl;
    f1();
    f2();
    f3();
    return 0;
}

void f1() {
    int x = 10;
    cout << "f1 (local): " << x << endl;
}

void f2() {
    cout << "f2 (global): " << x << endl;
}

void f3() {
    int x = 7;
    cout << "f3 (local): " << x << endl;
    cout << "f3 (global): " << ::x << endl;
}