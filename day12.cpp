#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cctype>

using namespace std;

#ifdef PART1
bool is_double_smol(const vector<string> &) { return true; }
#else
bool is_double_smol(const vector<string> &path) {
    for (string s : path) {
        if (islower(s.front()) && count(path.begin(), path.end(), s) > 1)
            return true;
    }
    return false;
}
#endif

int main() {
    multimap<string, string> edges;
    set<vector<string>> paths;
    set<vector<string>> result;
    
    for (string start, end; getline(getline(cin, start, '-'), end);) {
        edges.emplace(start, end);
        edges.emplace(end, start);
    }

    vector<vector<string>> q{{{"start"}}};
    do {
        auto curr = q.back();
        q.pop_back();
        
        for (const auto &[k, v] : edges) {
            if (k != curr.back() || v == "start") {
                continue;
            }
            if (islower(v.front()) && count(curr.begin(), curr.end(), v) + is_double_smol(curr) >= 2) {
                continue;
            }
            
            vector<string> next = curr;
            next.push_back(v);
            if (paths.count(next) != 0) {
                continue;
            }
            paths.insert(next);
            if (v == "end") {
                result.insert(next);
            }
            else {
                q.push_back(next);
            }
        }
        
    } while (not q.empty());
    
    cout << result.size() << endl;
}
