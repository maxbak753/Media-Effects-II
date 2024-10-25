#include <iostream>

// C Arrays

using namespace std;

// void print_array(string [], int); // <-- must put [] for array

int main() {
    int ints[10], biggest;

    for (int i=0; i<10; i++) {
        cout << "Enter #" << i+1 << ": ";
        cin >> ints[i];
        
        if (i == 0) {
            biggest = ints[i];
        } else {
            if (ints[i] > biggest) {
            biggest = ints[i];
            }
        } 
    }

    cout << "Largest number is " << biggest << endl;

    return 0;
}