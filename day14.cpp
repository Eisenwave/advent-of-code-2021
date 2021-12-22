#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

map<string, size_t> step(map<string, size_t> counts, map<string, char> &rules) {
    map<string, size_t> result;
    for (const auto &[ele, count] : counts) {
        auto ruleit = rules.find(ele);
        if (ruleit != rules.end()) {
            result[string{ele[0], ruleit->second}] += count;
            result[string{ruleit->second, ele[1]}] += count;
        }
        else {
            result[ele] += count;
        }
    }
    return result;
}

int main()
{
    string templ;
    getline(cin, templ).ignore();

    map<string, char> rules;
    string a; char b;
    while ((cin >> a).ignore(4) >> b) {
        rules.emplace(a, b);
    }

    map<string, size_t> counts;
    for (size_t i = 0; i + 1 < templ.size(); ++i) {
        counts[string{templ[i], templ[i + 1]}]++;
    }
    for (size_t i = 0; i < 40; ++i) {
        counts = step(counts, rules);
    }
    map<char, size_t> histo;
    for (auto [k, v] : counts) {
        histo[k[0]] += v;
        histo[k[1]] += v;
    }

    auto [lo, hi] = ranges::minmax_element(histo, less{}, [](auto &p) {return p.second;});
    size_t res = hi->second - lo->second;

    cout << res / 2 + res % 2 << endl;
}
