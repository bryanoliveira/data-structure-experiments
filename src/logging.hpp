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

    std::cout << "n\tops\tcomparisons\tcollisions\tload_"
                 "factor\tinserts\tremoves\tfinds\tgroups_"
                 "total\tgroups_mean\tgroups_stdev\tgroups_min\tgroups_max"
              << std::endl;
}

inline void output(uint n, uint ops, uint comparisons, uint collisions,
                   float load_factor, uint inserts, uint removes, uint finds,
                   uint groups_total, float groups_mean, float groups_stdev,
                   uint groups_min, uint groups_max) {
    if (!cfg::tsv_mode)
        return;

    std::cout << n << "\t" << ops << "\t" << comparisons << "\t" << collisions
              << "\t" << load_factor << "\t" << inserts << "\t" << removes
              << "\t" << finds << "\t" << groups_total << "\t" << groups_mean
              << "\t" << groups_stdev << "\t" << groups_min << "\t"
              << groups_max << std::endl;
}

#endif