// header files should have the same name as the main file

#ifndef MAIN_HPP // include gaurd -> preventsm ultiple definitions of same header
#define MAIN_HPP

#define MAX 1000

void announce(std::string message); // don't use namespace in header file because it forces everything else to use it

#endif