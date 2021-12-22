#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>
#include <numeric>

struct cuboid {
private:
    enum cuboid_axis { X, Y, Z };

    long d0[3], d1[3];

public:
    constexpr cuboid() = default;

    constexpr cuboid(long x0, long x1, long y0, long y1, long z0, long z1)
        : d0{std::min(x0, x1), std::min(y0, y1), std::min(z0, z1)},
          d1{std::max(x0, x1), std::max(y0, y1), std::max(z0, z1)} {}

    long volume() const {
        return (d1[X] - d0[X] + 1) * (d1[Y] - d0[Y] + 1) * (d1[Z] - d0[Z] + 1);
    }

    bool contains(cuboid other) const {
        return other.d0[X] >= d0[X] && other.d1[X] <= d1[X]
            && other.d0[Y] >= d0[Y] && other.d1[Y] <= d1[Y]
            && other.d0[Z] >= d0[Z] && other.d1[Z] <= d1[Z];
    }

    cuboid intersect(cuboid other) const {
        return {
            std::max(d0[X], other.d0[X]), std::min(d1[X], other.d1[X]),
            std::max(d0[Y], other.d0[Y]), std::min(d1[Y], other.d1[Y]),
            std::max(d0[Z], other.d0[Z]), std::min(d1[Z], other.d1[Z])
        };
    }

    bool intersects(cuboid other) const {
        return other.d1[X] >= d0[X] && other.d0[X] <= d1[X]
            && other.d1[Y] >= d0[Y] && other.d0[Y] <= d1[Y]
            && other.d1[Z] >= d0[Z] && other.d0[Z] <= d1[Z];
    }

    template <int D>
    bool split(long x, cuboid &lo, cuboid &hi) const {
        if (x <= d0[D] || x > d1[D]) {
            lo = *this;
            return false;
        }
        lo = hi = *this;
        lo.d1[D] = x - 1;
        hi.d0[D] = x;
        return true;
    }

    template <int D>
    void split_at_cuboid_bounds(cuboid other, std::vector<cuboid> &out) const {
        cuboid lo, hi;
        if (split<D>(other.d1[D] + 1, lo, hi)) {
            out.push_back(hi);
        }
        if (cuboid tmp = lo; tmp.split<D>(other.d0[D], lo, hi)) {
            out.push_back(hi);
        }
        out.push_back(lo);
    }

    bool subdivide_around(cuboid other, std::vector<cuboid> &res) const {
        if (not intersects(other)) {
            res.push_back(*this);
            return false;
        }

        size_t start_x = res.size();
        split_at_cuboid_bounds<0>(other, res);

        size_t start_y = res.size();
        for (size_t i = start_x; i < start_y; ++i) {
            res[i].split_at_cuboid_bounds<1>(other, res);
        }

        size_t start_z = res.size();
        for (size_t i = start_y; i < start_z; ++i) {
            res[i].split_at_cuboid_bounds<2>(other, res);
        }
        res.erase(res.begin() + ptrdiff_t(start_x), res.begin() + ptrdiff_t(start_z));
        return true;
    }

    void subtract(cuboid other, std::vector<cuboid> &res) const {
        auto before = ptrdiff_t(res.size());
        if (subdivide_around(other, res)) {
            res.erase(find_if(res.begin() + before, res.end(), [other](cuboid c) {
                return other.contains(c);
            }));
        }
    }
};

int main()
{
    constexpr cuboid limit{INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX};

    std::vector<std::pair<bool, cuboid>> input;

    char on_off[128] {};
    int x0, x1, y0, y1, z0, z1;
    while (std::scanf("%s x=%d..%d,y=%d..%d,z=%d..%d", on_off, &x0, &x1, &y0, &y1, &z0, &z1) > 0) {
        if (cuboid cube{x0, x1, y0, y1, z0, z1}; cube.intersects(limit)) {
            input.emplace_back(on_off[1] == 'n', cube.intersect(limit));
        }
    }

    std::vector<cuboid> state, tmp;
    long volume = 0;

    for (size_t i = 0; i < input.size(); ++i) {
        if (not input[i].first) continue;

        state = {input[i].second};
        for (size_t j = i + 1; j < input.size(); ++j) {
            tmp.clear();
            for (cuboid c : state) {
                c.subtract(input[j].second, tmp);
            }
            state = move(tmp);
        }

        volume += std::accumulate(state.begin(), state.end(), 0l, [](long v, cuboid c) {
            return v + c.volume();
        });
    }

    std::printf("%ld\n", volume);
}
