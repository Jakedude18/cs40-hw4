/**
 * @file CVFConvertor.c
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 * This file defines the CVFCompressor and CVFDecompressor public functions,
 * and the static function roundToOne. CVFCompressor takes an rgbBlock and
 * tranforms that values to component video color space. CVFDecompressor
 * takes the componenet video color space values and inverses the arithmetic
 * back to rgb values.
 **/

#include "CVFConvertor.h"
#include <mem.h>
#include <uarray.h>


static float roundToOne(float x);


/**
 * @brief Takes in a rgbBlock corresponding to a 2 by 2 block 
 * and converts to component video format
 * 
 * @param rgbBlock 
 * @note allocates a CVFFields_T that must be deallocated by client 
 * @return CVFFields 
 */
CVFFields_T CVFCompressor(rgbBlock_T rgbBlock)
{
        CVFFields_T CVFFields = ALLOC(sizeof(struct CVFFields));

        
        float pbSum = 0;
        float prSum = 0;
        
        for(int i = 0; i < PIXSINBLOCK; i++){
                unsigned r = ((Pnm_rgb)UArray_at(rgbBlock->block,i))->red;
                unsigned g = ((Pnm_rgb)UArray_at(rgbBlock->block,i))->green;
                unsigned b = ((Pnm_rgb)UArray_at(rgbBlock->block,i))->blue;
                CVFFields->lumas[i] =  (0.299 * r + 0.587 * g + 0.114 * b) / rgbBlock->denominator;
                pbSum += -0.168736 * r - 0.331264 * g + 0.5 * b;
                prSum +=  0.5 * r - 0.418688 * g - 0.081312 * b;
        }
        
        CVFFields->PB = (pbSum / PIXSINBLOCK) / rgbBlock->denominator;
        CVFFields->PR = (prSum / PIXSINBLOCK) / rgbBlock->denominator;
        // printf("PB: %f, PR: %f\n", CVFFields->PB, CVFFields->PR);
        // printf("%f, %f, %f, %f  \n", CVFFields->lumas[0], CVFFields->lumas[1], CVFFields->lumas[2], CVFFields->lumas[3]);
        return CVFFields;
}

/**
 * @brief For each set of luma and chromas: (Y1, Y2, Y3, Y4, PB, PR)
 * create a 2x2 pixel and set it to a block in a new 2BArray
 * 
 * @param CVFFields 
 * @note allocates an rgbblock which muse be deallocated by the client
 * @return rgbBlock_T 
 */
rgbBlock_T CVFDecompressor(CVFFields_T CVFFields, int denominator)
{
        // printf("PB: %f, PR: %f\n", CVFFields->PB, CVFFields->PR);
        // printf("%f, %f, %f, %f  \n", CVFFields->lumas[0], CVFFields->lumas[1], CVFFields->lumas[2], CVFFields->lumas[3]);
        rgbBlock_T rgbBlock = ALLOC(sizeof(struct rgbBlock));
        rgbBlock->block = UArray_new(PIXSINBLOCK, sizeof(struct Pnm_rgb));
        rgbBlock->count = 0;

        float pb = CVFFields->PB;
        float pr = CVFFields->PR;
        for(int i = 0; i < PIXSINBLOCK; i++){
                float y = CVFFields->lumas[i];
                float red = (1.0 * y + 0.0 * pb + 1.402 * pr);
                float green = (1.0 * y - 0.344136 * pb - 0.714136 * pr);
                float blue = (1.0 * y + 1.772 * pb + 0.0 * pr);
                
                red = roundToOne(red);
                green = roundToOne(green);
                blue = roundToOne(blue);
                
                ((Pnm_rgb)UArray_at(rgbBlock->block,i))->red = red * denominator;
                ((Pnm_rgb)UArray_at(rgbBlock->block,i))->green = green * denominator;
                ((Pnm_rgb)UArray_at(rgbBlock->block,i))->blue = blue * denominator;
        }

        return rgbBlock;
}

static float roundToOne(float x)
{
        if (x > 1){
                return 1.0;
        }
        if (x < 0){
                return 0;
        }
        return x;
}
