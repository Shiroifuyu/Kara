#ifndef _CPU_H_
#define _CPU_H_
#include "Memory.h"

typedef struct regPair{
    uint8_t h;
    uint8_t l;

    regPair() : h(0x00), l(0x00) {}
    regPair(uint8_t h, uint8_t l) : h(h), l(l) {}
};

//af, bc, de, hl | sp, pc
//F Register contains flags [7,6,5,4,3,2,1,0] => [Z,N,H,C,0,0,0,0] 
struct Registers {
    regPair af, bc, de, hl;
    uint16_t sp, pc;

    Registers() : af(0x01, 0xB0), bc(0x00, 0x13), de(0x00, 0xd8), hl(0x01, 0x4d), sp(0xFFFE), pc(0x0000) {}; 
};

class Cpu {
    private:
        /*
            AF = 0x01B0;
            BC = 0x0013;
            DE = 0x00D8;
            HL = 0x014D;
            SP = 0xFFFE;
        */
        Memory memory;
        Registers registers;    
        bool doubleSpeed;
        const unsigned int CLOCK_SPEED = 4194304; // 4.194304 MHZ
    public:
        void modifyFlags();
        void handleInterrupts();
        void updateTiemers();
        void fetchInstruction();
        void halt();
        void on_reset();
        enum {
            VBLANCK_INTERRUPT,
            LCD_INTERRUPT,
            TIMER_INTERRUPT,
            JOYPAD_INTERRUPT
        };


        // OP CODES
        void SRL(uint8_t);
        void PUSH();
        void POP();
        void RET();
        void RETI();
        void JR();
        void JP();
        void SWAP();
        void AND();
        void OR();
        void XOR();
        void CP();
        void DEC();
        void INC();
        void RLC();
        void RRC();
        void RR();
        void RL();
        void DAA();
        void CALL();
        void ADDW();
        void ADD();
        void ADC();
        void SUB();
        void SBC();
        void SLA();
        void SRA();
        void BIT();
        void RES();
        void SET();
        void LD();
        void LDH();
        void LD_HL_SP_n();  // LD HL, SP+
};

#endif