#include <quantize.h>
#include <mem.h>
#include <arith40.h>
#include <math.h>
#include <assert.h>


static float trim(float x);

static void checkCoeffients(int x);

/**
 * @brief Use Arith40_index_of_chroma to convert the two chroma values
 * to 4 bit values using non linear quantization (To be used for bitpacking later)
 * 
 * @param input PB and PR luma values (unsigned ints) retrieved through CVFFields
 * @param output Void, but passed through WordFields (IndexPB, IndexPR)
 */
void quantizeChromas(CVFFields_T input, WordFields_T output){
        // printf("PB: %f PR: %f\n", input->PB, input->PR);
        output->indexPB = Arith40_index_of_chroma(input->PB);
        output->indexPR = Arith40_index_of_chroma(input->PR);
}

/**
 * @brief Use float Arith40_chroma_of_index to convert the two 4 bit
 * quantized index values back to the PB and PR croma values
 * 
 * @param intput Quantized PB and PR (retrieved from wordField)
 * @param output Dequenatied PB and PR values passed through output
 */
void dequantizeChromas(WordFields_T input, CVFFields_T output){
        output->PB = Arith40_chroma_of_index(input->indexPB);
        output->PR = Arith40_chroma_of_index(input->indexPR);
        // printf("PB: %f PR: %f\n", output->PB, output->PR);
}


/**
 * @brief Code a into a 9 bit int and b,c,d into 4 bits using
 * linear quantization
 * 
 * @param input Luma values a, b, c, d (unsigned ints) 
 * @param output Void, but passed through WordFields 
 */
void quantizeCoeffients(DCTFields_T input, WordFields_T output){
        /*check for values that aren't encoded*/
        // printf("a:%f b:%f c:%f d:%f \n", input->a, input->b, input->c, input->d);
        input->b = trim(input->b);
        input->c = trim(input->c);
        input->d = trim(input->d);
        /* quantze a */
        output->a = (unsigned) (input->a * 511);
        output->b = round(input->b * 50);
        output->c = round(input->c * 50);
        output->d = round(input->d * 50);
        checkCoeffients(output->b);
        checkCoeffients(output->c);
        checkCoeffients(output->d);

        // printf("a:%d b:%d c:%d d:%d \n", output->a, output->b, output->c, output->d);
}

static void checkCoeffients(int x){
        assert(x >= -15);
        assert(x <= 15);
}

static float trim(float x){
        if(x > .3){
                return .3;
        }
        else if(x < -.3){
                return -.3;
        }
        else {
                return x;
        }
}


/**
 * @brief Use reverse linear quantization function to recover
 * original discrete cosine transform coefficients
 * 
 * @param input quantized DCT coefficients (retrieved from wordField)
 * @param output Dequantized DCT coefficents (a,b,c,d)
 */
DCTFields_T dequantizeCoeffients(WordFields_T input){
        DCTFields_T output = ALLOC(sizeof(struct DCTFields));
        // printf("a is %u\n", input->a);
        // printf("b is %d\n", input->b);
        // printf("c is %d\n", input->c);
        // printf("d is %d\n", input->d);

        output->a = ((float) input->a) / 511.0;
        output->b = ((float) input->b) / 50.0;
        output->c = ((float) input->c) / 50.0;
        output->d = ((float) input->d) / 50.0;

        //printf("a:%f b:%f c:%f d:%f \n", output->a, output->b, output->c, output->d);
        
        return output;
}