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

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "config.hpp"
#include "hash.hpp"
#include "logging.hpp"

int main(int argc, char **argv) {
    cfg::load_cmdline_args(argc, argv);
    output_header();

    // read input file and prepare buffers
    log("Reading ", cfg::filename);
    std::ifstream infile(cfg::filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::string line;
    uint n_ops = 0;
    uint n_inserts = 0;
    uint n_removes = 0;
    uint n_finds = 0;
    HashMap<int, int> *map = new HashMap<int, int>(1);

    // read the input file and execute its operations
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string op;
        int key, value;
        iss >> op;

        if (op == "#") {
            log(line);
        } else if (op == "m") {
            iss >> key;
            map = new HashMap<int, int>(key);
        } else if (op == "insert") {
            iss >> key >> value;
            map->insert(key, value);
            // update stats
            n_ops++;
            n_inserts++;
            log("Insert ", key);
        } else if (op == "remove") {
            iss >> key;
            map->remove(key);
            // update stats
            n_ops++;
            n_removes++;
            log("Remove ", key);
        } else if (op == "find") {
            iss >> key;
            log("Find ", key);
            log("map[", key, "=", map->hash(key), "]: ", map->find(key));
            // update stats
            n_ops++;
            n_finds++;
        } else if (op == "get_load_factor") {
            log("Load factor: ", map->get_load_factor());
        } else if (op == "get_comparisons") {
            log("Total collisions: ", map->get_collisions());
        } else if (op == "get_comparisons") {
            log("Total comparisons: ", map->get_comparisons());
        } else if (op == "get_grouping_stats") {
            auto stats = map->get_grouping_stats();
            log("Grouping stats: {total: ", stats.total, ", mean: ", stats.mean,
                ", stdev: ", stats.stdev, ", min: ", stats.min,
                ", max: ", stats.max, "}");
        } else if (op == "reset_comparisons") {
            map->reset_comparisons();
            log("Total comparisons: ", map->get_comparisons());
        } else if (op == "stats") {
            auto stats = map->get_grouping_stats();
            output(map->get_size(), n_ops, map->get_comparisons(), map->get_operations(),
                   map->get_collisions(), map->get_load_factor(), n_inserts,
                   n_removes, n_finds, stats.total, stats.mean, stats.stdev,
                   stats.min, stats.max);
        } else if (op == "render") {
            map->render();
            std::cout << std::endl;
        } else {
            std::cout << "Unknown operation '" << op << "'" << std::endl;
            throw std::invalid_argument("Unknown operation");
        }
    }

    infile.close();

    return 0;
}