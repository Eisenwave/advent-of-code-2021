#include <iostream>
#include <algorithm>
#include <array>

int main() {
    unsigned count = 0;
    std::array<int, 4> ring{};
    unsigned i = 0;
    for (unsigned i = 0; std::cin >> ring[i & 3]; ++i) {
        count += i >= 3 && ring[i - 0 & 3] > ring[i - 3 & 3];
    }
    std::cout << count << '\n';
}
