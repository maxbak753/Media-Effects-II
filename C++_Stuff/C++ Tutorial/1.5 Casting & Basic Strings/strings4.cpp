#include <iostream>

using namespace std;

int main() {
    string a; // default empty string
    string b = "hello"; // copy initialization (turns string literal C style into C++ style)
    string c("dude");   // direct initialization
    string d = b;       // copy initialization
    string e(c);        // direct initialization
    string f(10, 'a');  // ten "a" characters

    // you can finish lines on other lines if you want
    cout << a << " " << b << " " << c << " " << 
    d << " " << e << " " << f;

}