#include <bitpack.h>
#include <stdint.h>
#include <stdio.h>


// int main(int argc, char *argv[]){
//         (void) argc;
//         (void) argv;

//         uint64_t n = 0;
//         unsigned width = 0;

        

//         printf("%lu does fit in %d (unsigned): ", n, width);
//         if(Bitpack_fitsu(n, width)){
//                 printf("true\n");
//         }
//         else{
//                 printf("false\n");
//         }
        

// }


// int main(int argc, char *argv[]){
//         (void) argc;
//         (void) argv;

//         int64_t n = -2;
//         unsigned width = 2;

        

//         printf("%ld does fit in %d (signed): ", n, width);
//         if(Bitpack_fitss(n, width)){
//                 printf("true\n");
//         }
//         else{
//                 printf("false\n");
//         }
        

// }

// int main(int argc, char *argv[]){
//         (void) argc;
//         (void) argv;

//         uint64_t n = 0x3f4;
//         unsigned width = 0;
//         unsigned lsb = 0;
        

//         printf("%lu\n", Bitpack_getu(n, width, lsb));
        

// }


// int main(int argc, char *argv[]){
//         (void) argc;
//         (void) argv;

//         uint64_t n = 0x3f4;
//         unsigned width = 0;
//         unsigned lsb = 0;
        
//         printf("%ld\n", Bitpack_gets(n, width, lsb));

// }

// int main(int argc, char *argv[]){
//         (void) argc;
//         (void) argv;

//         uint64_t n = 0x3f4;
//         unsigned width = 4;
//         unsigned lsb = 2;
//         unsigned val = 15;
        
//         printf("%ld\n", Bitpack_getu(Bitpack_newu(n, width, lsb, val), width, lsb));

// }

int main(int argc, char *argv[]){
        (void) argc;
        (void) argv;

        uint64_t n = 0x3f4;
        unsigned width = 2;
        unsigned lsb = 0;
        int64_t val = 2;
        
        printf("%ld\n", Bitpack_gets(Bitpack_news(n, width, lsb, val), width, lsb));

}




