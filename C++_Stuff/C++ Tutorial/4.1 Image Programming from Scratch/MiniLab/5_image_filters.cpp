#include <iostream>
#include <fstream> // write/read images
#include <sstream> // stringstream
#include <vector> // image matrix
#include <cmath> // exponents x^2
#include <algorithm> // min(a,b)

// C:/Users/maxba/Documents/C++_Stuff/C++ Tutorial/4.1 Image Programming from Scratch/P3_Test_Images/monument.ppm

using namespace std;

void file_handler();
string get_filename();
bool open_file(fstream& file, string filename);

int choose_filter();
void rgb_shift(ifstream& og_im, ofstream& new_im);
void purple(ifstream& og_im, ofstream& new_im);
void blur(ifstream& og_im, ofstream& new_im);

int main() {
    cout << "START " <<endl;

    file_handler();

    cout << "END" << endl;
    return 0;
}

void file_handler() {
    ifstream og_im;
    ofstream new_im; // must create variable here so it is in the scope of other files via reference (&)
    string filename = get_filename();

    og_im.open(filename.c_str());
    new_im.open("filtered_image.ppm");

    // If both files opened successfully...
    if (og_im.is_open() && new_im.is_open()) {
        // Choose the filter type
        switch (choose_filter()) {
            // Go to the chosen filter function
            case 1:
                rgb_shift(og_im, new_im);
                break;
            case 2:
                purple(og_im, new_im);
                break;
            case 3:
                blur(og_im, new_im);
                break;
            default:
                cout << "Nuthin' chosen" << endl;
                break;
        }
    } else {
        cout << "The file never opened" << endl;
    }
    new_im.close(); // close file
}

string get_filename() {
    cout << "Enter a file path & name that you want to work with: " << endl;
    string filename = "";
    getline(cin, filename);
    return filename;
}

int choose_filter() {
    cout << "Filter options...\n[1] Color Shift\n[2] Purple\n[3] Blur\nChoose a filter (enter the number):" << endl;
    int filter_choice = 1;
    cin >> filter_choice;
    return filter_choice;
}

void rgb_shift(ifstream& og_im, ofstream& new_im) {

    // Copy Over Header Information
    string type = "", width = "", height = "", RGB = "";
    og_im >> type;
    og_im >> width;
    og_im >> height;
    og_im >> RGB;
    int RGB_int = stoi(RGB);
    cout << "Type: " << type << "\nDimensions: " << width << "x" << height << "\nMaximum Color Value: " << RGB << endl;

    new_im << type << endl;
    new_im << width << " " << height << endl;
    new_im << RGB << endl;

    string red = "", green = "", blue = "";
    int r = 0, g = 0, b = 0;
    int rgb_choice;

    cout << "Which color would you like to change? [1] Red, [2] Green, [3] Blue: ";
    cin >> rgb_choice;
    rgb_choice -= 1; // arrays start at 0 not 1

    int rgb[3] = {0,0,0};

    // While not at the end of the file...
    while (!og_im.eof()) {
        // Pattern of r, g, b, r, g, b, ... (may or may not have newlines!)
        // Get R G B for pixel
        og_im >> red;
        og_im >> green;
        og_im >> blue;
        stringstream redstream(red);
        stringstream greenstream(green);
        stringstream bluestream(blue);
        redstream >> r;
        greenstream >> g;
        bluestream >> b;
        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;

        // Increase the chosen color value (clip at maximum value)
        if (rgb[rgb_choice] + 50 > RGB_int) {
            rgb[rgb_choice] = RGB_int;
        } else {
            rgb[rgb_choice] += 50;
        }

        new_im << rgb[0] << " " << rgb[1] << " " << rgb[2] << endl;
    }

}

void purple(ifstream& og_im, ofstream& new_im) {
    // Copy Over Header Information
    string type = "", width = "", height = "", RGB = "";
    og_im >> type;
    og_im >> width;
    og_im >> height;
    og_im >> RGB;
    int RGB_int = stoi(RGB);
    cout << "Type: " << type << "\nDimensions: " << width << "x" << height << "\nMaximum Color Value: " << RGB << endl;

    new_im << type << endl;
    new_im << width << " " << height << endl;
    new_im << RGB << endl;

    string red = "", green = "", blue = "";
    int r = 0, g = 0, b = 0;

    // While not at the end of the file...
    while (!og_im.eof()) {
        // Pattern of r, g, b, r, g, b, ... (may or may not have newlines!)
        // Get R G B for pixel
        og_im >> red;
        og_im >> green;
        og_im >> blue;
        stringstream redstream(red);
        stringstream greenstream(green);
        stringstream bluestream(blue);
        redstream >> r;
        greenstream >> g;
        bluestream >> b;

        // Increase the red value (clip at maximum value)
        if (r + 50 > RGB_int) {
            r = RGB_int;
        } else {
            r += 50;
        }
        // Increase the blue value (clip at maximum value)
        if (b + 110 > RGB_int) {
            b = RGB_int;
        } else {
            b += 110;
        }

        new_im << r << " " << g << " " << b << endl;
    }
}

