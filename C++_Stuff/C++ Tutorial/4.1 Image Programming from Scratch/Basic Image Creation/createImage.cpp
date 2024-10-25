#include <iostream>
#include <fstream> // read/write to images
#include <ctime>
#include <cstdlib>

// create an image from scratch
// https://en.wikipedia.org/wiki/Netpbm

using namespace std;

int main() {

    ofstream image; // output file stream class
    image.open("image.ppm"); // Portable PixMap file

    srand(time(0)); // set random seed from current time

    // Check if Image is Open
    if (image.is_open()) {
        // place header info
        image << "P3" << endl; // type of file
        image << "250 250" << endl; // width & height
        image << "255" << endl; // maximum value for each color

        // loop through the rows & columns of the image
        // Put each pixel RGB value "R G B" on a new line
        // Use some type of math to get a cool effect on the pixels
        // for (int y = 0; y < 250; y++) {
        //     for (int x = 0; x < 250; x++) {
        //         image << (x * y) % 255 << " " << x << " " << y % 255 << endl;
        //     }
        // }
        for (int y = 0; y < 250; y++) {
            for (int x = 0; x < 250; x++) {
                image << rand() % 255 << " " << rand() % 255 << " " << rand() % 255 << endl;
            }
        }
    }

    image.close();

    cout << "Done." << endl;

    return 0;
}