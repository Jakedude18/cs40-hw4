/**
 * @file 40images.c
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 *  Main functionality for arith. Takes in a ppm of an image or a bit packed
 *  binary file containing the compressed version of a ppm and compresses or  *  decompresses the image according to the inputted flag.
 *  Compress40 calls the compress agregator function for each 2x2 block
 *  in the ppm of an image. Decompress40 calls the decompress agregator
 *  function for each "word" in the bitpacked binary file.
 *  
 * main() - is responsible for stdio / decoding the input from user
 * output
 * 
 * Usage:
 * 40images -c/d [filename]"
 * 
 * The -c flag is for compression and -d flag is for decompression
 * 
 * The transformed ppm is printed in binary to stdout
 */


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pnm.h>
#include <a2plain.h>
#include <uarray2.h>
#include <a2blocked.h>
#include <a2plain.h>
#include <uarray2b.h>
#include "assert.h"
#include "compress40.h"
#include <mem.h>
#include <compressor.h>
#include <decompressor.h>
#include <uarray.h>
#include <quantize.h>
#include <bitpack.h>

#define PIXSINBLOCK 4
#define MINDENOMINATOR 255
#define MAXDENOMINATOR 65535
#define PI 3.14159265358979323846  /* pi */
#define SCALLINGCOEFFICIENT 500



static UArray2b_T trimmedArray(UArray2b_T original, int trimmedWidth, int trimmedHeight);
static void (*compress_or_decompress)(FILE *input) = compress40;
static int denominatorCalculator(int size);
void copyArray(int col, int row, UArray2b_T copy, void *curr, void *original);
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
void smallMapper(A2Methods_Object *ptr, void *cl)
{
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
        FREE(cl);
}

/**
 * @brief wrapper function that reads in the pnm and calls the blockedPnmIterator
 * 
 * @param input Filename to read as a Pnm_ppm
 */
void compress40(FILE *input)
{
        Pnm_ppm inputPnm = Pnm_ppmread(input, uarray2_methods_blocked);
        
        int trimmedWidth = inputPnm->width;
        int trimedHeight = inputPnm->height;
        bool change = false;


        if(trimmedWidth % 2 == 1){
                change = true;
                trimmedWidth--;
        }
        if(trimedHeight % 2 == 1){
                change = true;
                trimedHeight--;
        }

        printf("COMP40 Compressed image format 2\n%u %u\n", trimmedWidth, trimedHeight);
        
        if(change){
                /* copy over the old array to the new one */
                UArray2b_T newArray = trimmedArray((UArray2b_T)inputPnm->pixels, trimmedWidth, trimedHeight);
                inputPnm->methods->free(&(inputPnm->pixels));
                inputPnm->pixels = (A2Methods_UArray2)newArray;
        }

        inputPnm->height = trimedHeight;
        inputPnm->width = trimmedWidth;
        blockedPnmIterator(inputPnm);

        Pnm_ppmfree(&inputPnm);
}

static UArray2b_T trimmedArray(UArray2b_T original, int trimmedWidth, int trimmedHeight)
{
        UArray2b_T trimmed = UArray2b_new(trimmedWidth, trimmedHeight, sizeof(struct Pnm_rgb), PIXSINBLOCK/2);
        UArray2b_map(trimmed, copyArray, original);
        return trimmed;

}

void copyArray(int col, int row, UArray2b_T copy, void *curr, void *original)
{
        original = (UArray2b_T) original;
        *((Pnm_rgb)curr) = *((Pnm_rgb)UArray2b_at(original, col, row));
        (void) copy;
}




// static void printRGB(Pnm_rgb input){
//         printf("%c%c%c", input->red, input->green, input->blue);
// }

void decompress40(FILE *input)
{
        unsigned height, width;
        int read = fscanf(input, "COMP40 Compressed image format 2\n%u %u", &width, &height);
        int denominator = denominatorCalculator(height * width);
        assert(read == 2);
        int c = getc(input);
        assert(c == '\n');



        

        UArray2_T outputUArray2 = UArray2_new(width, height, sizeof(struct Pnm_rgb));

        Pnm_ppm pixmap = ALLOC(sizeof(struct Pnm_ppm));
        pixmap->width = width;
        pixmap->height = height;
        pixmap->denominator = denominator;
        pixmap->pixels = outputUArray2;
        pixmap->methods = uarray2_methods_plain;

        for(unsigned j = 0; j < height/2; j++){                
                for(unsigned k = 0; k < width/2; k++){
                        uint64_t word = 0;
                        int first = getc(input);
                        assert(first != EOF);

                        int second = getc(input);
                        assert(second != EOF);

                        int third = getc(input);
                        assert(third != EOF);

                        int fourth = getc(input);
                        assert(fourth != EOF);

                        
                        // printf("first char %d\n", first);
                        // printf("second char %d\n", second);
                        // printf("third char %d\n", third);
                        // printf("fourth char %d\n", fourth);

                        word = Bitpack_newu(word, 8, 0, first);
                        word = Bitpack_newu(word, 8, 8, second);
                        word = Bitpack_newu(word, 8, 16, third);
                        word = Bitpack_newu(word, 8, 24, fourth);

                        //printf("the word is: %lu\n", word);

                        rgbBlock_T decompressedBlock = decompress(word, denominator);
                        // for(int i = 0; i < PIXSINBLOCK; i++){
                        //         Pnm_rgb curpix = (Pnm_rgb) UArray_at(decompressedBlock->block, i);
                        //         printf("%d,%d,%d\n", curpix->red, curpix->green, curpix->blue);
                        // }
                        *((Pnm_rgb)UArray2_at(outputUArray2, k * 2, j * 2)) = *((Pnm_rgb) UArray_at(decompressedBlock->block, 0)); 
                        *((Pnm_rgb)UArray2_at(outputUArray2, k * 2 + 1, j * 2)) = *((Pnm_rgb) UArray_at(decompressedBlock->block, 2)); 
                        *((Pnm_rgb)UArray2_at(outputUArray2, k * 2, j * 2 + 1)) = *((Pnm_rgb) UArray_at(decompressedBlock->block, 1)); 
                        *((Pnm_rgb)UArray2_at(outputUArray2, k * 2 + 1, j * 2 + 1)) = *((Pnm_rgb) UArray_at(decompressedBlock->block, 3)); 

                        UArray_free(&(decompressedBlock->block));
                        FREE(decompressedBlock);
                }
               
        }

        Pnm_ppmwrite(stdout, pixmap);
        Pnm_ppmfree(&pixmap);
}

/*
*/
static int denominatorCalculator(int size)
{
        assert(size > 0);
        /*           65535             65535 - 255                      (scaling coeffient which ranges from 0 - 1)*/
        return (MAXDENOMINATOR) - (MAXDENOMINATOR - MINDENOMINATOR) * (2 * atan(size / SCALLINGCOEFFICIENT) /  PI);
}



