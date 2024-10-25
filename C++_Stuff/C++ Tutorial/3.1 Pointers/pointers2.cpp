#include <iostream>
#include <cstdlib>

// Pointers!

using namespace std;

int main() {
    int *age_ptr = (int*)malloc(sizeof(int)); // cast the allocated memory (void default) to integer pointer
    *age_ptr = 30;
    cout << "Location: " << age_ptr << endl;
    cout << "Value: " << *age_ptr << endl;
    free(age_ptr); // every time your use malloc you ust free the memory later because it isn't handled by the OS and must be done manually
}