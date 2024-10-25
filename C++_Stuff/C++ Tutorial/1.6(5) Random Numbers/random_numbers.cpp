#include <cstdlib> // c standard library (C++ version)
// #include <stdlib.h> // c standard library (actual C version)
#include <ctime>
#include <iostream>
#include <chrono> // sleep function
#include <thread> // sleep fucntion

using namespace std;

int main() {
    int r, avg, sum = 0;
    srand(time(0)); // use the current time as the seed (0 or NULL) <-- DO BEFORE THE LOOP!
    for (int i=1; i<100; i++) {
        r = rand() % 100 + 1; // will be the same every time if the seed doesn't change
        sum += r;
        avg = sum / i;
        cout << "Random Number: " << r << ",  Average: " << avg << endl; 

        std::this_thread::sleep_for (std::chrono::microseconds(1000));
    }
}
    