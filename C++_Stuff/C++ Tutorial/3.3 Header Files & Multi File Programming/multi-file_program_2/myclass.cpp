#include "myclass.hpp"

// :: is the scope resolutions operator
//  It can be used to match functions to a namespace or match functions to a class

Rectangle::Rectangle(double l, double w) {
    length = l;
    width = w;
}

double Rectangle::area() {
    return length * width;
}

double Rectangle::perimeter() {
    return (2.0 * length) + (2.0 * width);
}