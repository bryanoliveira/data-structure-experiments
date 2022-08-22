#include <iostream>
#include <string>
#include <sstream>

#include "config.hpp"

namespace cfg {

bool csv_mode = false;
std::string filename = "inputs/test.txt";

void load_cmdline_args(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-csv" || std::string(argv[i]) == "--csv") {
            csv_mode = true;
        }
        if (std::string(argv[i]) == "-i" || std::string(argv[i]) == "--input") {
            i++;
            filename = std::string(argv[i]);
        }
        else {
            std::cout << "Usage: ./hashmap [-csv] [-i <input file>]\n";
            std::cout << "  -csv: output in CSV format\n";
            std::cout << "  -i <input file>: input file\n";
            exit(0);
        }
    }
}


} // namespace cfg