#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

// ------------------------------------------
// CONSTRUCTORS - - - - - - -
// just filename
Image::Image(const char* filename) {
    if (read(filename)) {
        printf("Read &s\n", filename);
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
// FUNCTION - - - - - - -
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
    else {
        return PNG;
    }
}