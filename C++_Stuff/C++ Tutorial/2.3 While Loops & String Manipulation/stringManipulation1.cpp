#include <iostream>
#include <string>

using namespace std;

int main() {

    string input = "";

    cout << "Hey bro, give me an entire sentence: ";
    getline(cin, input);
    cout << input << endl;

    if (input.length() > 10) {
        cout << "11th character: " << input[10] << endl;
    } else {
        cout << "Oops, the string is only " << input.length() << " characters!" << endl;
    }

    cout << "Index of 'am': " << input.find("am") << endl;
    
    input[0] = '$';
    cout << "Make 1st character '$': " << input << endl;

    return 0;
}