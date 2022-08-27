#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <limits.h>
#include <numeric>
#include <vector>

#include "hash.hpp"
#include "logging.hpp"

#define PROBE_PREP(key, k)                                                     \
    uint hk = hash(key);                                                       \
    k = hk;                                                                    \
    uint i = 1;
#ifdef LINEAR_PROBING
#define PROBE_STEP(k)                                                          \
    k = (hk + i) % m;                                                          \
    i++;                                                                       \
    if (k == hk)                                                               \
        throw std::runtime_error("Linear probing resulted in a loop.");
#else // quadratic probing
#define PROBE_STEP(k)                                                          \
    k = (hk + i * i) % m;                                                      \
    i++;                                                                       \
    if (k == hk)                                                               \
        throw std::runtime_error("Quadratic probing resulted in a loop.");
#endif

#define TKV template <typename TK, typename TV>

TKV HashMap<TK, TV>::HashMap(const uint m) {
    log("Instantiating HashMap expecting max of ", m, " elements...");
#ifdef LINEAR_PROBING
    log("Using linear probing.");
#else // linear probing
    log("Using quadratic probing.");
#endif
    HashMap::m = m;
    HashMap::table = new HashNode[m];
}

TKV HashMap<TK, TV>::~HashMap() { delete[] HashMap::table; }

TKV uint HashMap<TK, TV>::get_size() { return HashMap::n; }

TKV uint HashMap<TK, TV>::get_comparisons() { return HashMap::comparisons; }

TKV void HashMap<TK, TV>::reset_comparisons() { HashMap::comparisons = 0; }

TKV float HashMap<TK, TV>::get_load_factor() {
    return HashMap::n / (float)HashMap::m;
}

TKV Stats HashMap<TK, TV>::get_grouping_stats() {
    // calculate group sizes
    std::vector<uint> sizes;
    uint group_size = 0;
    for (uint i = 0, last_hash = 0; i < HashMap::m; i++) {
        if (hash(table[i].key) != last_hash && group_size > 0) {
            sizes.push_back(group_size);
            group_size = 0;
            last_hash = hash(table[i].key);
        }

        group_size += table[i].status != FREE;
    }
    if (group_size > 0) {
        sizes.push_back(group_size);
    }

    // generate stats
    Stats stats;
    stats.total = sizes.size();
    if (stats.total > 0) {
        stats.min = sizes[0];
        stats.max = sizes[0];
        for (uint i : sizes) {
            stats.mean += i;
            stats.stdev += (i - stats.mean) * (i - stats.mean);
            if (i < stats.min)
                stats.min = i;
            if (i > stats.max)
                stats.max = i;
        }

        stats.mean /= stats.total;
        stats.stdev /= stats.total;
        stats.stdev = sqrt(stats.stdev);
    }

    return stats;
}

TKV uint HashMap<TK, TV>::hash(const TK key) { return key % m; }

TKV TV &HashMap<TK, TV>::operator[](const TK key) { return find(key); }

TKV TV &HashMap<TK, TV>::find(const TK key) {
    uint k;
    PROBE_PREP(key, k);
    HashMap::comparisons++;
    while (table[k].status != FREE) {
        if (table[k].status == OCCUPIED && table[k].key == key)
            return table[k].value;

        HashMap::comparisons++;
        PROBE_STEP(k);
    }

    throw std::invalid_argument("Key not found!");
}

TKV void HashMap<TK, TV>::insert(const TK key, const TV value) {
    if (HashMap::n == HashMap::m)
        throw std::length_error("Cannot insert! HashMap is full!");

    uint k;
    PROBE_PREP(key, k);
    HashMap::comparisons++;
    while (table[k].status == OCCUPIED) {
        HashMap::comparisons++;
        PROBE_STEP(k);
    }

    table[k].status = OCCUPIED;
    table[k].key = key;
    table[k].value = value;
    n++;
}

TKV void HashMap<TK, TV>::remove(const TK key) {
    uint k;
    PROBE_PREP(key, k);
    HashMap::comparisons++;
    while (table[k].status != FREE) {
        if (table[k].status == OCCUPIED && table[k].key == key) {
            table[k].status = DELETED;
            n--;
            return;
        }

        HashMap::comparisons++;
        PROBE_STEP(k);
    }

    throw std::invalid_argument("Key not found!");
}

TKV void HashMap<TK, TV>::render() {
    for (uint i = 0; i < HashMap::m; i++) {
        if (table[i].status == OCCUPIED)
            std::cout << "█";
        else
            std::cout << "░";
    }
}

// instantiate type combinations that are expected to work
template class HashMap<int, int>;
template class HashMap<int, float>;
template class HashMap<int, std::string>;