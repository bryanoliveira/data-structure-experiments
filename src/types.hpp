#ifndef TYPES_HPP_
#define TYPES_HPP_

typedef unsigned char ubyte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef struct {
    int total;
    float mean;
    float stdev;
    int min;
    int max;
} Stats;

#endif