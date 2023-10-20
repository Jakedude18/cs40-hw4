#include <bitpacker.h>
#include <stdint.h>
#include <mem.h>


int bitPacker(WordFields_T input){
        
        uint64_t word = 0;

        word = Bitpack_newu(word, 9, 23, (uint64_t) input->a);;
        word = Bitpack_news(word, 5, 18, (uint64_t) input->b);
        word = Bitpack_news(word, 5, 13, (uint64_t) input->c);
        word = Bitpack_news(word, 5, 8, (uint64_t) input->d);

        word = Bitpack_newu(word, 4, 4, (uint64_t) input->indexPB);
        word = Bitpack_newu(word, 4, 0, (uint64_t) input->indexPR);

        return (int) Bitpack_getu(word, 32, 0);

}


WordFields_T bitUnpacker(uint64_t word){
        
        WordFields_T unpackedWord = ALLOC(sizeof(struct WordFields));
        
        unpackedWord->a = Bitpack_getu(word, 9, 23);
        unpackedWord->b = Bitpack_gets(word, 5, 18);
        unpackedWord->c = Bitpack_gets(word, 5, 13);
        unpackedWord->d = Bitpack_gets(word, 5, 8);

        unpackedWord->indexPB = Bitpack_getu(word, 4, 4);
        unpackedWord->indexPR = Bitpack_getu(word, 4, 0);
        
        return unpackedWord;
}