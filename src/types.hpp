#ifndef TYPES_HPP_
#define TYPES_HPP_

typedef unsigned char ubyte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct {
    uint total = 0;
    float mean = 0;
    float stdev = 0;
    uint min = 0;
    uint max = 0;
} Stats;

#endif