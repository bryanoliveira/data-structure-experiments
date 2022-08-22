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

inline void output() { std::cout << std::endl; }

template <typename First, typename... Strings>
inline void output(First arg, const Strings &... rest) {
    std::cout << arg << "\t";
    output(rest...);
}

#endif