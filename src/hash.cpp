#include <iostream>
#include <stdexcept>

#include "hash.hpp"

template <typename TK, typename TV> HashMap<TK, TV>::HashMap(const uint max_n) {
    std::cout << "Instantiating HashMap expecting max of " << max_n
              << " elements..." << std::endl;
    HashMap::max_n = max_n;
    HashMap::table = new HashNode[max_n];
}

template <typename TK, typename TV> HashMap<TK, TV>::~HashMap() {
    delete[] HashMap::table;
}

template <typename TK, typename TV> uint HashMap<TK, TV>::size() {
    return HashMap::n;
}

template <typename TK, typename TV> uint HashMap<TK, TV>::hash(const TK key) {
    return key % max_n;
}

template <typename TK, typename TV> TV &HashMap<TK, TV>::find(const TK key) {
    uint k = hash(key);
    while (table[k].status != FREE) {
        if (table[k].status == OCCUPIED && table[k].key == key)
            return table[k].value;

        k = (k + 1) % max_n;
    }

    throw std::runtime_error("Key not found!");
}

template <typename TK, typename TV>
bool HashMap<TK, TV>::insert(const TK key, const TV value) {
    uint k = hash(key);
    while (table[k].status == OCCUPIED)
        k = (k + 1) % max_n;

    table[k].status = OCCUPIED;
    table[k].key = key;
    table[k].value = value;
    n++;
    return true;
}

template <typename TK, typename TV> bool HashMap<TK, TV>::remove(const TK key) {
    uint k = hash(key);
    while (table[k].key != key)
        k = (k + 1) % max_n;

    table[k].status = DELETED;
    n--;
    return true;
}

template <typename TK, typename TV>
TV &HashMap<TK, TV>::operator[](const TK key) {
    return find(key);
}

// instantiate type combinations that are expected to work
template class HashMap<int, int>;
template class HashMap<int, float>;
template class HashMap<int, std::string>;