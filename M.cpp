#include <iostream>

int main() {
    int mult;
    std::cin >> mult;
    while(mult != 17) {
        std::cout << mult * 7 << " ";
        std::cin >> mult;
    }
    std::cout << 17;
    return 0;
}