void blur(ifstream& og_im, ofstream& new_im) {
    // Copy Over Header Information
    string type = "", width = "", height = "", RGB = "";
    og_im >> type;
    og_im >> width;
    og_im >> height;
    og_im >> RGB;
    int RGB_int = stoi(RGB);
    cout << "Type: " << type << "\nDimensions: " << width << "x" << height << "\nMaximum Color Value: " << RGB << endl;

    new_im << type << endl;
    new_im << width << " " << height << endl;
    new_im << RGB << endl;

    string red = "", green = "", blue = "";
    int r = 0, g = 0, b = 0;

    const int dims[2] = {stoi(height), stoi(width)}; // Rows by Columns
    cout << "Test" << endl;
    cout << "Dimensions 2: " << dims[0] << "x" << dims[1] << endl;

    // Initialising a 3D vector with 0 as initial value
    vector<vector<vector<int>>> im_mat(dims[0], vector<vector<int>>(dims[1], vector<int>(3)));


    int filt_size;
    bool filt_size_valid = false;
    
    while (!filt_size_valid) {
        cout << "Select a blurring filter size (odd number): ";
        cin >> filt_size;
        if (filt_size % 2) {
            if (filt_size < min(dims[0], dims[1])) {
                if (filt_size > 1) {
                    filt_size_valid = true;
                } else {
                    cout << "Filter Size is TOO SMALL! Try again..." << endl;
                }
            } else {
                cout << "Filter Size is TOO BIG! Try again..." << endl;
            }
        } else {
            cout << "Filter Size must be an ODD NUMBER! Try again ..." << endl;
        }
    }

    cout << "Putting image into matrix... ";


    int row = 0; // row
    int col = 0; // column

    // While not at the end of the file...
    while (!og_im.eof()) {
        // Pattern of r, g, b, r, g, b, ... (may or may not have newlines!)
        // Get R G B for pixel
        og_im >> red;
        og_im >> green;
        og_im >> blue;
        stringstream redstream(red);
        stringstream greenstream(green);
        stringstream bluestream(blue);
        redstream >> r;
        greenstream >> g;
        bluestream >> b;
    
        // read rgb values into 3d image matrix
        im_mat[row][col][0] = r;
        im_mat[row][col][1] = g;
        im_mat[row][col][2] = b;

        // Increment to next pixel
        if (col+1 < dims[1]) {
            col += 1;
        } else if (row+1 < dims[0]) {
            col = 0;
            row += 1;
        }

    }

    cout << "Done." << endl;

    // Operate Filter on Matrix
    cout << "Blurring... ";

    vector<vector<vector<int>>> im_mat_blurred = im_mat; // copy of image
    double k_sum = 0; // sum for kernel
    int k_rng = floor(filt_size/2);

    // Create Box Blur Filter Kernel
    std::vector<std::vector<double>> kernel(filt_size, std::vector<double>(filt_size, 1.0/pow(filt_size, 2)));

    // Create Box Blur Filter Kernel
    double gauss_k_sum = 0;
    double fr_kRng = k_rng * 0.95; // # proportional to filter size that determines scale of gaussian function
    for (double x=(double)(-k_rng); x<=(double)k_rng; x++) {
        for (double y=(double)(-k_rng); y<=(double)k_rng; y++) {
            kernel[x+k_rng][y+k_rng] = exp(-pow((x/fr_kRng),2) - pow((y/fr_kRng),2));
            gauss_k_sum += kernel[x+k_rng][y+k_rng]; // get sum of kernel elements
        }
    }

    // Normalize: divide each element by the sum
    for (int i = 0; i < filt_size; i++) {
        for (int j = 0; j < filt_size; j++) {
            kernel[i][j] /= gauss_k_sum;
        }
    }


    for (int rr=k_rng; rr<dims[0]-k_rng; rr++) {
        for (int cc=k_rng; cc<dims[1]-k_rng; cc++) {
            for (int rgb=0; rgb<3; rgb++){
                // Extract the sub-matrix
                for (int ki = -k_rng; ki <= k_rng; ki++) {
                    for (int kj = -k_rng; kj <= k_rng; kj++) {
                        k_sum += im_mat[rr + ki][cc + kj][rgb] * kernel[ki + k_rng][kj + k_rng];
                    }
                }
                // Put filter result into pixel & reset kernel convolution sum
                im_mat_blurred[rr][cc][rgb] = (int)k_sum;
                k_sum = 0;
            }
        }
    }

    cout << "Done." << endl;

    // Put 3D Array back into ppm Image File
    for (int rr=0; rr<dims[0]; rr++) {
        for (int cc=0; cc<dims[1]; cc++) {
            new_im << im_mat_blurred[rr][cc][0] << " " << im_mat_blurred[rr][cc][1] << " " << im_mat_blurred[rr][cc][2] << endl;
        }
    }

}
