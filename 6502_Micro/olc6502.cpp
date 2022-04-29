#include "headers/olc6502.h"
#include <cstdint>
#include <opencl-c-base.h>
#include <sys/types.h>
#include "headers/Bus.h"


olc6502::olc6502()
{
	using a=olc6502; //to make code more readable. a is an olc6502 object. 
	//helps make defining function pointers easier. 
		
	//lookup is essentially a table with all possible opcodes of the micro. It stores all data outlined in INSTRUCTION. 
	//NOTE: "???" are invalid opcodes.

	lookup = 
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
}



olc6502::~olc6502()
{
}


uint8_t olc6502::read(uint16_t a)
{
	return bus->read(a,false); //reads from the provided address the data on the bus
}


void olc6502::write(uint16_t address,uint8_t d)
{
	bus->write(address,d);
}


void olc6502::clock()
{
	/**cycles variable stores the number of requires clock cycles. if its greater than 0, it will do the operation, but the next few calls wont do anything until cycles is back to 0.**/

	if(cycles==0) //no cycles have occured.
	{
		opcode=read(pc);
		pc++;
		
		cycles=lookup[opcode].cycles;
		uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)(); //calls addrmode
		//"this" has pointer called lookup that is addressed by opcode number. 
		//that vector stores a function pointer that is used to call the (corrispodning) addrmode function. 

		uint8_t additional_cycle2 = (this->*lookup[opcode].operate)();

		cycles +=(additional_cycle2 & additional_cycle1);

	}

	cycles--;

}

void olc6502::SetFlag(FLAGS6502 f, bool v)
{
	if(v) //if v is 1, set flag (toggle on)
	{
		status |=f;
	}
	else //if v is 0, reset flag (toggle of)
	{
		status &= ~f; //0b1111 & !0001 = 1110, (toggle off bit mask) 
	}
}


// addressing modes

uint8_t olc6502::IMP() //implied addressing directly stores the data into the accumulator "a" 
{
	fetched =a;
	return 0;
}
uint8_t olc6502::IMM() 
{
	addr_abs = pc++; //The address of the data is stored in memory directly
	//fetch address then post increment
	return 0;
}


//Zero page addressing
//0xFF55 as an example
//8 MSB are referred to as "page"
//8 LSB are rererred to as "offset"
//hence, memory can be mapped as 256 pages, 256 offsets
//
uint8_t olc6502::ZP0() //used for addressing first 256 bytes of data in the system. 
{
	addr_abs = read(pc); 
	pc++;
	addr_abs &=0x00FF; //clear first t bytes since it can only be in first page
	return 0;
}

uint8_t olc6502::ZPX() 
{
	addr_abs=(read(pc)+x); //x is x register on processor 
												// add value in x to contents of read memory
	pc++; 								
	addr_abs &=0x00FF;

	//this one is slightly tricky. The pc points to a memory address. That memory address could be, for example, the address to an array. 
	//To index each element in that array, the value "X" can be added to that original addess fetched from PC. 
	//This effectivly enables addressing values indexed away from an original base address
	//This is exactly of arrays work in C++

	return 0;
}

uint8_t olc6502::ZPY() 
{

	//read explination for ZPX. Its the same
	addr_abs=(read(pc)+y); //y is y register on processor
												// add value in y to contents of read memory
	pc++;
	addr_abs &=0x00FF;
	return 0;
}

uint8_t olc6502::ABS()
{

	//if the instruction directly refers to the opcode, it wont fit in the standard instruction size
	//This is since memory is only 16 bits wide, but an address is 16 bits on its own.
	//This is not a problem in the above addressing modes since the address is discovered after that instruction is fetched
	//But if you want the full address in the instruction, absolute addressing si required. 

	uint16_t lo=read(pc);
	pc++;
	uint16_t hi=read(pc);
	pc++;

	addr_abs=(hi<<8) | lo;


	//this functions as follows:
	//go to memory location => you are told to fetch data from specific address
	//that place in memory will store the lower 8 bits. The next place in memory will store the upper 8 bits. 
	//PS. the 6502 is little endian. 
	return 0;
}


uint8_t olc6502::ABX()
{

	//Very similar to ZPX. It also increments a value "x" from a base address. 	//The only difference is that, instead of incrementing x from the pc, you increment from an absolute address provided in the instruction. 

	uint8_t lo =read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi<<8) | lo;
	addr_abs +=x;

	if((addr_abs & 0xFF00) != (hi<<8)) //return 1 if a new memory page is entered
	{
		return 1;
	}
	else 
	{
		return 0;
	}

}


