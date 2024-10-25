#include <iostream>

using namespace std;

int main() {
    string fname, lname;

    cout << "Enter your first & last name: ";
    cin >> fname;
    cin >> lname;

    // Strings can be concatenated with a "+" as long as they are C++ strings and not C strings
    // Here we have the space " " which is a C string, but since fname & lname are C++ strings it still works
    cout << "NAME: " + fname + " " + lname << endl;

    if (fname == lname) {
        cout << "Interesting... first & last name are the same." << endl;
    } else if ((fname == "Max") || (fname == "Maxwell")) {
        cout << "That's my name too!" << endl;
    }

    // THIS IS NOT ALLOWED
    // string stringy = "name" + "me" + "hi";
    // THIS IS ALLOWED (on some operating systems you may need to put the C++ string first, which happened to me)
    string stringy = fname + "name" + "me" + "hi";

    string fullname;
    fullname += fname;
    cout << fullname << endl;
    fullname += " " + lname; // here there is no error putting the C style string 1st for some reason
    cout << fullname << endl;

    return 0;
}