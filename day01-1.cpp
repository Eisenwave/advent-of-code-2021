#include <iostream>

int main() {
    int count = 0;
    int x;
    int prev;
    std::cin >> prev;
    while (std::cin >> x) {
        count += x > prev;
        prev = x;
    }
    std::cout << count << '\n';
}
