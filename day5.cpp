#include <cstdio>
#include <set>
#include <vector>

constexpr bool PART_1 = false;

constexpr int cmp(int a, int b) {
    return (b < a) - (a < b);
}

using point = std::pair<int, int>;

struct line {
    int x0, y0, x1, y1;
    
    bool contains(point p) const {
        return p.first  >= std::min(x0, x1)
            && p.first  <= std::max(x0, x1)
            && p.second >= std::min(y0, y1)
            && p.second <= std::max(y0, y1)
            && (x0 == x1 || y0 == y1 || std::abs(p.first - x0) == std::abs(p.second - y0));
    }
    
    void overlap(std::set<point> &out, line other) const {
        int dx = cmp(x1, x0);
        int dy = cmp(y1, y0);
        for (int x = x0, y = y0; ; x += dx, y += dy) {
            if (other.contains({x, y})) {
                out.emplace(x, y);
            }
            if (x == x1 && y == y1) break;
        }
    }
};

int main() {
    std::vector<line> lines;
    int x0, x1, y0, y1;
    
    while (std::scanf("%d,%d -> %d,%d", &x0, &y0, &x1, &y1) == 4) {
        if (not PART_1 || x0 == x1 || y0 == y1) {
            lines.push_back({x0, y0, x1, y1});
        }
    }
    
    std::set<point> points;
    for (std::size_t i = 0; i < lines.size(); ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            lines[i].overlap(points, lines[j]);
        }
    }
    std::printf("%d\n", int(points.size()));
}
