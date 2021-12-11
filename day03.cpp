#include <iostream>
#include <vector>

unsigned parse_bin(const std::string &s) {
    unsigned res = 0;
    for (char c : s) {
        res <<= 1;
        res |= c == '1';
    }
    return res;
}

void task1(const std::vector<std::string> &inputs) {
    std::vector<unsigned> accum(inputs.front().size());
    
    for (const auto &num : inputs) {
        for (unsigned i = 0; i < accum.size(); ++i) {
            accum[i] += num[i] == '1';
        }
    }
    
    unsigned gamma = 0;
    unsigned epsilon = 0;
    for (unsigned a : accum) {
        gamma <<= 1;
        gamma |= a * 2 >= inputs.size();
        
        epsilon <<= 1;
        epsilon |= a * 2 < inputs.size();
    }
    
    std::cout << "TASK 1: " << gamma << " * " << epsilon << " = " << gamma * epsilon << '\n';
}

unsigned solve2(const std::vector<std::string> &inputs, bool is_co2) {
    unsigned bit_size = inputs.front().size();   
    std::vector<bool> filter(inputs.size());
    unsigned res = 0;
    
    for (unsigned i = 0; i <= bit_size; ++i) {
        unsigned accum = 0;
        unsigned count = 0;
        unsigned candi = 0;
        
        for (unsigned n = 0; n < inputs.size(); ++n) {
            if (not filter[n]) {
                accum += i != bit_size && inputs[n][i] == '1';
                count += 1;
                candi = n;
            }
        }
        
        if (count == 1) {
            return candi;
        }
        else if (i != bit_size) {
            bool expected = (accum * 2 >= count) ^ is_co2;
            for (unsigned n = 0; n < inputs.size(); ++n) {
                if ((inputs[n][i] == '1') != expected) {
                    filter[n] = true;
                }
            }
        }
        else {
            throw "could not find solution";
        }
    }
    throw "unreachable";
}

void task2(const std::vector<std::string> &inputs) {
    unsigned oxy_res = solve2(inputs, false);
    unsigned co2_res = solve2(inputs, true);
    unsigned oxy_par = parse_bin(inputs[oxy_res]);
    unsigned co2_par = parse_bin(inputs[co2_res]);
    
    std::cout << "TASK 2: " << oxy_par << " * " << co2_par << " = " << oxy_par * co2_par << '\n';
}

int main() {
    std::vector<std::string> inputs;
    for (std::string num; std::cin >> num;) {
        inputs.push_back(std::move(num));
    }
    
    task1(inputs);
    task2(inputs);
}
