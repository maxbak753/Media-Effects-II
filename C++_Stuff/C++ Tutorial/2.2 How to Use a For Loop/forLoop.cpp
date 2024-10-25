#include <iostream>
#include <cmath>

using namespace std;

void sum();
void nestedloops();
void userinput();

int main() {
//     for (int i = 100; i >= 0; i--) {
//         cout << "Number: " << i << "\t";
//     }

    // sum();

    // nestedloops();

    userinput();

    return 0;
}

void userinput() {
    int limit = 0;
    cout << "How many times do you want the loop to run?: ";
    cin >> limit;

    int temp = 0;
    for (int i = 1; i <= limit; i++) {
        cout << "Enter a number: ";
        cin >> temp;
        cout << "You entered: " << temp << endl;

    }
}


void nestedloops() {
    for (int x = 1; x <= 10; x++) {
        for (int y = 1; y <= 10; y++) {
            cout << "X = " << x << ", Y = " << y << ", X^Y = " << pow(x,y) << endl;
        }
    }
}

void sum() {
    int sum = 0;

    for (int i = 1; i <=5; i++) {
        sum += i;
    }

    cout << "The sum is: " << sum << endl;
}