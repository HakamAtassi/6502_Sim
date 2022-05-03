#ifndef CPU_H_
#define CPU_H_
#include <vector>
#include <string>
#include "Memory.h"
static constexpr MAX_MEM=64*1024;

class CPU
{



    Memory* ram=nullptr;    //the system's memory

    char status;    //8 bit container for status register of the cpu. 
    char fetched;     //current fetched cycle. AKA the instruction currently being executed
    unsigned int cycles;    //current number of clocks needed to execut the current instruction
    short int PC;   //16 bit long PC (same size as an address)
    char stackptr;

    //"Main" registers
    char X; //X reg
    char Y; //Y reg
    char A; //accumulator



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

    char GetFlag(); //returns a specific bit from the status register 
    char SetFlag(); //sets/resets a specific bit from the status register 

    char fetch();   //fetches instruction
    char execute(); //exectures instruction based on lookup table.




    //Opcodes (all 56)
    char ADC(); char AND(); char ASL(); char BCC();
    char BCS(); char BEQ(); char BIT(); char BMI();
    char BNE(); char BPL(); char BRK(); char BVC();
    char BVS(); char CLC(); char CLD(); char CLI();
    char CLV(); char CMP(); char CPX(); char CPY();
    char DEC(); char DEX(); char DEY(); char EOR();
    char INC(); char INX(); char INY(); char JMP();
    char JSR(); char LDA(); char LDX(); char LDY();
    char LSR(); char NOP(); char ORA(); char PHA();
    char PHP(); char PLA(); char PLP(); char ROL();
    char ROR(); char RTI(); char RTS(); char SBC();
    char SEC(); char SED(); char SEI(); char STA();
    char STX(); char STY(); char TAX(); char TAY();
    char TSX(); char TXA(); char TXS(); char TYA();
    char XXX(); //illegal Opcodes


    void reset();   //resets micro
    void interrupt();   
    void nonMaskableInterrupt();


	//addressing modes: 16 modes available...12 used here. 
	char IMP();     char IMM();
	char ZP0();     char ZPX();
	char ZPY();     char REL();
	char ABS();     char ABX();
	char ABY();     char IND();
	char IZX();     char IZY(); 


    struct Instruction
    {
        std::string opcode_name;
        char (CPU::*opcode)(void);
        char (CPU::*addressing_mode)(void);
        int cycles=0;
    };
    

    std::vector<Instruction> lookup;


    CPU();
    char read(short int Address);
    void write(short int Address, char Data);


};

#endif 