uint8_t olc6502::ABY()
{
	//see above explination. Same applies but for Y register
	uint8_t lo =read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi<<8) | lo;
	addr_abs +=y;

	if((addr_abs & 0xFF00) != (hi<<8))
	{
		return 1;
	}
	else 
	{
		return 0;
	}

}


uint8_t olc6502::IND() //indirect addressing
{
	//Goes to an address in memory that contains an address in memory. 
	//Since an address wont fit in a single index of memory, it needs to split it across 2. 
	uint16_t ptr_lo =read(pc);
	pc++;
	uint16_t ptr_hi=read(pc);
	pc++;

	uint16_t ptr = (ptr_hi << 8 ) | ptr_lo; 

	//Above would normally be enough for indirect addressing.
	//however, the NES has a bug that incorrectly incremented the pointer if it entered a new page. 

	if (ptr_lo == 0x00FF) //simulate bug
	{
		addr_abs=(read(ptr & 0xFF00)<<8) | read(ptr+0);
	}
	else 
	{
		addr_abs =(read(ptr +1)<<8) | read (ptr+0);
	}

	return 0;
}

uint8_t olc6502::IZX()
{
	uint16_t t=read(pc);
	pc++;


	uint16_t lo=read((uint16_t)(t+(uint16_t)x)&0x00FF);
	uint16_t hi = read((uint16_t)(t+(uint16_t)x+1)&0x00FF);

	addr_abs=(hi<<8) | lo;

	return 0;
}

uint8_t olc6502::IZY()
{
	uint16_t t=read(pc);
	pc++;

	uint16_t lo=read(t+0x00FF);
	uint16_t hi = read((t+1) & 0x00FF);

	addr_abs = (hi<<8) | lo;
	addr_abs +=y;

	if((addr_abs & 0xFF00)!=(hi<<8))
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}


uint8_t olc6502::REL()
{
	addr_rel=read(pc);
	pc++;
	if (addr_rel & 0x80)
	{
		addr_rel |= 0xFF00;
	}
	return 0;
}

//Instructions


uint8_t olc6502::fetch()
{
	if (!(lookup[opcode].addrmode ==&olc6502::IMP)) //for all instructions except implied
	{
		fetched = read(addr_abs);
	}
	return fetched;
}

uint8_t olc6502::AND()
{
	fetch();
	a=a&fetched;
	SetFlag(Z,a==0x00);
	SetFlag(N,a&0x80); //if bit z is 1, then the number is negative
	return 1; //return indicates if more clocks might be required for the insrtuction
}

uint8_t olc6502::BCS() //branch if carry is set instrction.
{
	if (GetFlag(C)==1)
	{
		cycles++; //if a branch is required, add another clock automatrically
		addr_abs=pc+addr_rel; //branches can only branch a small distance relative to current address
		//addr_rel is the offset from base address addr_abs
		if((addr_abs&0xFF00)!= (pc & 0xFF00)) //if a new page is crossed
		{
			cycles++; //add another clock cycle
		}
	pc=addr_abs; //set pc to the branch address. 
	}
	return 0;
}

uint8_t olc6502::BCC() //branch if carry clear
{
	if (GetFlag(C)==0)
	{
		cycles++; //if a branch is required, add another clock automatrically
		addr_abs=pc+addr_rel; //branches can only branch a small distance relative to current address
		//addr_rel is the offset from base address addr_abs
		if((addr_abs&0xFF00)!= (pc & 0xFF00)) //if a new page is crossed
		{
			cycles++; //add another clock cycle
		}
	pc=addr_abs; //set pc to the branch address. 
	}
	return 0;
}
uint8_t olc6502::BEQ()
{
		if (GetFlag(Z)==1) //if number is 0.
			//subbtracts the compared number from loaded number. If result is 0, its equal. 
	{
		cycles++; //if a branch is required, add another clock automatrically
		addr_abs=pc+addr_rel; //branches can only branch a small distance relative to current address
		//addr_rel is the offset from base address addr_abs
		if((addr_abs&0xFF00)!= (pc & 0xFF00)) //if a new page is crossed
		{
			cycles++; //add another clock cycle
		}
	pc=addr_abs; //set pc to the branch address. 
	}
	return 0;
}

uint8_t olc6502::BMI() //branch if negative
{
	if (GetFlag(N)==1)
	{
		cycles++; //if a branch is required, add another clock automatrically
		addr_abs=pc+addr_rel; //branches can only branch a small distance relative to current address
		//addr_rel is the offset from base address addr_abs
		if((addr_abs&0xFF00)!= (pc & 0xFF00)) //if a new page is crossed
		{
			cycles++; //add another clock cycle
		}
	pc=addr_abs; //set pc to the branch address. 
	}
	return 0;
}

