
/**
 * @file decompressor.h
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 *  This is the header file to decompressor.c. It declares the public function
 *  decompress that calls the steps of decompression.
 **/

#ifndef DECOMPRESSOR
#define DECOMPRESSOR

#include <compressor.h>
#include <CVFConvertor.h>
#include <WordFields.h>
#include <stdint.h>



rgbBlock_T decompress(uint64_t input, int denominator);

#endif