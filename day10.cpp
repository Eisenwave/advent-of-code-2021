#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

char find_corrupt(string s, unsigned long long &complete) {
    complete = 0;
    vector<char> stack;
    
    for (char c : s) {
        switch (c) {
            case '<':
            case '(':
            case '[':
            case '{':
                stack.push_back(c); break;
            case ')':
                if (stack.empty() || stack.back() != '(') return c;
                stack.pop_back(); break;
            case ']':
                if (stack.empty() || stack.back() != '[') return c;
                stack.pop_back(); break;
            case '}':
                if (stack.empty() || stack.back() != '{') return c;
                stack.pop_back(); break;
            case '>':
                if (stack.empty() || stack.back() != '<') return c;
                stack.pop_back(); break;
        }
    }
    if (not stack.empty()) {
        do {
            complete *= 5;
            switch (stack.back()) {
                case '(': complete += 1; break;
                case '[': complete += 2; break;
                case '{': complete += 3; break;
                case '<': complete += 4; break;
            }
            stack.pop_back();
        } while (not stack.empty());
        return 1;
    }
    return 0;
}

int main() {
    vector<unsigned long long> scores;
    unsigned long long sum1 = 0, complete = 0;
    for (string s; getline(cin, s);) {
        switch (find_corrupt(s, complete)) {
            case 0: break;
            case 1: scores.push_back(complete); break;
            case ')': sum1 += 3; break;
            case ']': sum1 += 57; break;
            case '}': sum1 += 1197; break; 
            case '>': sum1 += 25137; break;
        }
    }
    sort(scores.begin(), scores.end());
    cout << sum1 << ' ' << scores[scores.size() / 2] << endl;
}
