#include <iostream>
#include <string>

using namespace std;

int main() {

    string input = "", up_input, low_input;

    cout << "Hey bro, give me an entire sentence: ";
    getline(cin, input);

    up_input = input;
    low_input = input;
    
    for (int i = 0; i < input.length(); i++) {
        if (isupper(input[i])) {
            cout << input[i] << " is an uppercase letter" << endl;
            low_input[i] = tolower(input[i]);
        } else if (islower(input[i])) {
            cout << input[i] << " is an lowercase letter" << endl;
            up_input[i] = toupper(input[i]);
        }
        // cout << input[i] << endl;
    }

    cout << "Uppercase Input: " << up_input << endl;
    cout << "Lowercase Input: " << low_input << endl;

    int upper_char_1 = toupper(input[0]);
    cout << upper_char_1 << " is " << (char)upper_char_1<< endl;

    return 0;
}