#pragma once

#include "defines.h"

namespace Instruction {
	// No Operation
	static constexpr Byte NOP		= 0xEA; // 1 Byte,  2 Cycles

	// Force Interrupt				B
	static constexpr Byte BRK		= 0x00; // 1 Bytes, 7 Cycles

	// Logical AND					Z,N
	static constexpr Byte AND_IM	= 0x29; // 2 Bytes, 2 Cycles
	static constexpr Byte AND_ZP	= 0x25; // 2 Bytes, 3 Cycles
	static constexpr Byte AND_ZPX	= 0x35; // 2 Bytes, 4 Cycles
	static constexpr Byte AND_AB	= 0x2D; // 3 Bytes, 4 Cycles
	static constexpr Byte AND_ABX	= 0x3D; // 3 Bytes, 4 Cycles (+1 if page crossed)
	static constexpr Byte AND_ABY	= 0x39; // 3 Bytes, 4 Cycles (+1 if page crossed)
	//static constexpr Byte AND_INX	= 0x21; // 2 Bytes, 6 Cycles
	//static constexpr Byte AND_INY	= 0x31; // 2 Bytes, 5 Cycles (+1 if page crossed)
	// Logical OR					Z,N
	static constexpr Byte ORA_IM	= 0x09; // 2 Bytes, 2 Cycles
	static constexpr Byte ORA_ZP	= 0x05; // 2 Bytes, 3 Cycles
	static constexpr Byte ORA_ZPX	= 0x15; // 2 Bytes, 4 Cycles
	static constexpr Byte ORA_AB	= 0x0D; // 3 Bytes, 4 Cycles
	static constexpr Byte ORA_ABX	= 0x1D; // 3 Bytes, 4 Cycles (+1 if page crossed)
	static constexpr Byte ORA_ABY	= 0x19; // 3 Bytes, 4 Cycles (+1 if page crossed)
	//static constexpr Byte ORA_INX	= 0x01; // 2 Bytes, 6 Cycles
	//static constexpr Byte ORA_INY	= 0x11; // 2 Bytes, 5 Cycles (+1 if page crossed)
	// Logical EOR					Z,N
	static constexpr Byte EOR_IM	= 0x49; // 2 Bytes, 2 Cycles
	static constexpr Byte EOR_ZP	= 0x45; // 2 Bytes, 3 Cycles
	static constexpr Byte EOR_ZPX	= 0x55; // 2 Bytes, 4 Cycles
	static constexpr Byte EOR_AB	= 0x4D; // 3 Bytes, 4 Cycles
	static constexpr Byte EOR_ABX	= 0x4D; // 3 Bytes, 4 Cycles (+1 if page crossed)
	static constexpr Byte EOR_ABY	= 0x59; // 3 Bytes, 4 Cycles (+1 if page crossed)
	//static constexpr Byte EOR_INX	= 0x41; // 2 Bytes, 6 Cycles
	//static constexpr Byte EOR_INY	= 0x41; // 2 Bytes, 5 Cycles (+1 if page crossed)

	// Load Accumulator				Z,N
	static constexpr Byte LDA_IM	= 0xA9; // 2 Bytes, 2 Cycles
	static constexpr Byte LDA_ZP	= 0xA5; // 2 Bytes, 3 Cycles
	static constexpr Byte LDA_ZPX	= 0xB5; // 2 Bytes, 4 Cycles
	static constexpr Byte LDA_AB	= 0xAD; // 3 Bytes, 4 Cycles
	static constexpr Byte LDA_ABX	= 0xBD; // 3 Bytes, 4 Cycles (+1 if page crossed)
	static constexpr Byte LDA_ABY	= 0xB9; // 3 Bytes, 4 Cycles (+1 if page crossed)
	// Load X Register				Z,N
	static constexpr Byte LDX_IM	= 0xA2; // 2 Bytes, 2 Cycles
	static constexpr Byte LDX_ZP	= 0xA6; // 2 Bytes, 3 Cycles
	static constexpr Byte LDX_ZPY	= 0xB6; // 2 Bytes, 4 Cycles
	static constexpr Byte LDX_AB	= 0xAE; // 3 Bytes, 4 Cycles
	static constexpr Byte LDX_ABY	= 0xBE; // 3 Bytes, 4 Cycles (+1 if page crossed)
	// Load Y Register				Z,N
	static constexpr Byte LDY_IM	= 0xA0; // 2 Bytes, 2 Cycles
	static constexpr Byte LDY_ZP	= 0xA4; // 2 Bytes, 3 Cycles
	static constexpr Byte LDY_ZPX	= 0xB4; // 2 Bytes, 4 Cycles
	static constexpr Byte LDY_AB	= 0xAC; // 3 Bytes, 4 Cycles
	static constexpr Byte LDY_ABX	= 0xBC; // 3 Bytes, 4 Cycles (+1 if page crossed)

