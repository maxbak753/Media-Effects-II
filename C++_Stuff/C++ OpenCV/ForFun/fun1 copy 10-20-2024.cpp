// First Program For Fun (imagination experiment)
// Maxwell Bakalos 10/10/2024

#include <iostream> // Input-im_out Stream
#include <opencv2/opencv.hpp> // Open Computer Vision
#include <filesystem> // print working directory
#include <cmath> // pow()

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace cv;
using namespace std;

// Functions
std::tuple<int, int> choose_filter(int dims[2]);
cv::Mat gauss_kernel(int k_size, double a, double sigma_x, double sigma_y, bool normalize);
cv::Mat vert_line_kernel(int k_size);
cv::Mat subplot_stitch(const std::vector<cv::Mat>& images, int rows, int cols);

// Main
int main(int argc, char** argv ) {
    cout << "Hello!" << endl;
    cout << "Current working directory: " << filesystem::current_path() << endl;

    // Load Image
    string imPath = "moon.jpg"; 
    // string imPath = "face (300x300).png";
    // string imPath = "DrCostanza.JPEG";
    Mat im = imread(imPath, IMREAD_COLOR);
    // In case of empty image
    if (im.empty()) {
        cerr << "Error: Image is empty. Could not load or find the image!" << endl;
        return -1;
    } else {
        cout << "Press and key (or x-out of the window) to stop displaying the image!" << endl;
    }
    // Display Image
    namedWindow("Display image", WINDOW_AUTOSIZE);
    imshow("Display image", im);
    waitKey(0);

    cout << "TESTS\n\n";
    
    cv::Vec3b pxl = im.at<cv::Vec3b>(200, 200);
    cv::Mat pxl_mat(1, 1, CV_8UC3, pxl);
    cout << pxl << endl;
    cv::namedWindow("Pixel (0,0)", cv::WINDOW_NORMAL); // makes the display window resizable/big size
    imshow("Pixel (0,0)", pxl); waitKey(0);

    imshow("Pixel (0,0)", pxl_mat); waitKey(0);

    // Region Of Interest
    // METHOD #1: Ranges
    cout << "ROI" << endl;
    int startRow = im.rows/4;
    int endRow = 3 * im.rows/4;
    int startCol = im.cols/4;
    int endCol = 3 * im.cols/4;
    cv::Mat roi = im(cv::Range(startRow, endRow), cv::Range(startCol, endCol));
    cv::namedWindow("ROI", cv::WINDOW_NORMAL); // makes the display window resizable/big size
    imshow("ROI", roi); waitKey(0);

    // METHOD #2: Rectangle Region
    // Create a rectangle for the region (x, y, width, height)
    cv::Rect roiRect(startCol, startRow, endCol - startCol, endRow - startRow);
    cv::Mat roi2 = im(roiRect);
    cv::namedWindow("ROI 2", cv::WINDOW_NORMAL); // makes the display window resizable/big size
    imshow("ROI 2", roi2); waitKey(0);

    cv::destroyAllWindows();

    // -----------------------------
    // CONVOLUTION

    // Dimensions of Image
    int dims[2] = {im.cols, im.rows}; // {width, height}

    // Choose the filter type
    int filter_type; // # index denoting the type of filter used
    int k_size; // must be odd (the side length in pixels of the square convolution kernel)
    tie(filter_type, k_size) = choose_filter(dims);

    // Create Specified Kernel...
    cv::Mat k; // kernel matrix
    double sigma_x = k_size * 0.3, sigma_y = k_size *0.3; // sigma is the sqrt{variance} for each respective direction
    bool blur_valid = true;
    switch (filter_type) {
        case 1: // Box Blur
            k = cv::Mat::ones(k_size, k_size, CV_32F) * (pow(k_size, -2)); // Box Blur Kernel
            break;
        case 2: // Gaussian Blur
            k = gauss_kernel(k_size, 1, sigma_x, sigma_y, true); // Gaussian Blur Kernel
            break;
        case 3: // Vertical Line Blur
            cout << "Vertical Line Blur" << endl;
            k = vert_line_kernel(k_size);
            break;
        case 4: // Game Of Life Effect
            cout << "Game Of Life Effect" << endl;
            k = gauss_kernel(k_size,1,3,3,false) - gauss_kernel(k_size,1,1,1,false); // subtract gaussians
            k /= cv::sum(k); // normalize
            blur_valid = false;
            break;
        default:
            cout << "The option you chose does not exist!\n>:(" << endl;
            blur_valid = false;
            break;
    }
    cv::namedWindow("Kernel", cv::WINDOW_NORMAL);
    imshow("Kernel", k*255);
    waitKey(0);

    // Create an output image to store the result
    cv::Mat im_out;

    if (blur_valid) {
        // // Create an output image to store the result
        // cv::Mat im_out;
        
        // Perform convolution
        cv::filter2D(im, im_out, CV_32F, k);

        // // Convert the im_out image to the same type as the original image
        // im_out.convertTo(im_out, im.type());

        // // Create a Subplot
        // std::vector<cv::Mat> im__im_out = {im, im_out}; // Put images in a vector
        // cv::Mat subplot = subplot_stitch(im__im_out, 1, 2); // make plot image
        // // Display Subplot
        // cv::namedWindow("Subplot: OG Image, Convolved Image", cv::WINDOW_NORMAL); // use this to allow resizing
        // cv::imshow("Subplot: OG Image, Convolved Image", subplot); // show image
        // cv::resizeWindow("Subplot: OG Image, Convolved Image", subplot.cols, subplot.rows); // Set the window to its actual size
        // cv::waitKey(0);

    } else if ((!blur_valid) && (filter_type == 4)) {
        cout << "GOL!!!" << endl;
        // Create matrices to store the three channels
        std::vector<cv::Mat> channels1(3);
        std::vector<cv::Mat> channels2(3);

        cout << "Test 1" << endl; // **************************************

        // Split the image into B, G, R channels
        cv::split(im, channels1);

        for (int rgb = 0; rgb < 3; rgb++) {
            double min_bound = 0.2;
            double max_bound = 0.45;
            double bound_diff = max_bound - min_bound;
            double shx = min_bound, shy = 0.5, scale = 0.5;

            cout << "Test 2" << endl; // **************************************
            
            // x = conv2(im_disp(:,:,rgb), kernel);
            cv::Mat im_c = channels1[rgb];
            cv::Mat x = im_c.clone();
            // extractChannel(im, x, rgb); // get rgb slice of image
            cv::filter2D(im_c, x, CV_32F, k);
            // (SKIP CROPPING for now)
            // x = x(n_k+1:end-n_k, n_k+1:end-n_k);

            // Ensure x is of type CV_32F (if not already)
            if (x.type() != CV_32F) {
                cout << "x is not CV_32F!!!" << endl;
                x.convertTo(x, CV_32F);
            }

            // Normalize x to range [0, 1]
            x /= 255.0;

            cout << "Test 3" << endl; // **************************************

            //  // above = x > min_bound;
            //  // im_n([below, rgb]) = 0;

            // cv::Mat y = ( ( -cos((1.0/(bound_diff*2))*2*M_PI*(x - shx)) ) * scale ) + shy;

            double idk = (1.0/(bound_diff*2))*2*M_PI;

            // cv::Mat x; // Assuming x is initialized with some values
            cv::Mat y = x.clone();

            // // Lambda Function "[=]" captures external variables shx and bound_diff
            // y.forEach<double>([=](double &val, const int * position) -> void {
            //     val = -std::cos(idk * (val - shx));
            // });

            // Lambda Function "[=]" captures external variables shx and bound_diff
            y.forEach<float>([=](float &val, const int * position) -> void {
                // must convert idk & shx variables to floats to interact with other float variables
                // -cos((1/(bound_diff*2))*2*pi*(x - shx)) )
                val = -std::cos(static_cast<float>(idk) * (val - static_cast<float>(shx)));
            });

            cout << "Test 4.0" << endl; // **************************************

            // Display Subplot
            cv::Mat y_now = y.clone();
            cv::namedWindow("y now", cv::WINDOW_NORMAL); // use this to allow resizing
            cv::imshow("y now", y_now); // show image
            cv::resizeWindow("y now", y_now.cols, y_now.rows); // Set the window to its actual size
            cv::waitKey(0);

            // Minimum, Maximum, & Average check 1
            double minVal, maxVal;
            cv::Point minLoc, maxLoc;
            cv::minMaxLoc(x, &minVal, &maxVal, &minLoc, &maxLoc);
            cout << "Minimum value: " << minVal << " at location " << minLoc << endl;
            cout << "Maximum value: " << maxVal << " at location " << maxLoc << endl;
            cv::Scalar meanVal = cv::mean(x);
            cout << "Average value: " << meanVal[0] << endl;

            // Convert min_bound to float to match the type of x
            float min_bound_f = static_cast<float>(min_bound);

            // // Ensure x is of type CV_32F (if not already)
            // if (x.type() != CV_32F) {
            //     cout << "x is not CV_32F!!!" << endl;
            //     x.convertTo(x, CV_32F);
            // }

            // // Normalize x to range [0, 1]
            // x /= 255.0;

            cout << "min_bound: " << min_bound << endl;

            // Create a mask where x < min_bound
            cv::Mat lessThanMask = (x < min_bound_f);

            cout << "Test 5.0" << endl; // **************************************

            // Set y to 0 wherever the mask is true (where x < min_bound)
            y.setTo(0, lessThanMask);

            cout << "Test 6" << endl; // **************************************

            // Display Subplot
            y_now = y.clone();
            cv::namedWindow("y now 2", cv::WINDOW_NORMAL); // use this to allow resizing
            cv::imshow("y now 2", y_now); // show image
            cv::resizeWindow("y now 2", y_now.cols, y_now.rows); // Set the window to its actual size
            cv::waitKey(0);

            // Display LessThanMask
            cv::namedWindow("ltm", cv::WINDOW_NORMAL); // use this to allow resizing
            cv::imshow("ltm", lessThanMask); // show image
            cv::resizeWindow("ltm", lessThanMask.cols, lessThanMask.rows); // Set the window to its actual size
            cv::waitKey(0);

             // Minimum, Maximum, & Average check 1
            // double minVal, maxVal;
            // cv::Point minLoc, maxLoc;
            cv::minMaxLoc(lessThanMask, &minVal, &maxVal, &minLoc, &maxLoc);
            cout << "Minimum value: " << minVal << " at location " << minLoc << endl;
            cout << "Maximum value: " << maxVal << " at location " << maxLoc << endl;
            meanVal = cv::mean(lessThanMask);
            cout << "Average value: " << meanVal[0] << endl;

            // y = ( ( -cos((1/(bound_diff*2))*2*pi*(x - shx)) ) * scale ) + shy;
            // y(x < min_bound) = 0;

            channels2[rgb] = y;

            cout << "Test end loop" << endl; // **************************************
        }

        
        cv::merge(channels2, im_out);
        cv::normalize(im_out, im_out, 0, 255, cv::NORM_MINMAX); // 0-255 range
        cout << "End of it" << endl;
    }

    // Convert the im_out image to the same type as the original image
    im_out.convertTo(im_out, im.type());

    // Create a Subplot
    std::vector<cv::Mat> im__im_out = {im, im_out}; // Put images in a vector
    cv::Mat subplot = subplot_stitch(im__im_out, 1, 2); // make plot image
    // Display Subplot
    cv::namedWindow("Subplot: OG Image, Convolved Image", cv::WINDOW_NORMAL); // use this to allow resizing
    cv::imshow("Subplot: OG Image, Convolved Image", subplot); // show image
    cv::resizeWindow("Subplot: OG Image, Convolved Image", subplot.cols, subplot.rows); // Set the window to its actual size
    cv::waitKey(0);

    cout << "Done." << endl;
    return 0;
}