uint8_t olc6502::BNE() //branch if not equal. 
	//branches if the result of subtraction is not 0
{
	if (GetFlag(Z)==0)
	{
		cycles++; //if a branch is required, add another clock automatrically
		addr_abs=pc+addr_rel; //branches can only branch a small distance relative to current address
		//addr_rel is the offset from base address addr_abs
		if((addr_abs&0xFF00)!= (pc & 0xFF00)) //if a new page is crossed
		{
			cycles++; //add another clock cycle
		}
	pc=addr_abs; //set pc to the branch address. 
	}
	return 0;
}

uint8_t olc6502::BPL() //Branch if positive	
{
	if (GetFlag(N)==0)
	{
		cycles++; //if a branch is required, add another clock automatrically
		addr_abs=pc+addr_rel; //branches can only branch a small distance relative to current address
		//addr_rel is the offset from base address addr_abs
		if((addr_abs&0xFF00)!= (pc & 0xFF00)) //if a new page is crossed
		{
			cycles++; //add another clock cycle
		}
	pc=addr_abs; //set pc to the branch address. 
	}
	return 0;
}

uint8_t olc6502::BVC() //branch if Overflow
{
	if (GetFlag(V)==0)
	{
		cycles++; //if a branch is required, add another clock automatrically
		addr_abs=pc+addr_rel; //branches can only branch a small distance relative to current address
		//addr_rel is the offset from base address addr_abs
		if((addr_abs&0xFF00)!= (pc & 0xFF00)) //if a new page is crossed
		{
			cycles++; //add another clock cycle
		}
	pc=addr_abs; //set pc to the branch address. 
	}
	return 0;
}

uint8_t olc6502::BVS() //branch if not Overflow
{
	if (GetFlag(V)==1)
	{
		cycles++; //if a branch is required, add another clock automatrically
		addr_abs=pc+addr_rel; //branches can only branch a small distance relative to current address
		//addr_rel is the offset from base address addr_abs
		if((addr_abs&0xFF00)!= (pc & 0xFF00)) //if a new page is crossed
		{
			cycles++; //add another clock cycle
		}
	pc=addr_abs; //set pc to the branch address. 
	}
	return 0;
}

uint8_t olc6502::CLC() //set carry bit
{
	SetFlag(C,false);
	return 0;
}

uint8_t olc6502::CLD() //set carry bit
{
	SetFlag(D,false);
	return 0;
}

uint8_t olc6502::CLV() //set carry bit
{
	SetFlag(C,false);
	return 0;
}


uint8_t olc6502::CLI() //set carry bit
{
	SetFlag(I,false);
	return 0;
}

uint8_t olc6502::ADC() 
{
//for this function, it is important to consider overflows.
//if a posative number is added to a another posative number, and the result is negative, a overflow occured. 
//The same is true for negative and negative addition
//negative posative addition will never overflow
//We need to check when an overflow has occured through a logical operation to set the overflow flag accordingly. 
	fetch();

	uint16_t temp= (uint16_t)a+(uint16_t)fetched + (uint16_t)GetFlag(C); //adds two numbers and potential flag from previous addition
	SetFlag(C,temp>255);
	//carry is set if c is greater than 255
	SetFlag(Z,(temp & 0x00FF)==0);
	//zero is set if its zero
	
	SetFlag(N,temp & 0x80);
	//negative is set if msb of temp (result) is 1

	SetFlag(V,(~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp))& 0x0080); //this is the logic that determines the state of the overflow flag previously mentioned
	//overflow is not the same as carry. 
	//Overflow is is related to the sign bit. A carry is just a carry (>|255|)
	
	a=temp&0x00FF;
	return 1;
}

uint8_t olc6502::SBC()
{
	//subtraction can be implemented very similarly to addition
	//A=A-M-(1-C). 1-C is the borrow bit
	//A=A+-M+1+C
	fetch();
	uint16_t value=((uint16_t)fetched) ^ 0x00FF;

	uint16_t temp= (uint16_t)a+(uint16_t)fetched + (uint16_t)GetFlag(C); //adds
	SetFlag(C,temp>255);
	SetFlag(Z,(temp & 0x00FF)==0);
	SetFlag(N,temp & 0x80);
	SetFlag(V,(~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp))& 0x0080); 
}

uint8_t olc6502::PHA() //push accumulator to stack
{
	write(0x0100 +stkp, a);
	stkp--;
	return 0;
}


