#include <stdint.h> // Standard Int (uint8_t & size_t)
#include <cstdio> // C Standard Input Output (printf())

// Enumeration
enum ImageType {
    PNG, JPG, BMP, TGA
};

// Structure
struct Image {
    uint8_t* data = NULL; // 1 byte image data
    size_t size = 0;
    int w;          // width
    int h;          // height
    int channels;   // # of channels

    // Constructors
    Image(const char* filename); // just filename
    Image(int w, int h, int channels); // create blank image
    Image(const Image& img); // copy images
    // Deconstructor
    ~Image();

    // Functions
    bool read(const char* filename);
    bool write(const char* filename);

    ImageType getFileType(const char* filename);

    Image& grayscale_avg();
    Image& grayscale_lum();
};