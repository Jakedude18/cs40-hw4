
/**
 * @file compressor.h
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 *  This is the header file to compressor.c. It declares the public function
 *  compress and the rgbBlock stucture that holds a UArray of Pnm_rgbs,
 *  the denominator of the ppm, and a count variable.
 **/


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