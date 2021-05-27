#include <iostream>

int main() {
    int pow;
    std::cin >> pow;
    while(pow != 17) {
        std::cout << pow * pow * pow << " ";
        std::cin >> pow;
    }
    std::cout << 17;
    return 0;
}