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
 *       - the 'config' namespace doesn't follow this as the 'config::' prefix
 *         is always made explicit
 *  - methods are snake_cased
 *  - Macros are UPPER_CASED (e.g. CUDA_ASSERT())
 */

#include <iostream>
#include <stdexcept>

#include "config.hpp"
#include "hash.hpp"

int main(int argc, char **argv) {
    config::load_cmd(argc, argv);
    config::load_file();

    Hash<int, int> map(config::n);

    std::cout << "n: " << map.size() << std::endl;
    map.insert(12312, 111);
    std::cout << "n: " << map.size() << std::endl;
    map.insert(3512, 222);
    std::cout << "n: " << map.size() << std::endl;

    std::cout << "map[3512]: " << map[3512] << std::endl;

    map.remove(3512);
    std::cout << "n: " << map.size() << std::endl;
    try {
        std::cout << "map[3512]: " << map[3512] << std::endl;
    } catch (const std::runtime_error &e) {
        std::cout << "map[3512]: " << e.what() << std::endl;
    }

    return 0;
}