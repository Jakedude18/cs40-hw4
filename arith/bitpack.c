#include <bitpack.h>
#include <stdio.h>
#include <assert.h>
#include <except.h>

Except_T Bitpack_Overflow = { "Overflow packing bits" };

static uint64_t twosCompliment(int64_t input);
static uint64_t makeMask(unsigned width, unsigned lsb);
static uint64_t newHelper(uint64_t word, unsigned width, unsigned lsb, uint64_t value);

bool Bitpack_fitsu(uint64_t n, unsigned width){
        if(width == 0){
                return 0;
        }
        return (n >> width) == 0;
}

bool Bitpack_fitss(int64_t n, unsigned width){
        if(width == 0){
                return false;
        }
        if(n == 0){
                return true;
        }
        if(n < 0){
                return (twosCompliment(n) >> (width - 1)) == 0;
        }
        return (n >> (width - 1)) == 0;

}

uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb){
        if(width == 0){
                return 0;
        }
        assert((width + lsb) <= 64);
        assert(lsb <= 63);
        //make a mask
        uint64_t mask = makeMask(width, lsb);
        return (mask & word) >> lsb;
}

int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb){

        uint64_t notsigned = Bitpack_getu(word, width, lsb);
        if(Bitpack_fitss(notsigned, width)){
                return notsigned;
        }
        else{
                uint64_t rMask = ~0;
                rMask = rMask >> (64 - width);
                return -((int64_t) (twosCompliment(notsigned) + 1) & rMask);
        }
}

uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t value){
        if(!Bitpack_fitsu(value, width)){
                RAISE(Bitpack_Overflow);
        }
        assert(width <= 64);
        assert(width + lsb <= 64);
        return newHelper(word, width, lsb, value);
        
}

uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb,  int64_t value){
        if(!Bitpack_fitss(value, width)){
                RAISE(Bitpack_Overflow);
        }
        assert(width <= 64);
        assert(width + lsb <= 64);
        return newHelper(word, width, lsb, (uint64_t)value);
}

static uint64_t newHelper(uint64_t word, unsigned width, unsigned lsb, uint64_t value){
        //make a mask
        uint64_t mask = makeMask(width, lsb);
        mask = ~mask;
        word = word & mask;

        value = value << lsb;

        word = word | value;

        return word;
}

static uint64_t makeMask(unsigned width, unsigned lsb){
        //make a mask
        uint64_t mask_l = ~0;
        mask_l = mask_l << (width + lsb);
        uint64_t mask_r = ~0;
        mask_r = mask_r << lsb;
        mask_r = ~mask_r;
        uint64_t mask = ~(mask_l | mask_r);
        return mask;
}

static uint64_t twosCompliment(int64_t input){
        return ~input;
}


