#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>

struct cuboid {
private:
    long x0, y0, z0, x1, y1, z1;

public:
    constexpr cuboid(long x0, long x1, long y0, long y1, long z0, long z1)
        : x0{std::min(x0, x1)}, y0{std::min(y0, y1)}, z0{std::min(z0, z1)},
          x1{std::max(x0, x1)}, y1{std::max(y0, y1)}, z1{std::max(z0, z1)} {}

    long volume() const {
        return (x1 - x0 + 1) * (y1 - y0 + 1) * (z1 - z0 + 1);
    }

    cuboid intersect(cuboid other) const {
        return {
            std::max(x0, other.x0), std::min(x1, other.x1),
            std::max(y0, other.y0), std::min(y1, other.y1),
            std::max(z0, other.z0), std::min(z1, other.z1)
        };
    }

    bool intersects(cuboid other) const {
        return other.x1 >= x0 && other.x0 <= x1
            && other.y1 >= y0 && other.y0 <= y1
            && other.z1 >= z0 && other.z0 <= z1;
    }
};

std::vector<cuboid>& make_intersect(std::vector<cuboid>& cuboids, cuboid c) {
    std::erase_if(cuboids, [c](const cuboid &o) { return not c.intersects(o); });
    for (cuboid &o : cuboids) { o = c.intersect(o); }
    return cuboids;
}

long union_volume(const std::vector<cuboid> &cuboids) {
    if (cuboids.empty()) return 0;
    cuboid tail = cuboids.back();
    std::vector<cuboid> head(cuboids.begin(), cuboids.end() - 1);
    long result = tail.volume() + union_volume(head);
    return result - union_volume(make_intersect(head, tail));
}

long subtraction_volume(cuboid head, std::vector<cuboid> minus) {
    return head.volume() - union_volume(make_intersect(minus, head));
}

int main()
{
    constexpr cuboid limit{INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX};

    std::vector<cuboid> cuboids;
    std::vector<bool> cuboids_on;

    char on_off[9] {};
    int x0, x1, y0, y1, z0, z1;
    while (std::scanf("%8s x=%d..%d,y=%d..%d,z=%d..%d", on_off, &x0, &x1, &y0, &y1, &z0, &z1) > 0) {
        if (cuboid cube{x0, x1, y0, y1, z0, z1}; cube.intersects(limit)) {
            cuboids.emplace_back(cube.intersect(limit));
            cuboids_on.push_back(on_off[1] == 'n');
        }
    }

    long volume = 0;
    for (size_t i = 0; i < cuboids.size(); ++i) {
        if (cuboids_on[i]) {
            volume += subtraction_volume(cuboids[i], {cuboids.begin() + long(i + 1), cuboids.end()});
        }
    }

    std::printf("%ld\n", volume);
}
