#include "cpu.h"

#include "instructions.h"

#include <iostream>

void CPU::init(Memory &memory) {
	reset(memory);
}

void CPU::reset(Memory &memory) {
	PC = 0xFFFC;
	SP = 0xFF;

	PS = 32;

	A = 0;
	X = 0;
	Y = 0;

	memory.init();
}

// Gets byte in location PC. Cycle 1
Byte CPU::fetchBytes(int& cycles, Memory &memory) {
	Byte byte = memory.ram[PC];
	PC++;

	cycles--;
	
	return byte;
}

// Gets word in location PC. Cycle 2
Word CPU::fetchWord(int& cycles, Memory& memory) {
	// 6502 is Little Endian
	Word word = memory.ram[PC];
	PC++;

	word |= (memory.ram[PC] << 8);
	PC++;

	cycles -= 2;

	return word;
}

// Reads byte from address. Cycle 1
Byte CPU::readByte(int& cycles, Word address, Memory& memory) {
	Byte byte = memory.ram[address];

	cycles--;

	return byte;
}

// Reads word from address. Cycle 2
Word CPU::readWord(int& cycles, Word address, Memory& memory) {
	Word word = memory.ram[address];
	word |= (memory.ram[address+1] << 8);

	cycles -= 2;

	return word;
}

// Writes byte to address. Cycle 1
void CPU::writeByte(int& cycles, Byte byte, Word address, Memory& memory) {
	memory.ram[address] = byte;

	cycles--;
}

// Writes word to address. Cycle 2
void CPU::writeWord(int& cycles, Word word, Word address, Memory& memory) {
	memory.ram[address] = word & 0xFF;
	memory.ram[address + 1] = (word >> 8);

	cycles -= 2;
}

// Pushes a byte to the stack. Cycle 2
void CPU::pushByteStack(int& cycles, Byte byte, Memory& memory) {
	memory.ram[SPtoAddress()] = byte;
	SP--;

	cycles -= 2;
}

// Pushes a word to the stack. Cycle 3
void CPU::pushWordStack(int& cycles, Word word, Memory& memory) {
	memory.ram[SPtoAddress()-1] = word & 0xFF;
	memory.ram[SPtoAddress()] = (word >> 8);
	SP -= 2;

	cycles -= 3;
}

// Pop a byte from the stack. Cycle 2
Byte CPU::popByteStack(int& cycles, Memory& memory) {
	Byte byte = memory.ram[SPtoAddress() + 1];
	SP++;

	cycles -= 2;

	return byte;
}

// Pops a word from the stack. Cycle 3
Word CPU::popWordStack(int& cycles, Memory& memory) {
	Word word = memory.ram[SPtoAddress() + 1];
	word |= (memory.ram[SPtoAddress() + 2] << 8);
	SP += 2;

	cycles -= 3;

	return word;
}

