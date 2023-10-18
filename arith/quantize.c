#include <quantize.h>
#include <mem.h>
#include <arith40.h>
#include <math.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

/**
 * @brief Use Arith40_index_of_chroma to convert the two chroma values
 * to 4 bit values using non linear quantization (To be used for bitpacking later)
 * 
 * @param input PB and PR luma values (unsigned ints) retrieved through CVFFields
 * @param output Void, but passed through WordFields (IndexPB, IndexPR)
 */
void quantizeChromas(CVFFields_T input, WordFields_T output){
        output->IndexPB = Arith40_index_of_chroma(input->PB);
        output->IndexPR = Arith40_index_of_chroma(input->PR);
}

/**
 * @brief Use float Arith40_chroma_of_index to convert the two 4 bit
 * quantized index values back to the PB and PR croma values
 * 
 * @param intput Quantized PB and PR (retrieved from wordField)
 * @param output Dequenatied PB and PR values passed through output
 */
void dequantizeChromas(WordFields_T input, CVFFields_T output){
        output->PB = Arith40_chroma_of_index(input->IndexPB);
        output->PR = Arith40_chroma_of_index(input->IndexPR);
}


/**
 * @brief Code a into a 9 bit int and b,c,d into 4 bits using
 * linear quantization
 * 
 * @param input Luma values a, b, c, d (unsigned ints) 
 * @param output Void, but passed through WordFields 
 */
void quantizeCoeffients(DCTFields_T input, WordFields_T output){
        /*check for values that arent encoded*/
        b = MIN(b, .3);
        b = MAX(b, -.3);
        c = MIN(c, .3);
        c = MAX(c, -.3);
        d = MIN(d, .3);
        d = MAX(d, -.3);
        /* quantze a */
        output->a = (unsigned) (input->a * 511);
        output->b =  round(input->b * 50);
        output->c =  round(input->c * 50);
        output->d =  round(input->d * 50);

}

/**
 * @brief Use reverse linear quantization function to recover
 * original discrete cosine transform coefficients
 * 
 * @param input quantized DCT coefficients (retrieved from wordField)
 * @param output Dequantized DCT coefficents (a,b,c,d)
 */
DCTFields_T dequantizeCoeffients(WordFields_T input){
        (void) input;
        DCTFields_T DCTFields = ALLOC(sizeof(struct DCTFields));
        
        return DCTFields;
}