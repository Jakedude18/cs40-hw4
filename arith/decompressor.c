/**
 * @file decompressor.c
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 * This file defines the decompress function which is an aggregator function
 * that calls all the steps of decompression. It takes a bitpacked integer
 * and returns an rgbBlock that holds that rgb values of a 2x2 block.
 **/

#include <compressor.h>
#include <CVFConvertor.h>
#include <DCTConvertor.h>
#include <quantize.h>
#include <bitpacker.h>
#include <pnm.h>
#include <mem.h>

/**
 * @brief takes in a bitpacked integer and prints it out as a rgbBlock
 * 
 * 
 * @param input rgbBlock_T to be compressed
 */
rgbBlock_T decompress(uint64_t input, int denominator)
{

        WordFields_T unpackedWord = bitUnpacker(input);

        DCTFields_T DCTFieldsDecomp = dequantizeCoeffients(unpackedWord);

        CVFFields_T CVFFieldsDecomp = DCTDecompressor(DCTFieldsDecomp);

        dequantizeChromas(unpackedWord, CVFFieldsDecomp);

        rgbBlock_T output = CVFDecompressor(CVFFieldsDecomp, denominator);
        
        FREE(unpackedWord);
        FREE(DCTFieldsDecomp);
        FREE(CVFFieldsDecomp);

        /* free later because we have to copy over values*/

        return output;
}