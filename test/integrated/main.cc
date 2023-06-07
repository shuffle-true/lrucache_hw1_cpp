#include <iostream>
#include <fstream>
#include <string>
#include "lru_cache.h"

int main() {
    lc::lru_cache<char, size_t> lru(4);
    lru.put('A', 1);
    lru.put('B', 1);
    lru.put('C', 1);

    std::ofstream file("output.txt");

    std::string s;

    s = "A=" + std::to_string(lru.get('A')) 
        + "\n" + "B=" + std::to_string(lru.get('B'))
        + "\n" + "C=" + std::to_string(lru.get('C'));

    file << s;

    return 0;
}