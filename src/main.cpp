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

#include "config.hpp"
#include "hash.hpp"

int main(int argc, char **argv) {
    cfg::load_cmdline_args(argc, argv);

    // read input file and prepare buffers
    std::cout << "Reading " << cfg::filename << std::endl;
    std::ifstream infile(cfg::filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::string line;
    HashMap<int, int> *map = new HashMap<int, int>(1);

    // read the input file and execute its operations
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string op;
        int key, value;
        iss >> op >> key;

        try {
            if (op == "#") {
                std::cout << line << std::endl;
            }
            else if (op == "n") {
                map = new HashMap<int, int>(key);
            }
            else if (op == "insert") {
                iss >> value;
                map->insert(key, value);
            } else if (op == "remove") {
                map->remove(key);
            } else if (op == "find") {
                std::cout << "map[" << key << "=" << map->hash(key)
                          << "]: " << map->find(key) << std::endl;
            } else if (op == "get_load_factor") {
                std::cout << "Load factor: " << map->get_load_factor() << std::endl;
            } else if (op == "get_comparisons") {
                std::cout << "Total comparisons: " << map->get_comparisons() << std::endl;
            } else if (op == "reset_comparisons") {
                map->reset_comparisons();
                std::cout << "Total comparisons: " << map->get_comparisons() << std::endl;
            } else {
                std::cout << "Unknown operation '" << op << " -> " << key << "'" << std::endl;
            }
        } catch (const std::invalid_argument &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    infile.close();

    return 0;
}