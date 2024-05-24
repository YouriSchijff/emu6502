#pragma once

#include "defines.h"

#include <vector>

#define MAX_MEMORY 65536

class Memory {
public:
	void init();

	void loadProgram(std::vector<Byte> program, Word offset);

	void printMemory();
	void printLine(Word address);

public:
	Byte ram[MAX_MEMORY];
};