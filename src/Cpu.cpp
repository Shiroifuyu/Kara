#include "Cpu.h"
#include <string>
void Cpu::on_reset() {

}

void Cpu::fetchInstruction() {
    uint8_t opcode = memory.read_byte(registers.pc++);
    string cc;
    switch(opcode) {
        case 0x00: // NOP
            registers.pc++;
            break;
        case 0x01: // LD BC,d16       //LD BC, 0x0000
            memory.read_byte(registers.pc++);
            break;
        case 0xC3: // JP d16          // pc <- d16
            uint8_t d16_l = memory.read_byte(registers.pc++);       //TODO: Encapsule the 16bit word retrieval from memory in a single function
            uint8_t d16_h = memory.read_byte(registers.pc++);
            uint16_t d16 = (d16_h << 8) | d16_l;
            registers.pc = d16;
        case 0xE9: // JP HL
            registers.pc = regPair_to_word(registers.hl);
            break;
        
        case 0xC2: cc = "NZ";   // JP NZ, d16 
        case 0xD2: cc = "NC";   // JP NC, d16 
        case 0xCA: cc = "C";    // JP C, d16 
        case 0xDA: cc = "Z";    //JP Z, d16 
            uint8_t d16_l = memory.read_byte(registers.pc++);
            uint8_t d16_h = memory.read_byte(registers.pc++);
            uint16_t d16 = (d16_h << 8) | d16_l;
            
            //if(registers.af.l.check_flag(cc)) TODO: Implement flag checking on register F
            //    registers.pc = d16;

            break;

        case 0x18:  // JP r
            uint8_t r = memory.read_byte(registers.pc++);   //TODO: REVISE SIGNED ARITHMETIC, MAY BE OFF SINCE R IS A SIGNED VALUE AND WE'RE USING UNSIGNED 8 BIT VALUES FOR THE MEMORY
            registers.pc += r;
            break;
        case 0x20: cc = "NZ"; 
        case 0x30: cc = "NC"; 
        case 0x28: cc = "Z"; 
        case 0x38:cc = "C";
            uint8_t r = memory.read_byte(registers.pc++);
            
            //if(registers.af.l.check_flag(cc)) TODO: Implement flag checking on register F
            //    registers.pc += r;

        case 0xCD: // CALL d16
            uint8_t d16_l = memory.read_byte(registers.pc++);
            uint8_t d16_h = memory.read_byte(registers.pc++);
            uint16_t d16 = (d16_h << 8) | d16_l;

            uint8_t pc_l = * ((uint8_t*)&registers.pc);
            uint8_t pc_h = * ((uint8_t*)((&registers.pc) + 1));

            memory.write_byte(--registers.sp, pc_h);
            memory.write_byte(--registers.sp, pc_l);
            registers.pc = d16;
    }
}

uint16_t Cpu::regPair_to_word(regPair hl) {
    uint16_t rp = ((hl.h) << 8) | hl.l;
    return rp;
}