#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

unsigned basin_size(vector<int> &v,
                    unsigned w, unsigned h,
                    unsigned x, unsigned y) {
    unsigned i = y * w + x;
    if (v[i] < 0 || v[i] == 9) {
        return 0;
    }
    v[i] = -1;
    
    unsigned sum = 1;
    if (x != 0 && v[i] < v[i - 1]) {
        sum += basin_size(v, w, h, x - 1, y);
    }
    if (x + 1 != w && v[i] < v[i + 1]) {
        sum += basin_size(v, w, h, x + 1, y);
    }
    if (y != 0 && v[i] < v[i - w]) {
        sum += basin_size(v, w, h, x, y - 1);
    }
    if (y + 1 != h && v[i] < v[i + w]) {
        sum += basin_size(v, w, h, x, y + 1);
    }
    return sum;
}

int main() {
    vector<int> v;
    unsigned w = 0;
    
    for (string line; getline(cin, line);) {
        w = line.length();
        for (unsigned c : line) {
            v.push_back(c - '0');
        }
    }
    unsigned h = v.size() / w;
    
    unsigned sum = 0;
    vector<unsigned> sizes;
    
    for (unsigned i = 0; i < v.size(); ++i) {
        unsigned x = i % w;
        unsigned y = i / w;
        bool is_low = (x == 0     || v[i] < v[i - 1]) &&
                      (x + 1 == w || v[i] < v[i + 1]) &&
                      (y == 0     || v[i] < v[i - w]) &&
                      (y + 1 == h || v[i] < v[i + w]);
        if (is_low) {
            sum += v[i] + 1;
            sizes.push_back(basin_size(v, w, h, x, y));
        }
    }
    sort(sizes.begin(), sizes.end(), greater{});
    
    cout << sum << ' ' << sizes[0] * sizes[1] * sizes[2] << endl;
}
