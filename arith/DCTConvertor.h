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