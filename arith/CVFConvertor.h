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