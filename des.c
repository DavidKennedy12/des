/*
** David Kennedy
*/

/* 
** bithacks.h - bit hacks macros. v1.0
** Peteris Krumins (peter@catonmat.net)
** http://www.catonmat.net
** Released under the MIT license.
*/
#ifndef BITHACKS_H
#define BITHACKS_H
/* test if n-th bit in x is set */
#define B_IS_SET(x, n)   (((x) & ((uint64_t)1<<(n)))?1:0)
/* set n-th bit in x */
#define B_SET(x, n)      ((x) |= ((uint64_t)1<<(n)))
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//The 16 round keys to be used
const uint64_t keys[16] =
  {
    0b100110110000001011101111111111000111000001110010, 
    0b011110011010111011011001110110111100100111100101,
    0b010101011111110010001010010000101100111110011001,
    0b011100101010110111010110110110110011010100011101,
    0b011111001110110000000111111010110101001110101000,
    0b011000111010010100111110010100000111101100101111,
    0b111011001000010010110111111101100001100010111100,
    0b111101111000101000111010110000010011101111111011,
    0b111000001101101111101011111011011110011110000001,
    0b101100011111001101000111101110100100011001001111,
    0b001000010101111111010011110111101101001110000110,
    0b011101010111000111110101100101000110011111101001,
    0b100101111100010111010001111110101011101001000001,
    0b010111110100001110110111111100101110011100111010,
    0b101111111001000110001101001111010011111100001010,
    0b110010110011110110001011000011100001011111110101
  };

