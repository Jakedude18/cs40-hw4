/**
 * @file DCTConvertor.h
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 *  This is the header file to DCTConverter.c. It declares the public functions
 *  DCTCompressor and DCTDecompressor, and the struct DCTFields that holds the
 *  cosine coefficients of a 2x2 block.
 **/

#ifndef DCTCONVERTOR
#define DCTCONVERTOR

#include "CVFConvertor.h"

struct DCTFields{
    float a, b, c, d;
};

typedef struct DCTFields * DCTFields_T;

DCTFields_T DCTCompressor(CVFFields_T input);

CVFFields_T DCTDecompressor(DCTFields_T input);

#endif