#include <iostream>
#include <algorithm>

int main() {
    std::string word;
    int amount, x = 0, y = 0, aim = 0;
    
    while (std::cin >> word >> amount) {
        aim += ((word == "down") - (word == "up")) * amount;
        x += (word == "forward") * amount;
        y = std::max(0, y + (word == "forward") * aim * amount);
    }
    
    std::cout << x * y << '\n';
}
