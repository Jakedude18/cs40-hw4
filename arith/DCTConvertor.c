
#include <DCTConvertor.h>
#include <mem.h>

/**
 * @brief uses the discrete cosine transform to convert the
 * 4 luma values into the cosine coeficients a,b,c,d
 * 
 * @param input CVFFields although we only need Y1, Y2, Y3, and Y4 
 * @return DCTFields_T 
 */
DCTFields_T DCTCompressor(CVFFields_T input){
        DCTFields_T DCTFields = ALLOC(sizeof(struct DCTFields));

        float Y1 = input->lumas[0];
        float Y2 = input->lumas[1];
        float Y3 = input->lumas[2];
        float Y4 = input->lumas[3];
        

        DCTFields->a = (Y4 + Y3 + Y2 + Y1)/4.0;
        DCTFields->b = (Y4 + Y3 - Y2 - Y1)/4.0;
        DCTFields->c = (Y4 - Y3 + Y2 - Y1)/4.0;
        DCTFields->d = (Y4 - Y3 - Y2 + Y1)/4.0;
        printf("%f, %f, %f, %f \n", DCTFields->a, DCTFields->b, DCTFields->c, DCTFields->d);
        return DCTFields;
}

/**
 * @brief Uses the inverse discrete cosine transformation to convert
 * the cosine coeffients a, b, c, d to the luma values Y1, Y2, Y3, Y4
 * 
 * @param input 
 * @return CVFFields_T 
 */
CVFFields_T DCTDecompressor(DCTFields_T input){
        CVFFields_T CVFFields = ALLOC(sizeof(struct CVFFields)); 

        float a = input->a;
        float b = input->b;
        float c = input->c;
        float d = input->d;


        CVFFields->lumas[0] = a - b - c + d;
        CVFFields->lumas[1] = a - b + c - d;
        CVFFields->lumas[2] = a + b - c - d;
        CVFFields->lumas[3] = a + b + c + d;
        
        return CVFFields;
}