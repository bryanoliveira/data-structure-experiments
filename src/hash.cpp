#include <iostream>
#include <stdexcept>

#include "hash.hpp"

template <typename TK, typename TV> Hash<TK, TV>::Hash(const uint exp_n) {
    std::cout << "Instantiating HashMap expecting max of " << exp_n
              << " elements..." << std::endl;
    Hash::exp_n = exp_n;
    Hash::table = new HashNode[n];
}

template <typename TK, typename TV> Hash<TK, TV>::~Hash() {
    delete[] Hash::table;
}

template <typename TK, typename TV> uint Hash<TK, TV>::size() {
    return Hash::n;
}

template <typename TK, typename TV> uint Hash<TK, TV>::hash(const TK key) {
    return key % exp_n;
}

template <typename TK, typename TV>
bool Hash<TK, TV>::insert(const TK key, const TV value) {
    uint k = hash(key);
    table[k].status = OCCUPIED;
    table[k].value = value;

    n++;
    return true;
}

template <typename TK, typename TV> bool Hash<TK, TV>::remove(const TK key) {
    table[hash(key)].status = DELETED;
    n--;
    return true;
}

template <typename TK, typename TV> TV &Hash<TK, TV>::operator[](const TK key) {
    uint k = hash(key);
    if (table[k].status == OCCUPIED)
        return table[k].value;
    throw std::runtime_error("Key not found!");
}

// instantiate type combinations that are expected to work
template class Hash<int, int>;
template class Hash<int, float>;
template class Hash<int, std::string>;