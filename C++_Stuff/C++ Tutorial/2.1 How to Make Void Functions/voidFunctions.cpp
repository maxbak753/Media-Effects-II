#include <iostream>

using namespace std;

// FUNCTION DECLARATIONS
void print_opening();
void ask_question();

// MAIN FUNCTION

int main() {
    print_opening();
    ask_question();
    return 0;
}

// FUNCTION DEFINITIONS

void print_opening() {
    cout << "Hello, welcome to my game!" << endl;
}

void ask_question() {
    string answer = "";
    cout << "Enter your name: ";
    cin >> answer;

    cout << "You entered " << answer;
}