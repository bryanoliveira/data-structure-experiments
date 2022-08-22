#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <string>

namespace cfg {

extern bool tsv_mode;
extern std::string filename;

void load_cmdline_args(int argc, char **argv);

} // namespace cfg

#endif