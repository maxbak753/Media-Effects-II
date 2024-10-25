#include <iostream>

int main() {

    // Single line comment

    /*
    multi
    line 
    comment
    */

    int integer = 12;
    char character = 'C';
    bool boolean = 1; // false or 0, true or 1
    double decimal = 12.14;

    std::cout << integer << std::endl;
    std::cout << character << std::endl;
    std::cout << boolean << std::endl;
    std::cout << decimal << std::endl;

    // Declarations
    long int long_integer;

    std::cout << long_integer << std::endl;

    long_integer = 12000000;

    std::cout << long_integer << std::endl;

    std::cout << "I'm an int of size: " << sizeof(int) << std::endl;

}