const int InitialPermutation[64] = 
  {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7   
  };

  const int FinalPermutation[64] = 
  { 
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25  
  };

  const int ExpansionPermutation[] =  {
    32, 1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
  };

  const int sbox[8][4][16] = {
   {
   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
   { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
   { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
   {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   },
 
   {
   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
   { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
   { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
   {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
   },
 
   {
   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
   {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
   {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
   { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   },
 
   {
   { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
   {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
   {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
   { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   },
 
   {
   { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
   {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
   { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
   {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   },
 
   {
   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
   {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
   { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
   { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   },
 
   {
   { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
   {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
   { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
   { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   },
 
   {
   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
   { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
   { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
   { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
   },
  };

  const int pbox[32] = {
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
  };

void initial_permutation(uint32_t v[2]);
void final_permutation(uint32_t v[2]);
uint64_t expansion_permutation(uint32_t v);
uint32_t s_box_substitution(uint64_t v);
void p_box_permutation(uint32_t v);
void des_enc(uint32_t v[2], uint32_t const key[2]);
void des_dec(uint32_t v[2], uint32_t const key[2]);

void hexdump_to_string(const void *data, int size, char *str) {
    const unsigned char *byte = (unsigned char *)data;
    while (size > 0) {
    size--;
    sprintf(str, "%.2x ", *byte);
    byte++;
    str+=2;
    }
}

int main (int argc, char **argv)
{
  //open file pointers
	FILE *msg_fp = fopen("message.txt", "r");
  FILE *encrypted_msg_fp = fopen("encrypted_msg.bin", "wb");;
  FILE *decrypted_msg_fp = fopen("decrypted_msg.txt", "w"); 

  //read message from file
  char *msg = (char *)malloc(sizeof(char)*8); //message is exactly 8 bytes long
  fread(msg, 1, 8, msg_fp);
  uint32_t v[2];
  memcpy(&v[0], &msg[0], 4);
  memcpy(&v[1], &msg[4], 4); 
  free(msg);

  //encrypt message and write to encrypted_msg.bin
  des_enc(v, NULL);
  char *str = (char *)malloc(sizeof(char) * 16);
  hexdump_to_string(&v, 8, str);
  fwrite(str, 1, 16, encrypted_msg_fp);
  free(str);
  
  //decrypt message and write to decrypted_msg.bin
  des_dec(v, NULL);
  fwrite(v, 1, 8, decrypted_msg_fp);

  //close file pointers
  fclose(msg_fp);
  fclose(encrypted_msg_fp);
  fclose(decrypted_msg_fp);

  return 0;
}

//Encypts the plaintext using DES with predefined round keys
void des_enc(uint32_t v[2], uint32_t const key[2])
{
  uint32_t v0;
  uint32_t v1;
  uint64_t R;
  uint32_t new_block;
  uint64_t round_key;

  initial_permutation(v);

  //the 16 rounds
  for(int i = 0; i < 16; i++) {
    round_key = keys[i] << 16; //shifted so padding is at the rear
    
    //the f function
    R = (expansion_permutation(v[1])); //Expand R to 48 bits
    R = R ^ round_key; //XOR the expanded R and the round key

    //Send the result through 8 S-boxes using the S-Box Substitution to get 32 new bits, and store in "new_block"
    new_block = s_box_substitution(R);
    p_box_permutation(new_block);

    v0 = v[1]; //left value comes from the initial right value
    v1 = v[0] ^ new_block; //right value comes from initial left value XORed with right value after being run through f
    v[0] = v0; //update the new left and right values
    v[1] = v1;
  }
  
  //Fiestel cipher final swap
  v0 = v[1];
  v1 = v[0];
  v[0] = v0;
  v[1] = v1;

  final_permutation(v);
  return;
}

//Decrypts the cipher text. Runs exactly the same as encryption but round key order is reversed
void des_dec(uint32_t v[2], uint32_t const key[2])
{
  uint32_t v0;
  uint32_t v1;
  uint64_t R;
  uint32_t new_block;
  uint64_t round_key;

  initial_permutation(v);

  for(int i = 15; i >= 0; i--) {
    round_key = keys[i] << 16;
    
    R = (expansion_permutation(v[1]));
    R = R ^ round_key;

    new_block = s_box_substitution(R);
    p_box_permutation(new_block);

    v0 = v[1];
    v1 = v[0] ^ new_block;
    v[0] = v0;
    v[1] = v1;
  }

  v0 = v[1];
  v1 = v[0];
  v[0] = v0;
  v[1] = v1;

  final_permutation(v);
  return;
}

void initial_permutation(uint32_t v[2]) 
{
  uint64_t temp = v[0];
  temp = temp << (uint64_t)32;
  temp += v[1];
  uint64_t final = 0;
                                    
  for(int i = 0; i < 64; i++) {
    if(B_IS_SET(temp, 64 - InitialPermutation[i])) {
      B_SET(final, 64 - (i+1));
    }   
  }
  v[0] = final >> 32; 
  v[1] = final;
  return;
}

void final_permutation(uint32_t v[2]) 
{
  uint64_t temp = v[0];
  temp = temp << (uint64_t)32;
  temp += v[1];
  uint64_t final = 0;
                                    
  for(int i = 0; i < 64; i++) {
    if(B_IS_SET(temp, 64 - FinalPermutation[i])) {
      B_SET(final, 64 - (i+1));
    }   
  }
  v[0] = final >> 32;
  v[1] = final;
  return;
}

//Expands the 32 bits to 48 bits
uint64_t expansion_permutation(uint32_t v) 
{
  uint64_t expanded = 0;
  for(int i = 0; i < 48; i++) {
    if(B_IS_SET(v, 32 - ExpansionPermutation[i])) {
      B_SET(expanded, 64 - (i+1));
    }
  }
 return expanded;
}

//Compresses the 48 bits to 32 bits
uint32_t s_box_substitution(uint64_t v)
{
  uint8_t block;
  uint8_t row;
  uint8_t column;
  uint32_t result = 0;

  for(int i = 0; i < 8; i++) {
    block = v >> (uint64_t)(56 - (6*i));
    block = block & 0b11111100; //removes last 2 bits leaving 6 bits
    row = 0;
    column = 0;
    row = ( (block >> 6) &  0b00000010 ) | ( (block >> 2) &  0b00000001 ); //first bit and the 6th bit create a 2 bit row number
    column = (block >> 3) & 0b00001111; //the middle 4 bits create the column number
    result = result << 4; //shift result left to make space for next 4 bits
    result = result | sbox[i][row][column];
  }
  return result;
}

void p_box_permutation(uint32_t v) 
{
  uint32_t temp = v;
  uint32_t final = 0;                                   
  for(int i = 0; i < 32; i++) {
    if(B_IS_SET(temp, 32 - pbox[i])) {
      B_SET(final, 32 - (i+1));
    }   
  }
  v = final;
  return;
}