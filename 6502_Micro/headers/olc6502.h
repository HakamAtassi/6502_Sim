#pragma once

#include <cstdint>
class Bus;

//The 6502 consists of a few major components/registors
//The accumulator -> stores the results of arithmatic
//The X register
//the Y register ->X and Y are used for indexing
//Stack Pointer -> Used to keep track of the stack. Program counter stored within stack pointer. PC stores next operation to be excecuted
//Status register -> Stores status of the processor. See "FLAGS6502" Enum


class olc6502
{
	public:
	olc6502();
	~olc6502();

	void ConnectBus(Bus *n){bus=n;} //to Connect to bus 
		//this gives the cpu access to the ram by providing it with a 
		//pointer to it. 
	
	enum FLAGS6502 //This represents each bit in the Status register. 
	{ //Used to adress each bit by name rather than by indexing. 
		C=(1<<0), //Carry bit
		Z=(1<<1), //Zero
		I=(1<<2), //Disable Interrupts
		D=(1<<3), //Decimal Mode 
		B=(1<<4), //Break
		U=(1<<5), //unused
		V=(1<<6), //Overflow
		N=(1<<7), //Negative
	};

	uint8_t a=0x00; //accumulator
	uint8_t x=0x00; //x reg
	uint8_t y=0x00; //y reg
	uint8_t stkp= 0x00; //stack pointer
	uint8_t pc=0x0000; //prog counter
	uint8_t status=0x00; //status register (FLAGS6502)

	//Addressing Modes here
	
	//Opcodes
		//legal op codes here. 56 of them
	
		uint8_t XXX(); //illegal Opcodes


		void clock(); //simulate clock
		void reset();
		void irq(); //interrupt request 
		void nmi(); //non maskable interrupt



		//**HELPER FUNCTIONS BELOW**//

		uint8_t fetch();
		uint8_t fetched =0x00; //stores fetched data

		uint16_t addr_abs=0x0000; //address of memory being read from
		uint8_t addr_rel=0x00; //if branched, addr_rel stores the distance between PC and branch address

		uint8_t opcode=0x00; //current opcode being excecuted
		uint8_t cycles =0; //Cycle counter. some opcodes take several cycles to excecute...


		//opcode struct here. 



private:
	Bus *bus=nullptr;
	uint8_t read(uint16_t a);
	void write(uint16_t a, uint8_t d);
	
	//FLAGS6502 Helper functions
	uint8_t GetFlag(FLAGS6502 f);
	void SetFlag(FLAGS6502 f, bool v);


};
