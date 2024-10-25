#include <iostream>

// C Arrays

using namespace std;

void print_array(string [], int); // <-- must put [] for array

int main() {
    double array[3] = {1.1, 2.2, 3.3};
    cout << array[5] << endl; // <- this will show  random number and may produce warnings (outside of the length of the array!)
    
    // Length of Array
    cout << "-------------------" << endl;
    string str_ar[3] = {"Hey", "Hi", "Hello"};
    int ar_bytes = sizeof(str_ar);
    int ar_elem_len = ar_bytes / sizeof(str_ar[0]);
    cout << "# of Bytes in Array: " << ar_bytes << endl;
    cout << "# of Array Elements: " << ar_elem_len << endl;
    
    // Print Arrays: functions pass arrays by reference! (not value)
    cout << "Print Array (location where 1st element of array is stored): " << str_ar << endl;
    cout << "Print Array (pointer to 1st element using *): " << *str_ar << endl;
    cout << "Print each array element: " << endl;
    print_array(str_ar, ar_elem_len);

    // Multi-Dimensional Arrays
    int multi_ar[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
    cout << "\n[Multi-Dimensional Arrays]" << endl;
    cout << multi_ar[0][1] << endl;
    cout << multi_ar[2][3] << endl;

    return 0;
}

void print_array(string array[], int length) {
    for (int i = 0; i < length; i++) {
        cout << array[i] << endl;
    }
}