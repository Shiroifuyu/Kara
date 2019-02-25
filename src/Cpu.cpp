#include "Cpu.h"

void Cpu::on_reset() {

}

void Cpu::fetchInstruction() {
    uint8_t op = memory.read_byte(registers.pc);

    switch(op) {
        case 0x00: // NOP
            registers.pc++;
            break;
        case 0x01: // LD BC,d16       //LD BC, 0x0000
            memory.read_byte(registers.pc++);

            /*
            	word Memory::read_word(const word addr) {
		            return ((read_byte(addr + 1) << 8) | read_byte(addr));
                }
            */
    }
}