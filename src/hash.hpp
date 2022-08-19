#ifndef HASH_HPP_
#define HASH_HPP_

#include "types.hpp"

#define FREE 0
#define OCCUPIED 1
#define DELETED 2

template <typename TK, typename TV> class Hash {
  private:
    typedef struct {
        ushort status = 0;
        TV value;
    } HashNode;

    HashNode *table;
    uint exp_n;
    uint n = 0;

    uint hash(const TK key);

  public:
    Hash(const uint exp_n);
    ~Hash();
    uint size();
    bool insert(const TK key, const TV value);
    bool remove(const TK key);
    TV& operator[](const TK key);
};


#endif