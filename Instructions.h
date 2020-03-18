#pragma once

#define HALT      0x00

// stack operations
#define SWAP      0x5f
#define DUP       0x59

// control flow
#define GOTO      0xa7
#define IFEQ      0x99
#define IFGE      0x9c
#define IFGT      0x9d
#define IFLE      0x9e
#define IFLT      0x9b
#define IFNE      0x9a

// functional
#define CALL      0xba
// call # of args, address
#define RETURN    0xb1
#define DRETURN   0xac
// returns data

#define FLOAD_0   0x22
#define FLOAD_1   0x23

// integer oprations
#define I2F       0x86
#define F2I       0x8b

#define IADD      0x60
#define ISUB      0x64
#define IMUL      0x68
#define IDIV      0x6c
#define INEG      0x74

#define ILDC      0x12
#define ICONST_M1 0x02
#define ICONST_0  0x03
#define ICONST_1  0x04
#define ICONST_2  0x05
#define ICONST_3  0x06
#define ICONST_4  0x07
#define ICONST_5  0x08