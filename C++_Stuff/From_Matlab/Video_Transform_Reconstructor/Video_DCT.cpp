#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

// Function Declarations
cv::Mat subplot_stitch(const std::vector<cv::Mat>& images, int rows, int cols);
void find_DCT_zigzag(int elemz, int dims[2], std::vector<std::vector<int>>& coef_map);

// MAIN
int main() {
    
    // Open the default camera (usually webcam at index 0)
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the webcam." << std::endl;
        return -1;
    }

    cv::Mat im;
    cap >> im;  // Capture a new frame from the webcam

    if (im.empty()) {
        std::cerr << "Error: Could not retrieve frame." << std::endl;
    }


    // // Load Image
    // string path2pic = "C:/Users/maxba/Documents/C++_Stuff/C++_Image_Processing_Tutorial/Test_Images/bees_flower_640x360.png";
    // string yn_path2pic;
    // cout << "The current image is in " << path2pic << "\nDo you want to specify a new image?(y/n): ";
    // cin >> yn_path2pic;
    // if (yn_path2pic == "y") {
    //     cout << "Enter a new path to an image file: ";
    //     cin >> path2pic;
    // }

    // cv::Mat im = cv::imread(path2pic);
    // if (im.empty()) {
    //     cout << "Could not load image!" << endl;
    //     return -1;
    // }

    int coef_method;
    cout << "[1] Remove High Frequency Coefficients, [2] Remove Highest valued squares of coefficients\nChoose coefficient method:  ";
    cin >> coef_method;

    int dims[2] = {im.cols, im.rows}; // {width/colums, height/rows}

    // Convert image to floating-point format
    cv::Mat im_float;
    std::vector<cv::Mat> im_f_vec;
    // im.convertTo(im_float, CV_32F);
    // cv::split(im_float, im_f_vec);  // Split image into RGB channels

    // Containers for DCT coefficients and IDCT results
    std::vector<cv::Mat> im_dct(3, cv::Mat(dims[1], dims[0], CV_32F)); // DCT coefficients
    std::vector<cv::Mat> im_c(3, cv::Mat(dims[1], dims[0], CV_32F)); // compressed output image

    float coef_keep_amt = 1;  // # of coefficients to keep;
    float p = 1; // percent of coefficients to keep

    int numORperc = 1;

    cout << "Do you want to use [1] # of coefficients, or [2] %% of coefficients?: ";
    cin >> numORperc;

    // Zigzag diagonal coefficient path finding varibles
    int elemz = im_dct[0].total();
    vector<vector<int>> coef_map(2, vector<int>(elemz, 0));

    string input_str1;
    if (coef_method == 1) {
        input_str1 = "of coefficients (starting low)";

        find_DCT_zigzag(elemz, dims, coef_map);

        cout << "Hi" << endl;

        

    } else if (coef_method == 2) {
        input_str1 = "of greatest-valued Squared Coefficients (Energy)";
    }


    // Get fraction of coefficients
    switch (numORperc) {
        case 1:
            cout << "# " << input_str1 << " to keep after DCT: ";
            cin >> coef_keep_amt;
            break;
        case 2:
            cout << "% (as decimal 0-1) " << input_str1 << " to keep after DCT: ";
            cin >> p;
            break;
    }


    cout << "(Press & Hold 'q' or ESC to exit)" << endl;
        
    // Whie "q" or ESC are not pressed... 
    while (true) {
        if (coef_keep_amt >= elemz) {
            coef_keep_amt = 1;
        }
        coef_keep_amt *= 1.1;
        p = coef_keep_amt / elemz;

        // Capture new frame from webcam
        cap >> im;
        if (im.empty()) {
            std::cerr << "Error: Could not retrieve frame." << std::endl;
            break;
        }
    
        im.convertTo(im_float, CV_32F);
        cv::split(im_float, im_f_vec);  // Split image into RGB channels


        // For Each Color Channel...
        for (int rgb = 0; rgb < 3; ++rgb) {
            // DCT
            cv::dct(im_f_vec[rgb], im_dct[rgb]);

            switch (coef_method) {
                case 1: // "high-freq"
                    if (numORperc == 1) {
                        // nuthin
                    }
                    else if (numORperc == 2) {
                        // Find # of coefficients for percent cutoff
                        cout << "YO" << endl;
                        coef_keep_amt = (p * static_cast<float>(im_dct[rgb].total()));
                    }

                    // Remove high-frequency coefficients (using zigzag diagonal order from top left)
                    for (int i = coef_keep_amt; i < elemz; i++) {
                        im_dct[rgb].at<float>(coef_map[0][i], coef_map[1][i]) = 0;
                    }

                    // // Remove high-frequency coefficients (old way)
                    // for (int i = 0; i < dims[1]; i++) {
                    //     for (int j = 0; j < dims[0]; j++) {
                    //         if (i >= coef_keep_amt || j >= coef_keep_amt) {
                    //             im_dct[rgb].at<float>(i, j) = 0;
                    //         }
                    //     }
                    // }

                    
                    break;

                case 2: // "high-squares"

                    // Step 2: Square the coefficients to get energy values
                    cv::Mat im_dct_sqr = im_dct[rgb].mul(im_dct[rgb]);

                    // Step 3: Flatten the 2D squared coefficients matrix to a 1D vector for sorting
                    cv::Mat im_dct_sqr_flat = im_dct_sqr.reshape(1, 1); // Reshape to 1 row
                    vector<float> im_dct_v;
                    im_dct_sqr_flat.copyTo(im_dct_v); // Copy data to a standard vector

                    // Sort the vector in descending order
                    sort(im_dct_v.begin(), im_dct_v.end(), greater<float>());

                    // Step 4: Determine the threshold for the top p% of coefficients
                    if (numORperc == 1) {
                        // nuthin
                    }
                    else if (numORperc == 2) {
                        int coef_amt = im_dct_v.size();
                        coef_keep_amt = static_cast<int>(p * coef_amt);
                    }
                    // int coef_amt = im_dct_v.size();
                    // coef_keep_amt = static_cast<int>(p * coef_amt);
                    float threshold = im_dct_v[coef_keep_amt - 1]; // Threshold is the (p*coef_amt)-th largest value

                    // Step 5: Zero out coefficients below the threshold
                    Mat im_dct_new = im_dct[rgb].clone();
                    for (int r = 0; r < dims[1]; ++r) {
                        for (int c = 0; c < dims[0]; ++c) {
                            if (im_dct_sqr.at<float>(r, c) < threshold) {
                                im_dct_new.at<float>(r, c) = 0;
                            }
                        }
                    }

                    im_dct[rgb] = im_dct_new;
                    

                    break;

            }

            // Inverse DCT (reconstruct)
            cv::idct(im_dct[rgb], im_c[rgb]);

            // Normalize & convert back to original format (CV_8U)
            cv::normalize(im_c[rgb], im_c[rgb], 0, 255, cv::NORM_MINMAX);
            im_c[rgb].convertTo(im_c[rgb], CV_8U);
        }

        // Merge channels into a single image
        cv::Mat im_out;
        cv::merge(im_c, im_out);

        // Create Tiled Subplot
        std::vector<cv::Mat> im__im_out = {im, im_out}; // Put images in a vector
        cv::Mat subplot = subplot_stitch(im__im_out, 1, 2);
        // Display Output Image
        cv::namedWindow("Original & Compressed", cv::WINDOW_NORMAL); // use this to allow resizing
        cv::imshow("Original & Compressed", subplot); // show image
        cv::resizeWindow("Original & Compressed", subplot.cols, subplot.rows); // Set the window to its actual size

        // Exit loop if 'q' or ESC is pressed
        if ((cv::waitKey(1) == 'q') || (cv::waitKey(1) == 27)) {
            break;
        }

    }

    return 0;
}


