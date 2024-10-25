#include <iostream>
#include <fstream> // write/read images
#include <sstream> // stringstream

using namespace std;

int main() {
    cout << "Filtering Image... " <<endl;

    ifstream image;
    ofstream newImage;

    image.open("C:/Users/maxba/Documents/C++_Stuff/C++ Tutorial/4.1 Image Programming from Scratch/P3_Test_Images/monument.ppm");
    newImage.open("newImage.ppm");

    // Copy Over Header Information
    string type = "", width = "", height = "", RGB = "";
    image >> type;
    image >> width;
    image >> height;
    image >> RGB;
    int RGB_int = stoi(RGB);
    cout << "Type: " << type << "\nDimensions: " << width << "x" << height << "\nMaximum Color Value: " << RGB << endl;

    newImage << type << endl;
    newImage << width << " " << height << endl;
    newImage << RGB << endl;

    string red = "", green = "", blue = "";
    int r = 0, g = 0, b = 0;
    // While not at the end of the file...
    while (!image.eof()) {
        // Pattern of r, g, b, r, g, b, ... (may or may not have newlines!)
        image >> red;
        image >> green;
        image >> blue;

        stringstream redstream(red);
        stringstream greenstream(green);
        stringstream bluestream(blue);

        redstream >> r;
        greenstream >> g;
        bluestream >> b;

        // Increase the blue value (clip at maximum color value)
        if (b + 50 > RGB_int) {
            b = RGB_int;
        } else {
            b += 50;
        }

        newImage << r << " " << g << " " << b << endl;
    }

    // Close
    image.close();
    newImage.close();
    cout << "Done." << endl;
    return 0;
}