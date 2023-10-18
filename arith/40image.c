/**
 * @file 40images.c
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 * main() - is responsible for stdio / decoding the input from user
 * output
 * 
 * Usage:
 * 40images -c/d [filename]"
 * 
 * The -s flag is for compression and -d flag is for decompression
 * 
 * The transformed ppm is printed in binary to stdout
 */


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <a2plain.h>
#include <uarray2.h>
#include <a2blocked.h>
#include <uarray2b.h>
#include "assert.h"
#include "compress40.h"
#include <mem.h>
#include <compressor.h>
#include <uarray.h>

/*for testing*/

#define PIXSINBLOCK 4


static void (*compress_or_decompress)(FILE *input) = compress40;
void compress40(FILE *input);
void decompress40(FILE *input);

int main(int argc, char *argv[])
{
        int i;

        for (i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-c") == 0) {
                        compress_or_decompress = compress40;
                } else if (strcmp(argv[i], "-d") == 0) {
                        compress_or_decompress = decompress40;
                } else if (*argv[i] == '-') {
                        fprintf(stderr, "%s: unknown option '%s'\n",
                                argv[0], argv[i]);
                        exit(1);
                } else if (argc - i > 2) {
                        fprintf(stderr, "Usage: %s -d [filename]\n"
                                "       %s -c [filename]\n",
                                argv[0], argv[0]);
                        exit(1);
                } else {
                        break;
                }
        }
        assert(argc - i <= 1);    /* at most one file on command line */
        if (i < argc) {
                FILE *fp = fopen(argv[i], "r");
                assert(fp != NULL);
                compress_or_decompress(fp);
                fclose(fp);
        } else {
                compress_or_decompress(stdin);
        }
        
        return EXIT_SUCCESS; 
}


/**
 * @brief mapping function used in blockedPnmIterator
 * Sets closure (an rgbBlock) to the next 2x2 pixels
 * For every 2x2 pixel block (4 pixels) feed the closure (rgbBlock)
 * into compression
 * 
 * @param ptr pointer to pnm_rgb 
 * @param cl 
 */
void smallMapper(A2Methods_Object *ptr, void *cl){
        rgbBlock_T rgbBlock = (rgbBlock_T) cl;
        *((Pnm_rgb) UArray_at(rgbBlock->block, rgbBlock->count)) = * ((Pnm_rgb)(ptr));
        
        rgbBlock->count++;
        if(rgbBlock->count == PIXSINBLOCK){
                /*compress that shit*/
                compress(rgbBlock);          
                rgbBlock->count = 0;
        }
}

/**
 * @brief allocates and instaniates cl which is an rgbBlock_T and feeds it into
 * the mapping function which iterators through pixels in row major order accessing
 * elements in 2x2 block order
 * 
 * @param inputPnm Pnm_ppm image to iterator through 
 */             
void blockedPnmIterator(Pnm_ppm inputPnm){
        rgbBlock_T cl = ALLOC(sizeof(struct rgbBlock));
        cl->block = UArray_new(PIXSINBLOCK, sizeof(struct Pnm_rgb));
        cl->count = 0;
        cl->denominator = inputPnm->denominator;
        inputPnm->methods->small_map_block_major(
                inputPnm->pixels, smallMapper, (void *) cl);  
        
        UArray_free(&(cl->block));
        free(cl);
}

/**
 * @brief wrapper function that reads in the pnm and calls the blockedPnmIterator
 * 
 * @param input Filename to read as a Pnm_ppm
 */
void compress40(FILE *input){
        Pnm_ppm inputPnm = Pnm_ppmread(input, uarray2_methods_blocked);
        blockedPnmIterator(inputPnm);
        Pnm_ppmfree(&inputPnm);
}

void decompress40(FILE *input){
        (void) input;    
}