// FUNCTIONS

cv::Mat subplot_stitch(const std::vector<cv::Mat>& images, int rows, int cols) {
    /*  ARGUMENTS
        images = vector (std::vector) of images (cv::Mat)
        rows = # of rows of images in the final subplot
        cols = # of cols in the final subplot
    */

    // Check if the number of images matches the specified rows and columns
    if (images.size() != rows * cols) {
        std::cerr << "Error: Number of images does not match rows * cols." << std::endl;
        return cv::Mat(); // Return an empty matrix
    }

    // Get the dimensions of the first image (assume all images are the same size)
    int height = images[0].rows;
    int width = images[0].cols;

    // Create a larger image to hold the sub-images
    cv::Mat combined_im_array(rows * height, cols * width, images[0].type());

    // Copy images into the combined image
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            images[r * cols + c].copyTo(combined_im_array(cv::Rect(c * width, r * height, width, height)));
        }
    }

    return combined_im_array;
}



void find_DCT_zigzag(int elemz, int dims[2], std::vector<std::vector<int>>& coef_map) {
    // Zigzag diagonal coefficient path finding varibles
    int r = 0, c = 0;
    int dir[2] = {1,-1};
    bool sides[4] = {0,0,0,0};
    bool touch_flag[2] = {0,0};

    for (int i = 0; i < elemz; ++i) {
        // cout << "[" << i << "]---------------------------" << endl;

        coef_map[0][i] = r;
        coef_map[1][i] = c;
        // cout << coef_map[0][i] << ", " << coef_map[1][i] << endl;

        if (c-1 < 0) { // left
            sides[0] = 1;
            touch_flag[0] = 1;
            // cout << "Left" << endl;
        }
        if (r-1 < 0) { // top
            sides[1] = 1;
            touch_flag[0] = 1;
            // cout << "Top" << endl;
        }
        if (c+1 == dims[0]) { // right
            sides[2] = 1;
            touch_flag[0] = 1;
            // cout << "Right" << endl;
        }
        if (r+1 == dims[1]) { // bottom
            sides[3] = 1;
            touch_flag[0] = 1;
            // cout << "Bottom" << endl;
        }

        // cout << "tf1 : " << touch_flag[0] << " " << touch_flag[1] << endl;
        if (touch_flag[0] && (!touch_flag[1])) {
            // cout << "TOUCH!" << endl;
            if (sides[1] && (!sides[2])) { // top normal
                c += 1;
            // } else if (sides[1] && (sides[2])) {
            //     r += 1;
            } else if (sides[0] && (!sides[3])) { // left normal
                r += 1;
            // } else if (sides[0] && (sides[3])) {
            //     c += 1;
            } else if (sides[2]) { // right
                r += 1;
            } else if (sides[3]) { // bottom
                c += 1;
            }
            // flip direction
            dir[0] *= -1; dir[1] *= -1;
            // sides[0] = 0; sides[1] = 0; sides[2] = 0; sides[3] = 0;
        }
        else {
            // cout << "Move: dir = {" << dir[0] << ", " << dir[1] << "}" << endl;
            // move
            c += dir[0];
            r += dir[1];
            touch_flag[0] = 0;
        }
        
        // Reset
        touch_flag[1] = touch_flag[0];
        touch_flag[0] = 0;
        // cout << "tf2 : " << touch_flag[0] << " " << touch_flag[1] << endl;
        sides[0] = 0; sides[1] = 0; sides[2] = 0; sides[3] = 0;
        

        // cout << coef_map[0][i] << ", " << coef_map[1][i] << endl;

    }

    // // Print
    // cout << "- - - - - - - - - - - - -" << endl;
    // for (int w = 0; w < 10; ++w) {
    //     cout << coef_map[0][w] << ", " << coef_map[1][w] << endl;
    // }
}