// -------------------------
// FUNCTIONS

std::tuple<int, int> choose_filter(int dims[2]) {
    /*  ARGUMENTS
        dims = dimensions of the image (width, height)
    */
    cout << "~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~" << endl;
    cout << "Filter options...\n[1] Box Blur\n[2] Gaussian Blur\n[3] Vertical Line Blur\nChoose a filter (enter the number): ";
    int filter_choice = 1;
    cin >> filter_choice;

    int filt_size;
    bool filt_size_valid = false;

    int while_count = 0;
    while (!filt_size_valid) {
        if (while_count < 10) {
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
        } else {
            cout << "Failed too many times (" << while_count << ") --> Filter Size to 5." << endl;
            filt_size = 5;
            filt_size_valid = true;
        }
        while_count += 1;
    }

    // int filter_properties[2] = {filter_choice, filt_size};
    return std::make_tuple(filter_choice, filt_size);
}

cv::Mat gauss_kernel(int k_size, double a, double sigma_x, double sigma_y, bool normalize) {
    /*  ARGUMENTS
        k_size = kernel size (length of square side)
        sigma_x = sigma for x-direction
        sigma_y = sigma for y-direction
    */

    // Create a kernel of the specified size
    cv::Mat kernel = cv::Mat::zeros(k_size, k_size, CV_32F);

    // Create 2D Gaussian Function
    int half_k_sz = k_size / 2;
    double gauss_k_sum = 0; // sum of kernel values (for normalization)
    // Populate the kernel with Gaussian values
    for (int y = -half_k_sz; y <= half_k_sz; ++y) {
        for (int x = -half_k_sz; x <= half_k_sz; ++x) {
            kernel.at<float>(y+half_k_sz, x+half_k_sz) = static_cast<float>( exp( -( (x*x)/(2*sigma_x*sigma_x) ) - ( (y*y)/(2*sigma_y*sigma_y) ) ) );
            // gauss_k_sum += kernel.at<float>(y+half_k_sz, x+half_k_sz); // get sum of kernel elements
        }
    }

    // Amplitude Scaling
    kernel *= a;

    if (normalize) {
        // Normalize
        // kernel /= gauss_k_sum;
        kernel /= cv::sum(kernel);
    }

    return kernel;
}

cv::Mat vert_line_kernel(int k_size) {
    cv::Mat kernel = cv::Mat::zeros(k_size, k_size, CV_32F);

    cv::Rect vLine(k_size/2, 0, 1, k_size);

    // kernel(vLine) = 1 / (vLine.width * vLine.height); // normalize
    kernel(vLine).setTo(1.0/((double)(vLine.width * vLine.height)));

    return kernel;
}

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

    // Get the dimensions of the first image
    int img_height = images[0].rows;
    int img_width = images[0].cols;

    // Create a larger image to hold the sub-images
    cv::Mat combined(rows * img_height, cols * img_width, images[0].type());

    // Copy images into the combined image
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            images[r * cols + c].copyTo(combined(cv::Rect(c * img_width, r * img_height, img_width, img_height)));
        }
    }

    return combined;
}