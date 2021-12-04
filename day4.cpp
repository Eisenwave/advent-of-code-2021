#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <vector>

std::vector<int> parse(const std::string &line, char sep) {
    std::vector<int> result;
    std::istringstream stream{line};
    
    for (std::string elem; std::getline(stream, elem, sep); ) {
        result.push_back(int(std::stoi(elem)));
    }
    return result;
}

int check_win(int board[25], int x, int y, bool vertical) {
    for (int i = 0; i < 5; ++i) {
        if (board[vertical ? i * 5 + x : y * 5 + i] >= 0) {
            return -1;
        }
    }
    int sum = 0;
    for (int i = 0; i < 25; ++i) {
        sum += (board[i] >= 0) * board[i];
    }
    return sum;
}

int bingo(int board[25], int input) {
    for (int i = 0; i < 25; ++i) {
        if (board[i] != input) {
            continue;
        }
        board[i] = -1;
        for (bool type : {false, true}) {
            if (int sum = check_win(board, i % 5, i / 5, type); sum >= 0) {
                return sum * input;
            }
        }
    }
    return -1;
}

std::pair<int, int> bingo(int board[25], const int inputs[], int rounds) {    
    for (int i = 0; i < rounds; ++i) {
        if (int result = bingo(board, inputs[i]); result != -1) {
            return {i + 1, result};
        }
    }
    throw "unsolvable board";
}

int main() {
    std::string line;
    std::getline(std::cin, line);
    std::vector<int> inputs = parse(line, ',');
    
    std::pair<int, int> first{inputs.size(), 0};
    std::pair<int, int> last{0, 0};
    
    while (std::getline(std::cin, line)) {
        int board[25];
        for (int &e : board) {
            std::cin >> e;
        }
        if (std::cin.ignore().fail()) {
            break;
        }
        auto result = bingo(board, inputs.data(), inputs.size());
        first = std::min(first, result);
        last = std::max(last, result);
    }
    
    std::cout << "FIRST after " << first.first << " rounds, with " << first.second << '\n';
    std::cout << "LAST  after " << last.first << " rounds, with " << last.second << '\n';
}
