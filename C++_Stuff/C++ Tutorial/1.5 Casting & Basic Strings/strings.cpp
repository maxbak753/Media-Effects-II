#include <iostream>

int main() {
    // Implicit Casting
    std::cout << "Implicit Casting: " <<3 + 4.5 << std::endl;

    // Explicit Casting
    std::cout << "Explicit Casting: " << 3 + (int)4.5 << std::endl;

    // Explicil y Casting Chars
    char a = 'a';
    std::cout << "a: " << a << std::endl;
    std::cout << "(int)a: " << (int)a << std::endl; // shows ascii code #
    a += 10;
    std::cout << "a + 10: " << a << std::endl;
    std::cout << "(int)(a + 10): " << (int)a << std::endl;

    // EXTRA endl meaning
    std::string name = "Hello, World";
    // 2 line version
    std::cout << name;
    std::cout << std::endl; // clear buffer
    // 1 line version
    std::cout << name << std::endl;

    return 0;
}