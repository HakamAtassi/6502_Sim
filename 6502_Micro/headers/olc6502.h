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
	}



private:
	Bus *bus=nullptr;
	uint8_t read(uint16_t a);
	void write(uint16_t a, uint8_t d);
	

};
