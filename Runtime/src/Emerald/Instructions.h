#pragma once

#define NOP    0xFFFF
#define HALT   0xFFFE

// arithmetic operators
//             0x00xx
//       ADD   0x000x
#define BADD   0x0000
#define SADD   0x0001
#define IADD   0x0002
#define JADD   0x0003
#define FADD   0x0004
#define DADD   0x0005
               
//       SUB   0x001x
#define BSUB   0x0010
#define SSUB   0x0011
#define ISUB   0x0012
#define JSUB   0x0013
#define FSUB   0x0014
#define DSUB   0x0015
               
//       MUL   0x002x
#define BMUL   0x0020
#define SMUL   0x0021
#define IMUL   0x0022
#define JMUL   0x0023
#define FMUL   0x0024
#define DMUL   0x0025
               
//       DIV   0x003x
#define BDIV   0x0030
#define SDIV   0x0031
#define IDIV   0x0032
#define JDIV   0x0033
#define FDIV   0x0034
#define DDIV   0x0035
               
// logical     
//             0x010x
#define ZAND   0x0100
#define ZOR    0x0101
#define ZNOT   0x0102
#define ZNAND  0x0103
#define ZNOR   0x0104
#define ZXOR   0x0105
#define ZXNOR  0x0106

// control flow
//             0x020x
#define JMP    0x0200
#define CALL   0x0201
#define JE     0x0202
#define JNE    0x0203
#define JG     0x0204
#define JGE    0x0205
#define JL     0x0206
#define JLE    0x0207
#define RET    0x0208
#define BCMP   0x0209
#define SCMP   0x020A
#define ICMP   0x020B
#define JCMP   0x020C
#define FCMP   0x020D
#define DCMP   0x020E



// operand stack operations
//             0x02xx
#define BPUSH  0x0220
#define SPUSH  0x0221
#define IPUSH  0x0222
#define JPUSH  0x0223
#define FPUSH  0x0224
#define DPUSH  0x0225
#define ZPUSH  0x0226
#define CPUSH  0x0227
#define BPOP   0x0230
#define SPOP   0x0231
#define IPOP   0x0232
#define JPOP   0x0233
#define FPOP   0x0234
#define DPOP   0x0235
#define ZPOP   0x0236
#define CPOP   0x0237
// pointer operations
#define BGET   0x0240
#define SGET   0x0241
#define IGET   0x0242
#define JGET   0x0243
#define FGET   0x0244
#define DGET   0x0245
#define ZGET   0x0246
#define CGET   0x0247
#define BPUT   0x0250
#define SPUT   0x0251
#define IPUT   0x0252
#define JPUT   0x0253
#define FPUT   0x0254
#define DPUT   0x0255
#define ZPUT   0x0256
#define CPUT   0x0257
// local var stack operations with arithmetic
//             0x026x
#define LDO    0x0260
#define LEA    0x0261

// load effective address

// register access
//             0x030x
#define ACCRIP 0x0300
#define ACCRSP 0x0301
#define ACCRBP 0x0302
#define PUTRSP 0x0303
#define PUTRBP 0x0304
