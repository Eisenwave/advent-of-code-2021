#include <map>
#include <string>
#include <set>
#include <iostream>
#include <bitset>

using namespace std;

using point = pair<int, int>;

set<point> step(bitset<512> algo, const set<point> &points, bool &inf,
                int &x_lo, int &y_lo, int &x_hi, int &y_hi) {
    set<point> result;
    x_lo -= 1; y_lo -= 1; x_hi += 1; y_hi += 1;
    for (int y = y_lo; y <= y_hi; ++y) {
        for (int x = x_lo; x <= x_hi; ++x) {
            size_t index = 0;
            for (int yi = y - 1; yi <= y + 1; ++yi) {
                for (int xi = x - 1; xi <= x + 1; ++xi) {
                    index <<= 1;
                    index |= xi <= x_lo || xi >= x_hi || yi <= y_lo || yi >= y_hi ? inf : points.contains({xi, yi});
                }
            }
            if (algo.test(index)) {
                result.emplace(x, y);
            }
        }
    }
    inf = algo.test(511 * inf);
    return result;
}

int main()
{
    string line(512, 0);
    for (size_t i = 512; i--;) {
        cin >> line[i];
    }
    bitset<512> algo(line, 0, 512, '.', '#');
    cin.ignore(2);

    set<point> points;
    int x_lo = 0, y_lo = 0, x_hi = 0, y_hi = 0;
    for (int y = 0; getline(cin, line) && not line.empty(); ++y) {
        for (int x = 0; x < int(line.size()); ++x) {
            if (line[size_t(x)] == '#') {
                points.emplace(x, y);
            }
        }
        x_hi = int(line.size() - 1);
        y_hi = y;
    }

    bool inf = false;
    for (int i = 0; i < 50; ++i) {
        points = step(algo, points, inf, x_lo, y_lo, x_hi, y_hi);
    }

    cout << points.size() << endl;
}
