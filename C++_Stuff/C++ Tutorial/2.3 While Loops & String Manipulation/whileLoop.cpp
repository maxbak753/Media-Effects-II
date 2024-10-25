#include <iostream>
#include <string>

using namespace std;

int main() {

    // Count Controlled
    cout << "\nCOUNT CONTROLLED" << endl;
    int x = 0;
    while (x < 10) {
        cout << x << endl;
        x++;
    }

    // Sentinel Controlled
    cout << "\n\nSENTINEL CONTROLLED" << endl;
    string input = "";
    while (input != "exit") {
        cout << " - Enter 'exit' to exit: ";
        cin >> input;
        cout << "End of the loop";
    }

    // Flag Controlled
    cout << "\n\nFLAG CONTROLLED" << endl;
    input = "";
    bool run = true;
    while (run) {
        cout << " - Enter 'exit' to exit: ";
        cin >> input;
        if (input == "exit") {
            run = false;
        }
        cout << "End of the loop" << endl;
    }

    // Forever Controlled
    cout << "\n\nFOREVER CONTROLLED" << endl;
    input = "";
    while (true) {
        cout << " - Enter 'exit' to exit: ";
        cin >> input;
        if (input == "exit") {
            break;
        }
        cout << "End of the loop" << endl;
    }

    return 0;
}