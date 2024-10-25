#include <iostream>
#include <vector>

using namespace std;

// technically a pointer input isn't needed to merely print the values, but if we wanted to modify them it would be!
void print_vector(vector<int> *vi) {
    for (int i = 0; i < vi->size(); i++) {
        cout << "Element at " << i << " is " << vi->at(i) << endl;
    }
}

int main() {
    // create integer vector with an initial size of 3
    vector<int> numbers(3);
    // assign values to vector
    numbers[0] = 100;
    numbers[1] = 1000;
    numbers[2] = 10000;
    cout << "Vector size: " << numbers.size() << endl;
    // print 1st elements
    cout << numbers[0] << endl;
    // append a 5 to the end of the vector
    numbers.push_back(5);
    cout << numbers[3] << endl;
    // Size of vector
    cout << "Vector size: " << numbers.size() << endl;
    // Remove last element
    numbers.pop_back();
    cout << "Vector size: " << numbers.size() << endl;
    // Print The Vector (function)
    print_vector(&numbers); // pass place in memory of vector to function

    return 0;
}