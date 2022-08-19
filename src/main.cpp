/**
 * Using ISO C++ 17 (C++ 11 may be compatible)
 *
 * Conventions (a variation of STL/Boost Style Guides):
 *  - use spaces instead of tabs
 *  - indent with 4 spaces
 *  - variables are camelCased
 *    - params are prefixed with p (e.g. pFillProb)
 *    - member variables are prefixed with m (e.g. mFillProb)
 *    - globals are prefixed with g (e.g. gDisplay)
 *  - methods are snake_cased
 *  - Macros are UPPER_CASED (e.g. CUDA_ASSERT())
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "hash.hpp"

int main(int argc, char **argv) {
    // load input file or use a default
    std::string filename = "inputs/test.txt";
    if (argc >= 2)
        filename = argv[1];


    // read input file and prepare buffers
    std::cout << "Reading " << filename << std::endl;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::string line;

    // read n & instantiate the hashmap
    std::getline(infile, line);
    HashMap<int, int> map(std::stoi(line));

    // read the input file and execute its operations
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string op;
        int key, value;
        iss >> op >> key;

        try {
            if (op == "insert") {
                iss >> value;
                map.insert(key, value);
            } else if (op == "remove") {
                map.remove(key);
            } else if (op == "find") {
                std::cout << "map[" << key << "=" << map.hash(key)
                          << "]: " << map.find(key) << std::endl;
            } else {
                throw std::runtime_error("Unknown operation");
            }
        } catch (const std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}