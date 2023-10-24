/**
 * @file CVFConvertor.h
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 *  This is the header file to CVFConverter.c. It declares the public functions
 *  CVFCompressor and CVFDecompressor, and the struct CVFFields that holds the
 *  PB, PR and the luma values of a 2x2 block.
 **/

#ifndef CVFCONVERTOR
#define CVFCONVERTOR

#include "CVFConvertor.h"
#include <compressor.h>

#define PIXSINBLOCK 4

struct CVFFields {
        float PB, PR;
        /* Y1, Y2, Y3, Y4 */
        float lumas[PIXSINBLOCK];
};

typedef struct CVFFields * CVFFields_T;

CVFFields_T CVFCompressor(rgbBlock_T rgbBlock);

rgbBlock_T CVFDecompressor(CVFFields_T CVFFields, int denominator);

#endif 