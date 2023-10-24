/**
 * @file compressor.c
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 * This file defines the compress function which is an aggregator function
 * that calls all the steps of compression. It takes a 2x2 block of Pgm_rgbs,
 * bitpacks it, and prints the bitpacked version to standard output.
 **/
#include <compressor.h>
#include <CVFConvertor.h>
#include <DCTConvertor.h>
#include <quantize.h>
#include <WordFields.h>
#include <pnm.h>
#include <mem.h>
#include <bitpacker.h>
#include <bitpack.h>


/**
 * @brief takes in a rgbBlock and prints it out as a bitpacked integer
 * aggrates togethe
 * 
 * @param input rgbBlock_T to be compressed
 */
void compress(rgbBlock_T input)
{


        
        // for(int i = 0; i < PIXSINBLOCK; i++){
        //         Pnm_rgb curPix = (Pnm_rgb) UArray_at(input->block, i );
        //         printf("%u.%u.%u  \n", curPix->red, curPix->green, curPix->blue);
        // }
        

        CVFFields_T CVFFieldsComp = CVFCompressor(input);
        
        DCTFields_T DCTFieldsComp = DCTCompressor(CVFFieldsComp);

        WordFields_T wordFieldsComp = ALLOC(sizeof(struct WordFields));
        quantizeChromas(CVFFieldsComp, wordFieldsComp);
        quantizeCoeffients(DCTFieldsComp, wordFieldsComp);

        uint64_t packedInt = bitPacker(wordFieldsComp);
        
        //printf("the word is: %lu\n", packedInt);

        /* print out in big endian order */
        /* remeber that in our amd systems ints are stored in little endian order */
        int first = Bitpack_getu(packedInt, 8, 0);
        putchar(first);
        int second = Bitpack_getu(packedInt, 8, 8);
        putchar(second);
        int third = Bitpack_getu(packedInt, 8, 16);
        putchar(third);
        int fourth = Bitpack_getu(packedInt, 8, 24);
        putchar(fourth);

        // printf("first char %d\n", first);
        // printf("second char %d\n", second);
        // printf("third char %d\n", third);
        // printf("fourth char %d\n", fourth);



        FREE(CVFFieldsComp);
        FREE(DCTFieldsComp);
        FREE(wordFieldsComp);

    
        // printf("\nDecompressed rgbBlock\n");
        // for(int i = 0; i < PIXSINBLOCK; i++){
        //         Pnm_rgb curPix = (Pnm_rgb) UArray_at(output->block, i);
        //         printf("%u.%u.%u  ", curPix->red, curPix->green, curPix->blue);
        // }

}

