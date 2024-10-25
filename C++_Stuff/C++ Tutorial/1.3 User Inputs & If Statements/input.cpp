#include <iostream>

int main() {

    std::cout << "Enter a number: ";

    int x = 0;

    if (std::cin >> x) {
        std::cout << "You entered " << x << " successfully" << std::endl;
    } else {
        // if it wasn't an int, ask again
        std::cin.clear(); // resets error flags (doesn't clear the buffer)
        std::cin.ignore(1000, '\n'); // stop after 1000 characters or newline

        std::cout << "Enter a number (INTEGER!): ";
        int y = 0;
        std::cin >> y;
        std::cout << "You entered " << y << " successfully (hopefully int this time)" << std::endl;
    }
    
    if (x > 10) {
        std::cout << "x is greater than 10" << std::endl;
    } else if (x == 10) {
        std::cout << "x equals 10" << std::endl;
    } else {
        std::cout << "x is less than 10" << std::endl;
    }

    /*
    int y = 0;
    if (std::cin >> y) {
        // runs if the stream successfully puts a value into y
        // (if the entered character was an int)

    } else {
        std::cin.clear(); // resets any error flags
        std::cin.ignore(10000, '\n'); // clears the buffer up to 10000 characters or \n character.
        // runs if the stream did not successfully put a value into y
        // this tends to happen when we use the wrong data type
    }
    */

    return 0;
}