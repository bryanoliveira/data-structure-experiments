#ifndef LOGGING_HPP_
#define LOGGING_HPP_

#include <iostream>
#include "config.hpp"
#include "logging.hpp"

//// LOGS

inline void __log() { std::cout << std::endl; }

template <typename First, typename... Strings>
inline void __log(First arg, const Strings &... rest) {
    std::cout << arg;
    __log(rest...);
}

template <typename... Strings> inline void log(const Strings &... args) {
    if (cfg::tsv_mode)
        return;

    __log(args...);
}

//// TSV OUTPUTS

inline void output_header() {
    if (!cfg::tsv_mode)
        return;

    std::cout << "n\tops\tcomparisons\tload_factor\tinserts\tremoves\tfinds" << std::endl;
}

inline void output(uint n, uint ops, uint comparisons, float load_factor,
                   uint inserts, uint removes, uint finds) {
    if (!cfg::tsv_mode)
        return;

    std::cout << n << "\t" << ops << "\t" << comparisons << "\t" << load_factor
              << "\t" << inserts << "\t" << removes << "\t" << finds
              << std::endl;
}

#endif