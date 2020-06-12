#pragma once

// arithmetic operators
//            0x00xx
//       ADD  0x000x
#define BADD  0x0000
#define SADD  0x0001
#define IADD  0x0002
#define JADD  0x0003
#define FADD  0x0004
#define DADD  0x0005
              
//       SUB  0x001x
#define BSUB  0x0010
#define SSUB  0x0011
#define ISUB  0x0012
#define JSUB  0x0013
#define FSUB  0x0014
#define DSUB  0x0015
              
//       MUL  0x002x
#define BMUL  0x0020
#define SMUL  0x0021
#define IMUL  0x0022
#define JMUL  0x0023
#define FMUL  0x0024
#define DMUL  0x0025
              
//       DIV  0x003x
#define BDIV  0x0030
#define SDIV  0x0031
#define IDIV  0x0032
#define JDIV  0x0033
#define FDIV  0x0034
#define DDIV  0x0035

// logical
//            0x010x
#define ZAND  0x0100
#define ZOR   0x0101
#define ZNOT  0x0102
#define ZNAND 0x0103
#define ZNOR  0x0104
#define ZXOR  0x0105
#define ZXNOR 0x0106

// control flow
//            0x02xx
#define JMP   0x0200
#define CALL  0x0201
#define CMP   0x0202
#define JE    0x0203
#define JNE   0x0204
#define JG    0x0205
#define JGE   0x0206
#define JL    0x0207
#define JLE   0x0208
