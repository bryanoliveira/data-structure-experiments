#ifndef HASH_HPP_
#define HASH_HPP_

#include "types.hpp"

#define FREE     0
#define OCCUPIED 1
#define DELETED  2

template <typename TK, typename TV> class HashMap {
  private:
    typedef struct {
        ushort status = FREE;
        TK key;
        TV value;
    } HashNode;

    HashNode *table;
    uint max_n;
    uint n = 0;
    uint comparisons = 0;

  public:
    HashMap(const uint max_n);
    ~HashMap();
    uint get_size();
    // TODO get_comparisons()
    // TODO float get_load_factor();
    // TODO Stats get_grouping_stats();
    uint hash(const TK key);
    TV &find(const TK key);
    bool insert(const TK key, const TV value);
    bool remove(const TK key);

    TV &operator[](const TK key);
};

#endif