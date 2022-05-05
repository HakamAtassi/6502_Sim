#ifndef CPU_H_
#define CPU_H_

#include <vector>
#include <string>
#include "Memory.h"


class CPU
{
    Memory* ram;    //the system's memory
    

    uint8_t status;    //8 bit container for status register of the cpu. 
    uint8_t fetched;     //current fetched cycle. AKA the instruction currently being executed
    uint16_t PC;   //16 bit long PC (same size as an address)
    uint8_t stackptr;
    uint16_t absolute_address=0x0;

    //"Main" registers
    uint8_t X; //X reg
    uint8_t Y; //Y reg
    uint8_t A; //accumulator


    //helper members
    int cycles=0;
    int operand=0;
    std::string current_opcode;


    enum STATUS //status registers 
    {
        C=(1<<0), //Carry bit
		Z=(1<<1), //Zero
		I=(1<<2), //Disable Interrupts
		D=(1<<3), //Decimal Mode 
		B=(1<<4), //Break
		U=(1<<5), //unused
		V=(1<<6), //Overflow
		N=(1<<7), //Negative  
    };

    uint8_t GetFlag(STATUS S, int value); //returns a specific bit from the status register 
    void SetFlag(STATUS S, int value); //sets/resets a specific bit from the status register 


public:

    uint8_t fetch();   //fetches instruction
    uint8_t getOperand();
    void execute(); //exectures instruction based on lookup table.
    


    //Opcodes (all 56)
    uint8_t ADC(); uint8_t AND(); uint8_t ASL(); uint8_t BCC();
    uint8_t BCS(); uint8_t BEQ(); uint8_t BIT(); uint8_t BMI();
    uint8_t BNE(); uint8_t BPL(); uint8_t BRK(); uint8_t BVC();
    uint8_t BVS(); uint8_t CLC(); uint8_t CLD(); uint8_t CLI();
    uint8_t CLV(); uint8_t CMP(); uint8_t CPX(); uint8_t CPY();
    uint8_t DEC(); uint8_t DEX(); uint8_t DEY(); uint8_t EOR();
    uint8_t INC(); uint8_t INX(); uint8_t INY(); uint8_t JMP();
    uint8_t JSR(); uint8_t LDA(); uint8_t LDX(); uint8_t LDY();
    uint8_t LSR(); uint8_t NOP(); uint8_t ORA(); uint8_t PHA();
    uint8_t PHP(); uint8_t PLA(); uint8_t PLP(); uint8_t ROL();
    uint8_t ROR(); uint8_t RTI(); uint8_t RTS(); uint8_t SBC();
    uint8_t SEC(); uint8_t SED(); uint8_t SEI(); uint8_t STA();
    uint8_t STX(); uint8_t STY(); uint8_t TAX(); uint8_t TAY();
    uint8_t TSX(); uint8_t TXA(); uint8_t TXS(); uint8_t TYA();
    uint8_t XXX(); //illegal Opcodes


    void reset();   //resets micro
    void interrupt();   
    void nonMaskableInterrupt();


	//addressing modes: 16 modes available...12 used here. 
	uint8_t IMP();     uint8_t IMM();
	uint8_t ZP0();     uint8_t ZPX();
	uint8_t ZPY();     uint8_t REL();
	uint8_t ABS();     uint8_t ABX();
	uint8_t ABY();     uint8_t IND();
	uint8_t IZX();     uint8_t IZY(); 


    struct Instruction
    {
        std::string opcode_name;
        uint8_t (CPU::*opcode)(void);
        uint8_t (CPU::*addressing_mode)(void);
        int cycles;
    };
    

    std::vector<Instruction> lookup;


    CPU(Memory *_ram);
    uint8_t read(uint16_t Address);
    void write(short int Address, uint8_t Data);

    void dumpData(); //dumps all microprocessor data
    void dumpRegisters();
};

#endif