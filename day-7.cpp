#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
#include <numeric>

using ll = signed long long;

ll sum_n(ll n) {
    return n * (n + 1) / 2;
}

template <typename D>
ll cost(const std::vector<ll> &v, ll pos, D distance) {
    return std::accumulate(v.begin(), v.end(), ll{0}, [=](ll a, ll b) {
        return a + std::abs(distance(pos, b));
    });
}

void part1(std::vector<ll> &v) {
    std::sort(v.begin(), v.end());
    std::cout << cost(v, v[v.size() / 2], [](ll a, ll b) { return a - b; }) << '\n';
}

void part2(std::vector<ll> &v) {
    auto [lo, hi] = std::minmax_element(v.begin(), v.end());
    ll min_cost = INT_MAX;
    for (ll i = *lo; i <= *hi; ++i) {
        ll cost_i = cost(v, i, [](ll a, ll b) { return sum_n(std::abs(a - b)); });
        min_cost = std::min(min_cost, cost_i);
    }
    std::cout << min_cost << '\n';
}

int main() {
    std::vector<ll> v;
    for (ll x; (std::cin >> x).ignore(); ) {
        v.push_back(x);
    }
    part1(v);
    part2(v);
}
