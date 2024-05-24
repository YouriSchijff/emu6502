#include "memory.h"

#include "instructions.h"

#include <iostream>

void Memory::init() {
	for (uint32_t i = 0; i < MAX_MEMORY; i++)
		ram[i] = Instruction::NOP;

	ram[0xFFFB] = Instruction::BRK;
	ram[0xFFFC] = Instruction::JMP_AB;
	ram[0xFFFD] = 0x00;
	ram[0xFFFE] = 0x00;
}

void Memory::loadProgram(std::vector<Byte> program, Word offset) {

	if (program.size() + offset >= 0xFFFB) {
		printf("Program + offset is out of bounds");
		return;
	}

	for(int i = 0; i < program.size(); i++) {
		ram[i + offset] = program[i];
	}
}

void Memory::printMemory() {

	printf("\n========================================================================================================================\n\n");

	Byte previous[16] = { 0xea };
	Byte now[16];

	Word address = 0x0000;

	Word lastPrint = 0x0000;

	for (int j = 0; j < MAX_MEMORY / 16; j++) {
		
		for (Byte i = 0; i < 16; i++) {
			now[i] = ram[address + i];
		}

		for (Byte i = 0; i < 16; i++) {
			if (now[i] != previous[i]) {

				
				if(lastPrint+0x10 != address && address != 0x0000)
					printf("*\n");

				printLine(address);

				previous[0] = now[0];
				previous[1] = now[1];
				previous[2] = now[2];
				previous[3] = now[3];
				previous[4] = now[4];
				previous[5] = now[5];
				previous[6] = now[6];
				previous[7] = now[7];
				previous[8] = now[8];
				previous[9] = now[9];
				previous[10] = now[10];
				previous[11] = now[11];
				previous[12] = now[12];
				previous[13] = now[13];
				previous[14] = now[14];
				previous[15] = now[15];

				lastPrint = address;

				break;
			}
		}

		address += 0x10;
	}

	printf("\n========================================================================================================================\n\n");
}

void Memory::printLine(Word address) {

	Word add = (address >> 4) << 4;

	printf("%04X  ", add);

	for(Byte i = 0; i < 8; i++) {
		Byte byte = ram[add + i];

		if (byte == 0xEA)
			printf("\x1b[90m%02x\x1b[0m ", byte);
		else
			printf("%02x ", byte);
	}

	for (Byte i = 8; i < 16; i++) {
		Byte byte = ram[add + i];

		if (byte == 0xEA)
			printf("\x1b[90m%02x\x1b[0m ", byte);
		else
			printf("%02x ", byte);
	}

	printf(" ");

	for (Byte i = 0; i < 16; i++) {
		Byte byte = ram[add + i];

		if (byte >= 0x20 && byte != 0xEA) {
			printf("%c", byte);
			continue;
		}

		printf("\x1b[90m.\x1b[0m");
	}

	printf("\n");
}