	// Store Accumulator
	static constexpr Byte STA_ZP	= 0x85; // 2 Bytes, 3 Cycles
	static constexpr Byte STA_ZPX	= 0x95; // 2 Bytes, 4 Cycles
	static constexpr Byte STA_AB	= 0x8D; // 3 Bytes, 4 Cycles
	static constexpr Byte STA_ABX	= 0x9D; // 3 Bytes, 5 Cycles
	static constexpr Byte STA_ABY	= 0x99; // 3 Bytes, 5 Cycles
	//static constexpr Byte STA_INX	= 0x81; // 2 Bytes, 6 Cycles
	//static constexpr Byte STA_INY	= 0x91; // 2 Bytes, 6 Cycles
	// Store X Register
	static constexpr Byte STX_ZP	= 0x86; // 2 Bytes, 3 Cycles
	static constexpr Byte STX_ZPY	= 0x96; // 2 Bytes, 4 Cycles
	static constexpr Byte STX_AB	= 0x8E; // 3 Bytes, 4 Cycles
	// Store Y Register
	static constexpr Byte STY_ZP	= 0x84; // 2 Bytes, 3 Cycles
	static constexpr Byte STY_ZPX	= 0x94; // 2 Bytes, 4 Cycles
	static constexpr Byte STY_AB	= 0x8C; // 3 Bytes, 4 Cycles

	// Jump
	static constexpr Byte JMP_AB	= 0x4C; // 3 Bytes, 3 Cycles
	static constexpr Byte JMP_IN	= 0x6C; // 3 Bytes, 5 Cycles
	// Jump to Subroutine
	static constexpr Byte JSR		= 0x20; // 3 Bytes, 6 Cycles
	// Return from Subroutine
	static constexpr Byte RTS		= 0x60; // 1 Bytes, 6 Cycles

	// Transfer Stack Pointer to X	Z,N
	static constexpr Byte TSX		= 0xBA; // 1 Bytes, 2 Cycles
	// Transfer X to Stack Pointer
	static constexpr Byte TXS		= 0x9A; // 1 Bytes, 2 Cycles

	// Push Accumulator
	static constexpr Byte PHA		= 0x48; // 1 Bytes, 3 Cycles
	// Push Processor Status
	static constexpr Byte PHP		= 0x08; // 1 Bytes, 3 Cycles
	// Pull Accumulator				Z,N
	static constexpr Byte PLA		= 0x68; // 1 Bytes, 3 Cycles
	// Pull Processor Status		C,Z,I,D,B,V,N
	static constexpr Byte PLP		= 0x28; // 1 Bytes, 3 Cycles




	//
	// TODO: Implement These
	//
	
