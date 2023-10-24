/**
 * @file bitpack.h
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 * This is the header file to bitpack.c. It declares functions
 * Bitpack_fitsu, Bitpack_fitss, Bitpack_getu, Bitpack_gets, Bitpack_newu,
 * and Bitpack_news. The functions are called for bitpacking values into an 
 * integer and unpacking values from a bitpacked integer.
 **/

#ifndef BITPACK_INCLUDED
#define BITPACK_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#include "except.h"
bool Bitpack_fitsu(uint64_t n, unsigned width);
bool Bitpack_fitss( int64_t n, unsigned width);
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb);
 int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb);
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t value);
uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb,  int64_t value);
extern Except_T Bitpack_Overflow;

#endif
