#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using ull = unsigned long long;

void foldv(vector<vector<int>> &paper, ull &w, ull &h, ull at) {
    for (ull y = 0; y < h; ++y) {
        for (ull i = 0; i < w - at; ++i) {
            paper[y][at-i] |= paper[y][at+i];
        }
    }
    w -= w - at;
}

void foldh(vector<vector<int>> &paper, ull &w, ull &h, ull at) {
    for (ull x = 0; x < w; ++x) {
        for (ull i = 0; i < h - at; ++i) {
            paper[at-i][x] |= paper[at+i][x];
        }
    }
    h -= h - at;
}

void print(vector<vector<int>> &paper, ull w, ull h) {
    for (ull j = 0; j < h; ++j) {
        for (ull i = 0; i < w; ++i) {
            cout << (paper.at(j).at(i) ? '#' : '.');
        }
        cout << endl;
    }
}

int main()
{
    vector<pair<ull,ull>> dots;
    vector<vector<int>> paper;
    ull width = 0, height = 0;

    string w;
    for (ull x, y; cin >> w;) {
        if (w == "fold") {
            if (paper.empty()) {
                paper = {height, vector<int>(width)};
                for (auto [x, y] : dots) {
                    paper[y][x] = 1;
                }
            }
            cin >> w >> w;
            (w.front() == 'x' ? foldv : foldh)(paper, width, height, stoull(w.substr(2)));
        }
        else {
            stringstream st{w};
            getline(st, w, ',') >> y;
            x = stoull(w);
            dots.emplace_back(x, y);

            width = max(width, x + 1);
            height = max(height, y + 1);
        }
    }
    print(paper, width, height);
}
