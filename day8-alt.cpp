#include <iostream>
#include <string>
#include <algorithm>

std::size_t common_count(const std::string &a, const std::string &b) {
    return std::ranges::count_if(a, [&b](char c) {
        return b.find(c) != std::string::npos;
    });
}

std::size_t decode(std::string (&a)[10], std::string (&nums)[4]) {
    static constexpr std::size_t desired_order[] {
        1, 7, 4, 2, 5, 3, 6, 0, 9, 8  
    };
    std::ranges::sort(a + 0, a + 10, {}, [](const auto &s) {
        return s.length();
    });
    std::ranges::sort(a + 3, a +  6, {}, [&a](const auto &s) {
        return common_count(a[0], s) * 16 + common_count(a[2], s);
    });
    std::ranges::sort(a + 6, a +  9, {}, [&a](const auto &s) {
        return common_count(a[0], s) * 16 + common_count(a[2], s);
    });
    
    for (std::string &s : a) {
        std::ranges::sort(s);
    }
    
    std::size_t val = 0;
    for (std::string &n : nums) {
        std::ranges::sort(n);
        val *= 10;
        val += desired_order[std::ranges::find(a, n) - a];
    }
    return val;
}

int main() {
    char sep;
    std::string in[10], out[4];
    std::size_t count1478 = 0;
    std::size_t sum = 0;
    while (true) {
        for (std::string &i : in) {
            std::cin >> i;
        }
        if (not (std::cin >> sep)) {
            break;
        }
        
        for (std::string &o : out) {
            std::cin >> o;
            count1478 += (o.length() == 2) || (o.length() == 3)
                      || (o.length() == 4) || (o.length() == 7);
        }
        sum += decode(in, out);
    }
    std::cout << count1478 << ' ' << sum  << '\n';
}