void CPU::execute(int cycles, Memory &memory) {
	while (cycles > 0) {
		bool handled = false;

		Byte instruction = fetchBytes(cycles, memory);

		if (instruction == Instruction::NOP) {
			cycles--;

			handled = true;
			continue;
		}

		if (instruction == Instruction::BRK) {
			setFlag(CPU_BREAK_FLAG, 1);
			cycles-= 6;

			handled = true;
			return;
		}

		if (instruction == Instruction::LDA_IM) { 
			A = fetchBytes(cycles, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);
			
			handled = true;
			continue;
		}
		if (instruction == Instruction::LDA_ZP) {
			Word address = fetchBytes(cycles, memory);
			A = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);
			
			handled = true;
			continue;
		}
		if (instruction == Instruction::LDA_ZPX) {
			Word address = fetchBytes(cycles, memory);
			address += X;
			cycles--;
			A = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);
			
			handled = true;
			continue;
		}
		if (instruction == Instruction::LDA_AB) {
			Word address = fetchWord(cycles, memory);
			A = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDA_ABX) {
			Word address = fetchWord(cycles, memory);
			address += X;
			A = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDA_ABY) {
			Word address = fetchWord(cycles, memory);
			address += Y;
			A = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		
		if (instruction == Instruction::LDX_IM) {
			X = fetchBytes(cycles, memory);
			setFlag(CPU_ZERO_FLAG, (X == 0));
			setFlag(CPU_NEGATIVE_FLAG, (X & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDX_ZP) {
			Word address = fetchBytes(cycles, memory);
			X = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (X == 0));
			setFlag(CPU_NEGATIVE_FLAG, (X & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDX_ZPY) {
			Word address = fetchBytes(cycles, memory);
			address += Y;
			X = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (X == 0));
			setFlag(CPU_NEGATIVE_FLAG, (X & 0b10000000) > 0);

			cycles--;

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDX_AB) {
			Word address = fetchWord(cycles, memory);
			X = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (X == 0));
			setFlag(CPU_NEGATIVE_FLAG, (X & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDX_ABY) {
			Word address = fetchWord(cycles, memory);
			address += Y;
			X = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (X == 0));
			setFlag(CPU_NEGATIVE_FLAG, (X & 0b10000000) > 0);

			handled = true;
			continue;
		}

		if (instruction == Instruction::LDY_IM) {
			Y = fetchBytes(cycles, memory);
			setFlag(CPU_ZERO_FLAG, (Y == 0));
			setFlag(CPU_NEGATIVE_FLAG, (Y & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDY_ZP) {
			Word address = fetchBytes(cycles, memory);
			Y = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (Y == 0));
			setFlag(CPU_NEGATIVE_FLAG, (Y & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDY_ZPX) {
			Word address = fetchBytes(cycles, memory);
			address += X;
			cycles--;
			Y = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (Y == 0));
			setFlag(CPU_NEGATIVE_FLAG, (Y & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDY_AB) {
			Word address = fetchWord(cycles, memory);
			Y = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (Y == 0));
			setFlag(CPU_NEGATIVE_FLAG, (Y & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::LDY_ABX) {
			Word address = fetchWord(cycles, memory);
			address += X;
			Y = readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (Y == 0));
			setFlag(CPU_NEGATIVE_FLAG, (Y & 0b10000000) > 0);

			handled = true;
			continue;
		}

		if (instruction == Instruction::STA_ZP) {
			Word address = fetchBytes(cycles, memory);
			writeByte(cycles, A, address, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::STA_ZPX) {
			Word address = fetchBytes(cycles, memory);
			address += X;
			cycles--;
			writeByte(cycles, A, address, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::STA_AB) {
			Word address = fetchWord(cycles, memory);
			writeByte(cycles, A, address, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::STA_ABX) {
			Word address = fetchWord(cycles, memory);
			address += X;
			cycles--;
			writeByte(cycles, A, address, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::STA_ABY) {
			Word address = fetchWord(cycles, memory);
			address += Y;
			cycles--;
			writeByte(cycles, A, address, memory);

			handled = true;
			continue;
		}

		if (instruction == Instruction::STX_ZP) {
			Word address = fetchBytes(cycles, memory);
			writeByte(cycles, X, address, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::STX_ZPY) {
			Word address = fetchBytes(cycles, memory);
			address += Y;
			cycles--;
			writeByte(cycles, X, address, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::STX_AB) {
			Word address = fetchWord(cycles, memory);
			writeByte(cycles, X, address, memory);

			handled = true;
			continue;
		}
		
		if (instruction == Instruction::STY_ZP) {
			Word address = fetchBytes(cycles, memory);
			writeByte(cycles, Y, address, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::STY_ZPX) {
			Word address = fetchBytes(cycles, memory);
			address += X;
			cycles--;
			writeByte(cycles, Y, address, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::STY_AB) {
			Word address = fetchWord(cycles, memory);
			writeByte(cycles, Y, address, memory);

			handled = true;
			continue;
		}

		if (instruction == Instruction::JMP_AB) {
			Word address = fetchWord(cycles, memory);
			PC = address;

			handled = true;
			continue;
		}
		if (instruction == Instruction::JMP_IN) {
			Word address = fetchWord(cycles, memory);
			address = readWord(cycles, address, memory);
			PC = address;

			handled = true;
			continue;
		}
		if (instruction == Instruction::JSR) {
			Word address = fetchWord(cycles, memory);
			pushWordStack(cycles, PC - 1, memory);

			PC = address;

			handled = true;
			continue;
		}
		if (instruction == Instruction::RTS) {
			Word address = popWordStack(cycles, memory);
			PC = address + 0x1;
			
			cycles -= 2;

			handled = true;
			continue;
		}

		if (instruction == Instruction::TSX) {
			X = SP;
			setFlag(CPU_ZERO_FLAG, (X == 0));
			setFlag(CPU_NEGATIVE_FLAG, (X & 0b10000000) > 0);

			cycles--;

			handled = true;
			continue;
		}
		if (instruction == Instruction::TXS) {
			SP = X;

			cycles--;

			handled = true;
			continue;
		}

		if (instruction == Instruction::PHA) {
			pushByteStack(cycles, A, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::PHP) {
			pushByteStack(cycles, PS, memory);

			handled = true;
			continue;
		}
		if (instruction == Instruction::PLA) {
			A = popByteStack(cycles, memory);

			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::PLP) {
			PS = popByteStack(cycles, memory);

			handled = true;
			continue;
		}

		if (instruction == Instruction::AND_IM) {
			A &= fetchBytes(cycles, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::AND_ZP) {
			Word address = fetchBytes(cycles, memory);
			A &= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::AND_ZPX) {
			Word address = fetchBytes(cycles, memory);
			address += X;
			cycles--;
			A &= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::AND_AB) {
			Word address = fetchWord(cycles, memory);
			A &= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::AND_ABX) {
			Word address = fetchWord(cycles, memory);
			address += X;
			A &= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::AND_ABY) {
			Word address = fetchWord(cycles, memory);
			address += Y;
			A &= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}

		if (instruction == Instruction::ORA_IM) {
			A |= fetchBytes(cycles, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::ORA_ZP) {
			Word address = fetchBytes(cycles, memory);
			A |= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::ORA_ZPX) {
			Word address = fetchBytes(cycles, memory);
			address += X;
			cycles--;
			A |= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::ORA_AB) {
			Word address = fetchWord(cycles, memory);
			A |= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::ORA_ABX) {
			Word address = fetchWord(cycles, memory);
			address += X;
			A |= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::ORA_ABY) {
			Word address = fetchWord(cycles, memory);
			address += Y;
			A |= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}

		if (instruction == Instruction::EOR_IM) {
			A ^= fetchBytes(cycles, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::EOR_ZP) {
			Word address = fetchBytes(cycles, memory);
			A ^= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::EOR_ZPX) {
			Word address = fetchBytes(cycles, memory);
			address += X;
			cycles--;
			A ^= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::EOR_AB) {
			Word address = fetchWord(cycles, memory);
			A ^= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::EOR_ABX) {
			Word address = fetchWord(cycles, memory);
			address += X;
			A ^= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}
		if (instruction == Instruction::EOR_ABY) {
			Word address = fetchWord(cycles, memory);
			address += Y;
			A ^= readByte(cycles, address, memory);
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			handled = true;
			continue;
		}

		if (instruction == Instruction::TAX) {
			X = A;
			setFlag(CPU_ZERO_FLAG, (X == 0));
			setFlag(CPU_NEGATIVE_FLAG, (X & 0b10000000) > 0);

			cycles--;

			handled = true;
			continue;
		}
		if (instruction == Instruction::TAY) {
			Y = A;
			setFlag(CPU_ZERO_FLAG, (Y == 0));
			setFlag(CPU_NEGATIVE_FLAG, (Y & 0b10000000) > 0);

			cycles--;

			handled = true;
			continue;
		}
		if (instruction == Instruction::TXA) {
			A = X;
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			cycles--;

			handled = true;
			continue;
		}
		if (instruction == Instruction::TYA) {
			A = Y;
			setFlag(CPU_ZERO_FLAG, (A == 0));
			setFlag(CPU_NEGATIVE_FLAG, (A & 0b10000000) > 0);

			cycles--;

			handled = true;
			continue;
		}

		if(!handled) {
			printf("Instruction at 0x%X not handled. 0x%X : %d\n", PC, instruction, instruction);
			return;
		}
	}
}

Word CPU::SPtoAddress() {
	return 0x100 | SP;
}

void CPU::setFlag(Byte bit, Bit value) {
	if(bit == 6) // Bit 6 is always 1
		return;
	PS = (PS & ~(1 << value)) | (value << bit-1);
}

void CPU::printInfo(Memory& memory) {

	Word cSP = 0x1C0;
	
	printf("\n========================================================================================================================\n\n");
	printf("Registers");
	printf("\t\t\t\t| Inner state\n");
	printf("   A = %d\t: 0x%x", A, A);
	printf("\t\t\t|   Program Counter = 0x%04X : %d\n", PC, PC);
	printf("   X = %d\t: 0x%x", X, X);
	printf("\t\t\t|\n");
	printf("   Y = %d\t: 0x%x", Y, Y);
	printf("\t\t\t|   Stack Pointer = 0x%X : %d\n", SPtoAddress(), SPtoAddress());
	printf("\t\t\t\t\t|\n");
	printf("Stack     ( 0x1C0 <==> 0x1FF )");
	printf("\t\t|   Flags = %d : 0x%x\n", PS, PS);
	printInfoLine(memory, cSP);
	printf("\t|     Carry     = %d\n", PS & 0b00000001);
	printInfoLine(memory, cSP);
	printf("\t|     Zero      = %d\n", PS & 0b00000010);
	printInfoLine(memory, cSP);
	printf("\t|     Interrupt = %d\n", PS & 0b00000100);
	printInfoLine(memory, cSP);
	printf("\t|     Decimal   = %d\n", PS & 0b00001000);
	printInfoLine(memory, cSP);
	printf("\t|     Break     = %d\n", PS & 0b00010000);
	printInfoLine(memory, cSP);
	printf("\t|     NOT USED  = %d\n", PS & 0b00100000);
	printInfoLine(memory, cSP);
	printf("\t|     Overflow  = %d\n", PS & 0b01000000);
	printInfoLine(memory, cSP);
	printf("\t|     Negative  = %d\n", PS & 0b10000000);
	printf("\n========================================================================================================================\n\n");
}

void CPU::printInfoLine(Memory& memory, Word &cSP) {
	printf("  %04X  ", cSP );

	for (Word i = 0; i < 4; i++) {
		Byte byte = memory.ram[cSP+i];
		
		if (byte == 0xEA) {
			printf("\x1b[90m%02x \x1b[0m", byte);
			continue;
		}
		
		printf("%02x ", byte);
	}
	printf(" ");
	for (Word i = 4; i < 8; i++) {
		Byte byte = memory.ram[cSP+i];

		if (byte == 0xEA) {
			printf("\x1b[90m%02x \x1b[0m", byte);
			continue;
		}

		printf("%02x ", byte);
	}
	cSP += 0x08;
	printf(" %04X ", cSP);
}