#pragma once

#include "defines.h"

#include "memory.h"

#define CPU_CARRY_FLAG 1
#define CPU_ZERO_FLAG 2
#define CPU_INTERRUPT_DISABLE 3
#define CPU_DECIMAL_MODE 4
#define CPU_BREAK_FLAG 5
#define CPU_OVERFLOW_FLAG 7
#define CPU_NEGATIVE_FLAG 8

class CPU {
public:
    void init(Memory &memory);
    void reset(Memory& memory);
    
    void execute(int cycles, Memory& memory);

    Word SPtoAddress();

    void setFlag(Byte bit, Bit value);

    void printInfo(Memory& memory);

private:
    Byte fetchBytes(int& cycles, Memory& memory);
    Word fetchWord(int& cycles, Memory& memory);

    Byte readByte(int& cycles, Word address, Memory& memory);
    Word readWord(int& cycles, Word address, Memory& memory);

    void writeByte(int& cycles, Byte byte, Word address, Memory& memory);
    void writeWord(int& cycles, Word word, Word address, Memory& memory);

    void pushByteStack(int& cycles, Byte byte, Memory& memory);
    void pushWordStack(int& cycles, Word word, Memory& memory);

    Byte popByteStack(int& cycles, Memory& memory);
    Word popWordStack(int& cycles, Memory& memory);


    void printInfoLine(Memory& memory, Word& cSP);

private:
    Word PC;
    Byte SP; // 0x0100 <=> 0x01FF

    Byte A, X, Y;


    // NV1BDIZC
    Byte PS;

};