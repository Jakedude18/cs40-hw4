#ifndef DECOMPRESSOR
#define DECOMPRESSOR

#include <compressor.h>
#include <CVFConvertor.h>
#include <WordFields.h>
#include <stdint.h>


/**
 * @brief takes in a bitpacked integer and prints it out as a rgbBlock
 * 
 * @param input int to be decompressed
 */
rgbBlock_T decompress(uint64_t input, int denominator);

#endif