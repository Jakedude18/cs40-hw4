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

        uint64_t n = 0;
        (void) n;
        unsigned width = 9;
        unsigned lsb = 23;
        int64_t val = 207;
        uint64_t word = 0;
        word = Bitpack_newu(word, width, lsb, val);
        word = Bitpack_news(word, 5, 18, -12);
        word = Bitpack_news(word, 5, 13, -5);
        word = Bitpack_news(word, 5, 8, 13);
        
        printf("a is now %lu\n", Bitpack_getu(word, 9, 23));
        printf("b is now %ld\n", Bitpack_gets(word, 5, 18));
        

}




