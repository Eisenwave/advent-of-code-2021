#include <map>
#include <iostream>

constexpr int START[] {9, 6};

using namespace std;

int rand() {
    static int die = 99;
    return (++die %= 100) + 1;
}

void part1()
{
    int pos[] {START[0], START[1]};
    int score[] {0, 0};
    int rolls = 0;

    while (true) {
        for (int i : {0, 1}) {
            pos[i] += rand() + rand() + rand();
            pos[i] = (pos[i] - 1) % 10 + 1;
            rolls += 3;
            score[i] += pos[i];
            if (score[i] >= 1000) {
                cout << score[i ^ 1] << " * " << rolls << " = " << score[i ^ 1] * rolls << endl;
                return;
            }
        }
    }
}

struct state {
    array<size_t, 2> pos;
    array<size_t, 2> score;
    auto operator<=>(const state&) const = default;
};

state advance(state s, size_t r, size_t i) {
    size_t step = r % 3 + r / 3 % 3 + r / 9 % 3 + 3;
    s.pos[i] = (s.pos[i] + step - 1) % 10 + 1;
    s.score[i] += s.pos[i];
    return s;
}

void part2() {
    state initial{{START[0], START[1]}, {0, 0}};
    map<state, size_t> multiverse{{initial, 1}};
    size_t wins[2] {};

    while (not multiverse.empty()) {
        map<state, size_t> nue;
        for (auto &[s, count] : multiverse) {
            for (size_t q = 0; q < 3 * 3 * 3; ++q) {
                state s0 = advance(s, q, 0);
                if (s0.score[0] >= 21) {
                    wins[0] += count;
                    continue;
                }
                for (size_t p = 0; p < 3 * 3 * 3; ++p) {
                    state s1 = advance(s0, p, 1);
                    if (s1.score[1] >= 21) {
                        wins[1] += count;
                        continue;
                    }
                    nue[s1] += count;
                }
            }
        }
        multiverse = std::move(nue);
    }

    cout << max(wins[0], wins[1]) << ' ' << min(wins[0], wins[1]) << endl;
}

int main()
{
    part1();
    part2();
}
