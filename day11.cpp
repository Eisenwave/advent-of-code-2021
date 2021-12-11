#include <iostream>
#include <string>

using namespace std;
using ll = long long;

ll flash_at(ll (&map)[100], ll y, ll x) {
    ll i = y * 10 + x;
    if (++map[i] != 10) {
        return 0;
    }
    ll sum = 1;
    for (ll dy = -1; dy <= 1; ++dy) {
        for (ll dx = -1; dx <= 1; ++dx) {
            if ((dx != 0 || dy != 0) && x + dx >= 0 && x + dx < 10 && y + dy >= 0 && y + dy < 10) {
                sum += flash_at(map, y + dy, x + dx);
            }
        }
    }
    return sum;
}

ll flash(ll (&map)[100]) {
    ll sum = 0;
    for (ll y = 0; y < 10; ++y) {
        for (ll x = 0; x < 10; ++x) {
            sum += flash_at(map, y, x);
        }
    }
    for (ll &o : map)
        if (o > 9)
            o = 0;
    return sum;
}

int main() {
    ll map[100], i = 0;
    for (char c; cin >> c;) {
        map[i++] = c - '0';
    }
    
    ll flashes100 = 0;
    for (ll j = 0; ; ++j) {
        ll f = flash(map);
        flashes100 += (j < 100) * f;
        if (f == 100) {
            cout << flashes100 << ' ' << j + 1 << '\n';
            break;
        }
    }
}
