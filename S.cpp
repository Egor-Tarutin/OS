#include <iostream>

int main() {
    int num;
    std::cin >> num;
    int sum = 0;
    while(num != 17) {
        sum += num;
        std::cin >> num;
    }
    std::cout << sum;
    return 0;
}