	/*
	// Add with Carry				C,Z,V,N
	static constexpr Byte ADC_IM	= 0x69; // 2 Bytes, 2 Cycles
	static constexpr Byte ADC_ZP	= 0x65; // 2 Bytes, 3 Cycles
	static constexpr Byte ADC_ZPX	= 0x75; // 2 Bytes, 4 Cycles
	static constexpr Byte ADC_AB	= 0x6D; // 3 Bytes, 4 Cycles
	static constexpr Byte ADC_ABX	= 0x7D; // 3 Bytes, 4 Cycles (+1 if page crossed)
	static constexpr Byte ADC_ABY	= 0x79; // 3 Bytes, 4 Cycles (+1 if page crossed)
	static constexpr Byte ADC_INX	= 0x61; // 2 Bytes, 6 Cycles
	static constexpr Byte ADC_INY	= 0x71; // 2 Bytes, 5 Cycles (+1 if page crossed)

	// Arithmetic Shift left		C,Z,N
	static constexpr Byte ASL_IM	= 0x0A; // 1 Bytes, 2 Cycles
	static constexpr Byte ASL_ZP	= 0x06; // 2 Bytes, 5 Cycles
	static constexpr Byte ASL_ZPX	= 0x16; // 2 Bytes, 6 Cycles
	static constexpr Byte ASL_AB	= 0x0E; // 3 Bytes, 6 Cycles
	static constexpr Byte ASL_ABX	= 0x1E; // 3 Bytes, 7 Cycles

	// Branch if Carry Clear
	static constexpr Byte BCC		= 0x90; // 2 Bytes, 2 Cycles (+1 if branch succeeds, +2 if to a new page)

	// Branch if Carry Set
	static constexpr Byte BCS		= 0xB0; // 2 Bytes, 2 Cycles (+1 if branch succeeds, +2 if to a new page)

	// Branch if Equal
	static constexpr Byte BEQ		= 0xF0; // 2 Bytes, 2 Cycles (+1 if branch succeeds, +2 if to a new page)

	// Bit test						Z,V,N
	static constexpr Byte BIT_ZP	= 0x24; // 2 Bytes, 3 Cycles
	static constexpr Byte BIT_AB	= 0x2C; // 3 Bytes, 4 Cycles

	// Branch if Minus
	static constexpr Byte BMI		= 0x30; // 2 Bytes, 2 Cycles (+1 if branch succeeds, +2 if to a new page)

	// Branch if Not Equal
	static constexpr Byte BNE		= 0xD0; // 2 Bytes, 2 Cycles (+1 if branch succeeds, +2 if to a new page)

	// Branch if Positive
	static constexpr Byte BPL		= 0x10; // 2 Bytes, 2 Cycles (+1 if branch succeeds, +2 if to a new page)

	// Branch if Overflow Clear
	static constexpr Byte BVC		= 0x50; // 2 Bytes, 2 Cycles (+1 if branch succeeds, +2 if to a new page)

	// Branch if Overflow Set
	static constexpr Byte BVS		= 0x70; // 2 Bytes, 2 Cycles (+1 if branch succeeds, +2 if to a new page)

	// Clear Carry Flag				C
	static constexpr Byte CLC		= 0x18; // 1 Bytes, 2 Cycles

	// Clear Decimal Mode			D
	static constexpr Byte CLD		= 0xD8; // 1 Bytes, 2 Cycles

	// Clear Interrupt Flag			I
	static constexpr Byte CLI		= 0x58; // 1 Bytes, 2 Cycles

	// Clear Overflow Flag			V
	static constexpr Byte CLV		= 0xB8; // 1 Bytes, 2 Cycles

	// Compare						C,Z,N
	static constexpr Byte CMP_IM	= 0x69; // 2 Bytes, 2 Cycles
	static constexpr Byte CMP_ZP	= 0x65; // 2 Bytes, 3 Cycles
	static constexpr Byte CMP_ZPX	= 0x75; // 2 Bytes, 4 Cycles
	static constexpr Byte CMP_AB	= 0x6D; // 3 Bytes, 4 Cycles
	static constexpr Byte CMP_ABX	= 0x7D; // 3 Bytes, 4 Cycles (+1 if page crossed)
	static constexpr Byte CMP_ABY	= 0x79; // 3 Bytes, 4 Cycles (+1 if page crossed)
	static constexpr Byte CMP_INX	= 0x61; // 2 Bytes, 6 Cycles
	static constexpr Byte CMP_INY	= 0x71; // 2 Bytes, 5 Cycles (+1 if page crossed)
	*/
}