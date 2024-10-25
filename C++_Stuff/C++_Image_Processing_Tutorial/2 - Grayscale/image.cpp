#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

// [1 - Setup]
// ------------------------------------------
// CONSTRUCTORS - - - - - - -
// just filename
Image::Image(const char* filename) {
    if (read(filename)) {
        printf("Read %s\n", filename);
        size = w*h*channels; // width * height * channels
    }
    else {
        printf("Failed to read %s\n", filename);
    }
}
// create blank image
Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) { // <-- initializer list (?)
    size = w*h*channels; // width * height * channels
    data = new uint8_t[size]; // blank image of specific size
}
// copy images
Image::Image(const Image& img) : Image(img.w, img.h, img.channels) { // <-- call the other constructor to create a blank image
    // copy the desired image into the blank image 
    memcpy(data, img.data, img.size);
}

// ------------------------------------------
// DECONSTRUCTOR - - - - - - -
Image::~Image() {
    stbi_image_free(data); // cleans up al the data
}

// ------------------------------------------
// FUNCTIONS - - - - - - -
bool Image::read(const char* filename) {
    // Load Data using STB Image Library function
    data = stbi_load(filename, &w, &h, &channels, 0);
    // Return 1 if the data is not empty
    return data != NULL;
}

bool Image::write(const char* filename){ 
    ImageType type = getFileType(filename);
    int success;
    int jpg_quality = 100; // JPEG image quality 0-100
    switch(type) {
        case PNG:
            success = stbi_write_png(filename, w, h, channels, data, w*channels);
            break;
        case BMP:
            success = stbi_write_bmp(filename, w, h, channels, data);
            break;
        case JPG:
            success = stbi_write_jpg(filename, w, h, channels, data, jpg_quality);
            break;
        case TGA:
            success = stbi_write_tga(filename, w, h, channels, data);
            break;
    }
    // if "success" is not zero the nit was successful
    return success != 0;
}

ImageType Image::getFileType(const char* filename) {
    // get file type extension from file's name
    const char* ext = strrchr(filename, '.'); // locate last occurance of character in string
    if (ext != nullptr) {
        if (strcmp(ext, ".png") == 0) {
            return PNG;
        }
        else if (strcmp(ext, ".jpg") == 0) {
            return JPG;
        }
        else if (strcmp(ext, ".bmp") == 0) {
            return BMP;
        }
        else if (strcmp(ext, ".tga") == 0) {
            return PNG;
        }
    }
    return PNG;
}

// [2 - Grayscale]

Image& Image::grayscale_avg() {
    // Average: (r + g + b) / 3
    if (channels < 3) {
        printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
    }
    else {
        for (int i = 0; i < size; i += channels) {
            //(r+g+b)/3
            int gray = (data[i] + data[i+1] + data[i+2])/3;
            // set each of the channels to the same gray value
            // data+i = current pixel
            memset(data+i, gray, 3);
        }
    }
    return *this;
}

Image& Image::grayscale_lum() {
    // https://en.wikipedia.org/wiki/Grayscale
    // Luminance: 
    if (channels < 3) {
        printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
    }
    else {
        for (int i = 0; i < size; i += channels) {
            // 0.2126*r + 0.7152*g + 0.0722*b
            int gray = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
            // data+i = current pixel
            memset(data+i, gray, 3);
        }
    }
    return *this;

}