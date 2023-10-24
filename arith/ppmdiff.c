#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <math.h>
#include <a2plain.h>
#include <uarray2.h>
#include <assert.h>

#define NUMPIXS 3
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

static void
usage(const char *progname)
{
        fprintf(stderr, "Usage: %s -/filename_1 -/filename_2 ", progname);
        exit(1);
}

int main(int argc, char *argv[])
{
        if(argc != 3){
                usage(argv[0]);
        }

        FILE *fp1;
        FILE *fp2;
        if(!strcmp(argv[1],"-")){
                fp1 = stdin;        
        }
        else{
                fp1 = fopen(argv[1], "r");
        }
        if(!strcmp(argv[2], "-")){
                assert(fp1 != stdin);
                fp2 = stdin;        
        }        
        else{
                fp2 = fopen(argv[2], "r");
        }
        
        Pnm_ppm fileOne = Pnm_ppmread(fp1, uarray2_methods_plain);
        Pnm_ppm fileTwo = Pnm_ppmread(fp2, uarray2_methods_plain);

        assert(abs((int) fileOne->width - (int) fileTwo->width) <= 1);
        assert(abs((int) fileOne->height - (int) fileTwo->height) <= 1);

        int smallerWidth = MIN(fileOne->width, fileTwo->width);
        int smallerHeight = MIN(fileOne->height, fileTwo->height);


        float sum = 0;
        for(int i = 0; i < smallerWidth; i++){
                for(int j = 0; j < smallerHeight; j++){
                        Pnm_rgb curPix1 = (Pnm_rgb) fileOne->methods->at(fileOne->pixels, i, j);
                        Pnm_rgb curPix2 = (Pnm_rgb) fileTwo->methods->at(fileTwo->pixels, i, j);
                        float redDiff = pow(curPix1->red - curPix2->red, 2);
                        float greenDiff = pow(curPix1->green - curPix2->green, 2);
                        float blueDiff = pow(curPix1->blue - curPix2->blue, 2);
                        sum += (redDiff + greenDiff + blueDiff); 
                }
        } 
        sum /= (NUMPIXS * smallerWidth * smallerHeight);
        printf("%f\n", sqrt(sum));
        fclose(fp1);
        fclose(fp2);
        exit(0);
}
