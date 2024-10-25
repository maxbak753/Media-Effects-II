#ifndef MYCLASS_HPP

#define MYCLASS_HPP

class Rectangle {
    public:
        double length;
        double width;

        Rectangle(double l, double w);

        double area();
        double perimeter();
};

#endif