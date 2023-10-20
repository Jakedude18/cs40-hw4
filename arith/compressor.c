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
void compress(rgbBlock_T input) {


        
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

        /* print out in big endian order */
        putchar(Bitpack_getu(packedInt, 8, 0));
        putchar(Bitpack_getu(packedInt, 8, 8));
        putchar(Bitpack_getu(packedInt, 8, 16));
        putchar(Bitpack_getu(packedInt, 8, 24));



        FREE(CVFFieldsComp);
        FREE(DCTFieldsComp);
        FREE(wordFieldsComp);

    
        // printf("\nDecompressed rgbBlock\n");
        // for(int i = 0; i < PIXSINBLOCK; i++){
        //         Pnm_rgb curPix = (Pnm_rgb) UArray_at(output->block, i);
        //         printf("%u.%u.%u  ", curPix->red, curPix->green, curPix->blue);
        // }

}

