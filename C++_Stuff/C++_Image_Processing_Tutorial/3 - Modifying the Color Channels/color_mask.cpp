#include "Image.h"

int main() {
    Image test("C:/Users/maxba/Documents/C++_Stuff/C++_Image_Processing_Tutorial/Test_Images/Barbara_color.jpg");

    // Color Mask
    test.colorMask(0,0,1);

    // Write to File
    test.write("blue.png");

    return 0;
}