#ifndef QUANTIZE
#define QUANTIZE

#include <CVFConvertor.h>
#include <DCTConvertor.h>

struct WordFields{
        int a, b, c, d;
        unsigned IndexPB, IndexPR; 
};

typedef struct WordFields * WordFields_T;


void quantizeChromas(CVFFields_T input, WordFields_T output);

void dequantizeChromas(WordFields_T input, CVFFields_T output);

void quantizeCoeffients(DCTFields_T input, WordFields_T output);

DCTFields_T dequantizeCoeffients(WordFields_T input);

#endif