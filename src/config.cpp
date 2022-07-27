#include <boost/program_options.hpp>
#include <iostream>

#include "config.hpp"

namespace po = boost::program_options;

namespace config {

uint n;
std::string inputFileName;

void load_file() {}
void load_cmd(const int argc, char **const argv) {
    po::options_description description("Usage");

    description.add_options()("help,h", "Display this help message") //
        ("number,n", po::value<uint>(), "Number of elements")        //
        ("input,i", po::value<std::string>(), "Input file name");    //

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(description).run(),
              vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << description << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (vm.count("number"))
        n = vm["number"].as<uint>();
    if (vm.count("file"))
        inputFileName = vm["input"].as<std::string>();
}

} // namespace config