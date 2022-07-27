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
#include "config.hpp"

int main(int argc, char **argv) {
    config::load_cmd(argc, argv);
    config::load_file();

    std::cout << "Hello, World!" << std::endl;
    std::cout << "N: " << config::n << std::endl;

    return 0;
}