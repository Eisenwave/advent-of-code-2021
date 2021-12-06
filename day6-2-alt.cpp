#include <iostream>
#include <numeric>

int main() {
    unsigned long long fish[9] {}, i;
    while ((std::cin >> i).ignore()) {
        fish[i] += 1;
    }
    for (i = 0; i < 256; ++i) {
        fish[(i + 7) % 9] += fish[i % 9];
    }
    std::cout << std::accumulate(fish, fish + 9, 0ull) << '\n';
}
