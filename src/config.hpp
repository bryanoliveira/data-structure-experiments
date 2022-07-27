#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <string>
#include "types.hpp"

namespace config {

// global configs
extern uint n;
extern std::string inputFileName;

void load_file();
void load_cmd(const int argc, char **const argv);

} // namespace config

#endif