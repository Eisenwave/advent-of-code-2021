#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>

struct cuboid {
private:
    enum cuboid_axis { X, Y, Z };

    long d0[3], d1[3];

public:
    constexpr cuboid() = default;

    constexpr cuboid(long x0, long x1, long y0, long y1, long z0, long z1)
        : d0{x0, y0, z0}, d1{x1, y1, z1} {}

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

struct cuboids {
    std::vector<cuboid> state, tmp0, tmp1;

    void insert(cuboid other) {
        tmp0 = {other};
        for (cuboid c : state) {
            if (tmp0.empty()) {
                return;
            }
            tmp1.clear();
            for (cuboid t : tmp0) {
                t.subtract(c, tmp1);
            }
            swap(tmp0, tmp1);
        }
        state.insert(state.end(), tmp0.begin(), tmp0.end());
    }

    void erase(cuboid other) {
        tmp0.clear();
        for (cuboid c : state) {
            c.subtract(other, tmp0);
        }
        state = move(tmp0);
    }

    long volume() const {
        long sum = 0;
        for (cuboid c : state) {
            sum += c.volume();
        }
        return sum;
    }

};

template <typename T>
void sort2(T &a, T &b) {
    if (b < a) {
        std::swap(a, b);
    }
}

int main()
{
    constexpr cuboid limit{INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX};

    cuboids cubes;

    char on_off[128] {};
    int x0, x1, y0, y1, z0, z1;
    while (scanf("%s x=%d..%d,y=%d..%d,z=%d..%d", on_off, &x0, &x1, &y0, &y1, &z0, &z1)>0) {
        sort2(x0, x1);
        sort2(y0, y1);
        sort2(z0, z1);

        cuboid cube{x0, x1, y0, y1, z0, z1};
        if (not cube.intersects(limit)) {
            continue;
        }
        cube = cube.intersect(limit);

        if (on_off[1] == 'n') {
            cubes.insert(cube);
        }
        else {
            cubes.erase(cube);
        }
    }
    printf("%ld\n", cubes.volume());
}
