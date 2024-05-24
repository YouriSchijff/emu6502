#include "6502/cpu.h"
#include "6502/instructions.h"

int main(int argc, char** argv) {
	CPU cpu;
	Memory mem;
	cpu.init(mem);

	std::vector<Byte> prog = {
		Instruction::LDA_IM, 43, Instruction::JMP_AB, 0x00, 0x80
	};

	mem.loadProgram(prog, 0x0010);

	mem.ram[0xFFFD] = 0x10;
	mem.ram[0xFFFE] = 0x00;

	int cycleCount = MAX_MEMORY;
	cpu.execute(cycleCount, mem);

	cpu.printInfo(mem);
	mem.printMemory();
	return 0;
}