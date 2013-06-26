#include "main.h"
#include "emoticons.h"

/*
  Definitions of few emoticons with 8X8 resolutions.
  The pixels are selected as follows:

el
  7 h0 h1 h2 h3 h4 h5 h6 h7
  6 g0 g1 g2 g3 g4 g5 g6 g7
  5 f0 f1 f2 f3 f4 f5 f6 f7
  4 e0 e1 e2 e3 e4 e5 e6 e7
  3 d0 d1 d2 d3 d4 d5 d6 d7
  2 c0 c1 c2 c3 c4 c5 c6 c7
  1 b0 b1 b2 b3 b4 b5 b6 b7
  0 a0 a1 a2 a3 a4 a5 a6 a7
arr[0, 1, 2, 3, 4, 5, 6, 7]

So:
arr[0] = a0<<7 | b0<<6 | c0<<5 | d0<<4 | e0<<3 | f0<<2 | g0<<1 | h0<<0
arr[1] = a1<<7 | b1<<6 | c1<<5 | d1<<4 | e1<<3 | f1<<2 | g1<<1 | h1<<0
etc.

If you want a different orientation of the picture
you should use the function Set_Matrix_Rotate with the respective angle.
*/

/*
const unsigned char Laugh[8] = {0x43, 0xC3, 0xC0, 0xCE, 0xCE, 0xC0, 0xC3, 0x43};    // 0 degrees
const unsigned char Happy[8] = {0x66, 0x86, 0x80, 0x9C, 0x9C, 0x80, 0x86, 0x66};    // 0 degrees
const unsigned char Smile[8] = {0x46, 0x86, 0x80, 0x9C, 0x9C, 0x80, 0x86, 0x46};    // 0 degrees
const unsigned char None[8]  = {0x03, 0x03, 0x40, 0x4E, 0x4E, 0x40, 0x03, 0x03};    // 0 degrees
*/

const unsigned char Laugh[8] = {0x32, 0x61, 0xC2, 0xC8, 0xC8, 0xC2, 0x61, 0x32};    // 0 degrees
const unsigned char Happy[8] = {0x32, 0x42, 0x80, 0x88, 0x88, 0x80, 0x42, 0x32};    // 0 degrees
const unsigned char Smile[8] = {0x22, 0x42, 0x40, 0x48, 0x48, 0x40, 0x42, 0x22};    // 0 degrees
const unsigned char None[8]  = {0x02, 0x02, 0x40, 0x48, 0x48, 0x40, 0x02, 0x02};    // 0 degrees

//const unsigned char Angry[8] = {0x86, 0x46, 0x40, 0x5C, 0x5C, 0x40, 0x46, 0x86};    // 0 degrees
const unsigned char Angry[8] = {0x00, 0x66, 0x18, 0x18, 0x18, 0x00, 0x7E, 0x81};    // 90 degrees
