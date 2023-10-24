/**
 * @file bitpacker.h
 * @author Jake Kerrigan, Jacob Frieman
 * @date 10/16/2023
 * 
 * @brief 
 *  This is the header file to bitpacker.c. It declares the public functions
 *  bitpacker and bitUnpacker that call the bitpacker interface to bitpack and
 *  unpack 2x2 blocks.
 **/

#ifndef BITPACKER
#define BITPACKER

#include <quantize.h>
#include <bitpack.h>

int bitPacker(WordFields_T input);

WordFields_T bitUnpacker(uint64_t input);




#endif