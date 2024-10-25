#include <iostream> // pre-built header file <>
#include "main.hpp" // our home-made header file ""
// ^ heade file contains "announce()" function declaration
using namespace std;
 
 //#define MAX 1000 // preprocessor directive (replaces MAX with 1000)

 int main() {

    cout << MAX << endl;
    announce("Hello, World");
    cout << "__FILE__: " <<  __FILE__ << endl; // __FILE__ is a pre-defined macro name

    return 0;
 }

 void announce(string message) {
    cout << "Announce: " << message << endl;
 }