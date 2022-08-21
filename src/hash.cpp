#include <iostream>
#include <stdexcept>

#include "hash.hpp"

#define PROBE_PREP(key, k)                                                     \
    uint hk = hash(key);                                                       \
    k = hk;                                                                    \
    uint i = 1;
#ifdef LINEAR_PROBING
#define PROBE_STEP(k)                                                          \
    k = (hk + i) % max_n;                                                      \
    i++;
#else // quadratic probing
#define PROBE_STEP(k)                                                          \
    k = (hk + i * i) % max_n;                                                  \
    i++;
#endif

#define TKV template <typename TK, typename TV>

TKV HashMap<TK, TV>::HashMap(const uint max_n) {
    std::cout << "Instantiating HashMap expecting max of " << max_n
              << " elements..." << std::endl;
#ifdef LINEAR_PROBING
    std::cout << "Using linear probing." << std::endl;
#else // linear probing
    std::cout << "Using quadratic probing." << std::endl;
#endif
    HashMap::max_n = max_n;
    HashMap::table = new HashNode[max_n];
}

TKV HashMap<TK, TV>::~HashMap() { delete[] HashMap::table; }

TKV uint HashMap<TK, TV>::get_size() { return HashMap::n; }

TKV uint HashMap<TK, TV>::hash(const TK key) { return key % max_n; }

TKV TV &HashMap<TK, TV>::operator[](const TK key) { return find(key); }

TKV TV &HashMap<TK, TV>::find(const TK key) {
    uint k;
    PROBE_PREP(key, k);
    while (table[k].status != FREE) {
        if (table[k].status == OCCUPIED && table[k].key == key)
            return table[k].value;

        PROBE_STEP(k);
    }

    throw std::runtime_error("Key not found!");
}

TKV bool HashMap<TK, TV>::insert(const TK key, const TV value) {
    uint k;
    PROBE_PREP(key, k);
    while (table[k].status == OCCUPIED) {
        PROBE_STEP(k);
    }

    table[k].status = OCCUPIED;
    table[k].key = key;
    table[k].value = value;
    n++;
    return true;
}

TKV bool HashMap<TK, TV>::remove(const TK key) {
    uint k;
    PROBE_PREP(key, k);
    while (table[k].key != key) {
        PROBE_STEP(k);
    }

    table[k].status = DELETED;
    n--;
    return true;
}

// instantiate type combinations that are expected to work
template class HashMap<int, int>;
template class HashMap<int, float>;
template class HashMap<int, std::string>;