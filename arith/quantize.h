/**
 * @file quantize.h
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 *  This is the header file to quantize.c. It declares the public functions
 *  quantizeChromas, quantizeCoefficients, dequantizeChromas, and
 *  dequantizeCoefficients that transform values to be stored in a
 *  WordFields struct.
 **/
#ifndef QUANTIZE
#define QUANTIZE

#include <CVFConvertor.h>
#include <DCTConvertor.h>
#include <WordFields.h>



void quantizeChromas(CVFFields_T input, WordFields_T output);

void dequantizeChromas(WordFields_T input, CVFFields_T output);

void quantizeCoeffients(DCTFields_T input, WordFields_T output);

DCTFields_T dequantizeCoeffients(WordFields_T input);

#endif