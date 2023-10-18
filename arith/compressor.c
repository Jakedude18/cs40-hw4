#include <compressor.h>
#include <CVFConvertor.h>
#include <DCTConvertor.h>
#include <quantize.h>
#include <pnm.h>
#include <mem.h>


/**
 * @brief takes in a rgbBlock and prints it out as a bitpacked integer
 * aggrates togethe
 * 
 * @param input rgbBlock_T to be compressed
 */
void compress(rgbBlock_T input) {


        /*
        printf("original rgbBlock\n");
        for(int i = 0; i < PIXSINBLOCK; i++){
                Pnm_rgb curPix = (Pnm_rgb) UArray_at(input->block, i );
                printf("%u.%u.%u  ", curPix->red, curPix->green, curPix->blue);
        }
        */
        

        CVFFields_T CVFFieldsComp = CVFCompressor(input);
        
        DCTFields_T DCTFieldsComp = DCTCompressor(CVFFieldsComp);

        WordFields_T wordFieldsComp = ALLOC(sizeof(struct WordFields));
        quantizeChromas(CVFFieldsComp, wordFieldsComp);
        
        CVFFields_T CVFFieldsDecomp = DCTDecompressor(DCTFieldsComp);
        FREE(DCTFieldsComp);
        CVFFieldsDecomp->PB = CVFFieldsComp->PB;
        CVFFieldsDecomp->PR = CVFFieldsComp->PR;
        /* free later because we have to copy over values*/
        FREE(CVFFieldsComp);

        rgbBlock_T output = CVFDecompressor(CVFFieldsDecomp);
        FREE(CVFFieldsDecomp);
    
        
        /*
        printf("\ndecompressed rgbBlock\n");
        for(int i = 0; i < PIXSINBLOCK; i++){
                Pnm_rgb curPix = (Pnm_rgb) UArray_at(output->block, i);
                printf("%u.%u.%u  ", curPix->red, curPix->green, curPix->blue);
        }
        */


        UArray_free(&(output->block));
        FREE(output);
        
        // FREE(output);
        printf("\n");
        /*for testing*/

}
