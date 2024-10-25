#include <iostream>

int main() {

    int a = 5, b = 7, c = 11;
    double e = 5, f = 7, g = 11.11;

    // Arithmetic Operators 
    std::cout << "Arithmetic Operators" << std::endl;

    std::cout << a + b << std::endl;
    std::cout << e - g << std::endl;
    std::cout << e * f << std::endl;

    std::cout << b / a << std::endl; // 7/5 = 1.4 rounds to 1
    std::cout << b % a << std::endl; // remainder of 7/5 is 2

    std::cout << f / e << std::endl; // 7/5 = 1.4

    // Compound Assignments
   std::cout << "\nCompound Assignments" << std::endl;
   
   std::cout << a << std::endl;
   a+= c; // a-= c; a /= c; a *= c; a%= c;
   std::cout << a << std::endl;

   // Precedence of Arithmetic Operators
   std::cout << "\nPrecedence of Arithmetic Operators" << std::endl;
   a *= (a/b) + c; // a/b -->  +c --> *a
   std::cout << a << std::endl;

   // Awkward Assignment
   std::cout << "\nAwkward Assignment" << std::endl;

   int h;
   int i = 5 + (h = 2); // assigning h inside of an expression!
   std::cout << h << std::endl;
   std::cout << i << std::endl;

   int j, k, l;
   j = k = l = 3;
   std::cout << j << std::endl;
   std::cout << k << std::endl;
   std::cout << l << std::endl;

   // Inputs Test
   std::cout << "\n[Inputs Test]" << std::endl;
   int ia, ib, ic;
   std::cout << "Enter Integer A: ";
   std::cin>> ia;
   std::cout << "Enter Integer B: ";
   std::cin>> ib;
   std::cout << "Enter Integer C: ";
   std::cin>> ic;

   std::cout << "A + B + C = " << ia + ib + ic << std::endl;




    return 0;
}