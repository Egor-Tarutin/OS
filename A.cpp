#include <iostream>

int main() {
    int add;
    std::cin >> add;
    while(add != 17) {
        std::cout << add + 17 << " ";
        std::cin >> add;
    }
    std::cout << 17;
    return 0;
}