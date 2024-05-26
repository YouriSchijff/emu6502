# 6502 Emulator

This repository is made using C++17.

For all instructions see [6502 Instruction reference](http://www.6502.org/users/obelisk/6502/instructions.html).

## Programming the CPU

Currently you must modify the src/main.cpp file.

<details>
    <summary>Example Code:</summary>

```C++
#include "6502/cpu.h"
#include "6502/instructions.h" 
// Check `6502/instructions.h` for all implemented instructions

int main(int argc, char** argv) {
    CPU cpu;
    Memory mem;
    cpu.init(mem);

    // A program that loads the number 43 into A
    std::vector<Byte> prog = {
        Instruction::LDA_IM, 43
    };

    mem.loadProgram(prog, 0x0000);

    // You can also code this way if you want more control
    /* 
    mem.ram[0x0000] = Instruction::LDA_IM;
    mem.ram[0x0001] = 43;
    */ 

    int cycleCount = 2; // Calculate or set it to MAX_MEMORY
    cpu.execute(cycleCount, mem);

    cpu.printInfo(mem);
    mem.printMemory();
    return 0;
}
```

</details>

## Information about the 6502

The 6502 has a stack from address `100` to address `1FF`.
The stack pointer starts at 255 and subtracts towards 0.

Force Interrupt (BRK) just returns for now. Proper interrupts will be provided in the future

## Inspiration

This project is inspired by [Dave Poo 6502 Emulation series](https://www.youtube.com/DavePoo) and by [Ben Eater's 6502 series](https://www.youtube.com/BenEater).

## To Do

- [ ] Restricted mode (Restrict writing the stack)
- [ ] All Load/Store Operations
- [x] All Register Transfers
- [x] All Stack Operations
- [ ] All Logical Operations
- [ ] All Arithmetic Operations
- [ ] All Increments & Decrements
- [ ] All Shifts
- [x] All Jumps & Calls
- [ ] All Branches
- [ ] All Status Flag Changes
- [ ] All System Functions