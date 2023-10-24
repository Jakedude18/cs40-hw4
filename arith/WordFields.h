/**
 * @file WordFields.h
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 *  This is a header file that declares the WordFields struct that holds
 *  quantized chroma values and quantized cosine coefficients.
 **/
#ifndef WORDFIELDS
#define WORDFIELDS


struct WordFields{
        unsigned a;
        int b, c, d;
        unsigned indexPB, indexPR; 
};

typedef struct WordFields * WordFields_T;

#endif