#ifndef COMPRESSOR
#define COMPRESSOR

#include <pnm.h>
#include <uarray.h>
#include <WordFields.h>



#define PIXSINBLOCK 4

struct rgbBlock{
        int denominator;
        int count;
        UArray_T block;
};

typedef struct rgbBlock * rgbBlock_T; 

void compress(rgbBlock_T input);

#endif