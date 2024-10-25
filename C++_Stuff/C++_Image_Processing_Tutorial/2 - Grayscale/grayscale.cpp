#include "Image.h"

int main() {
    Image test("C:/Users/maxba/Documents/C++_Stuff/C++_Image_Processing_Tutorial/Test_Images/Barbara_color.jpg");

    // Average Grayscale
    Image gray_avg = test;
    gray_avg.grayscale_avg();
    gray_avg.write("gray_avg.png");

    // Luminance Grayscale
    Image gray_lum = test;
    gray_lum.grayscale_lum();
    gray_lum.write("gray_lum.png");
    

    return 0;
}