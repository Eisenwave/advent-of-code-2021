#include <iostream>
#include <unordered_map>

using ull = unsigned long long;
using map_type = std::unordered_map<ull, ull>;

void simulate(map_type &nue, const map_type &old) {
    for (const auto [state, count] : old) {
        if (state != 0) {
            nue[state - 1] += count;
        }
        else {
            nue[6] += count;
            nue[8] += count;
        }
    }
}

int main() {
    map_type old;
    map_type nue;
    ull f;
    while ((std::cin >> f).ignore()) {
        old[f] += 1;
    }
    for (ull i = 0; i < 256; ++i) {
        simulate(nue, old);
        std::swap(nue, old);
        nue.clear();
    }
    ull total = 0;
    for (const auto [state, count] : old) {
        total += count;
    }
    std::cout << total << '\n';
}
