#include <iostream>
#include <string>
#include <algorithm>

template <bool Intersection>
std::string set_op(std::string a, const std::string &b) {
    a.erase(std::remove_if(a.begin(), a.end(), [&b](char c) {
        return (b.find(c) == std::string::npos) == Intersection; 
    }), a.end());
    return a;
}

std::string minus(std::string a, const std::string &b) {
    return set_op<false>(std::move(a), b);
}

std::string isect(std::string a, const std::string &b) {
    return set_op<true>(std::move(a), b);
}

std::size_t decode(std::string (&a)[10], std::string (&nums)[4]) {
    std::sort(a, std::end(a), [](const auto &l, const auto &r){
        return l.length() < r.length();
    });
    
    auto hz = isect(isect(a[3], a[4]), a[5]);                    // 2 ^ 3 ^ 5

    char hi = minus(a[1], a[0]).front();                         // 7 - 1
    char tl = minus(minus(a[2], hz), a[0]).front();              // 4 - hz - 1
    char md = minus(minus(a[2], a[0]), {tl}).front();            // 4 - 1 - {tl}
    char lo = minus(hz, {hi, md}).front();                       // hz - {hi, md}
    char bl = minus(minus(minus(a[9], hz), a[0]), {tl}).front(); // 8 - hz - 1 - tl
    char br = minus(minus(isect(isect(a[6], a[7]), a[8]), hz), {tl}).front(); // 0 ^ 6 ^ 9 - hz - {tl}
    char tr = minus(a[0], {br}).front();                         // 1 - {br}
    
    a[0] = {hi, tl, tr, bl, br, lo};
    a[1] = {tr, br};
    a[2] = {hi, lo, md, tr, bl};
    a[3] = {hi, lo, md, tr, br};
    a[4] = {tl, tr, md, br};
    a[5] = {hi, lo, md, tl, br};
    a[6] = {hi, lo, md, tl, bl, br};
    a[7] = {hi, tr, br};
    a[8] = {hi, lo, md, tl, tr, bl, br};
    a[9] = {hi, lo, md, tl, tr, br};
    
    for (std::string &s : a) {
        std::sort(s.begin(), s.end());
    }
    
    std::size_t val = 0;
    for (std::string &n : nums) {
        std::sort(n.begin(), n.end());
        val *= 10;
        val += std::find(a, std::end(a), n) - a;
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
        std::cin >> sep;
        if (std::cin.fail()) {
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
