#include "CPU.h"
#include <iostream>



/**OPERTAIONS BELOW**/


uint8_t CPU::LDA() 
{

		
		uint8_t operand=ram->read(absolute_address);
		A=operand;
		SetFlag(Z,(operand==0));
		SetFlag(N,!((operand&0x80)==0));
		return 0;
}

uint8_t CPU::ADC()
{
    return 0;
};
uint8_t CPU::AND()
{

		uint8_t operand=ram->read(absolute_address);
		A=A&operand;
		SetFlag(N,((A&0x80)>0)); 
		SetFlag(Z,(A==0)); 
		return 0;
}; 
uint8_t CPU::ASL()  //double check this. Also double check that absolute_address value is being maintained correctly. 
{

    if(lookup[fetched].addressing_mode==&CPU::IMP) //if addressing mode is implied then act on accumulator
    {
        A=A<<1;
    }
    else
    {
        write(absolute_address,ram->read(absolute_address)<<1);
    }
    return 0;
}; 
uint8_t CPU::BCC()  //branch if carry clear
{
    if(GetFlag(C)==0)
    {
        PC=absolute_address;    //branching means setting the absolute address
    }
    return 0;
};

uint8_t CPU::BCS()
{
        if(GetFlag(C)==1)
    {
        PC=absolute_address;    //branching means setting the absolute address
    }
    return 0;
}; 
uint8_t CPU::BEQ()  //branch if zero
{
        if(GetFlag(Z)==1)
    {
        PC=absolute_address;    //branching means setting the absolute address
    }
    return 0;
};

uint8_t CPU::BNE()
{
    if(GetFlag(Z)==0)
    {
        PC=absolute_address;    //branching means setting the absolute address
    }
    return 0;
}; 
uint8_t CPU::BIT()
{}; 
uint8_t CPU::BMI()
{
    if(GetFlag(N)==1)
    {
        PC=absolute_address;    //branching means setting the absolute address
    }
    return 0;
};
uint8_t CPU::BPL()
{
    if(GetFlag(N)==0)
    {
        PC=absolute_address;    //branching means setting the absolute address
    }
    return 0;
}; 
uint8_t CPU::BRK(){}; 

uint8_t CPU::BVC() //branch overflow clear
{
    if(GetFlag(V)==0)
    {
        PC=absolute_address;    //branching means setting the absolute address
    }
    return 0;
};
uint8_t CPU::BVS()  //branch overflow set
{
    if(GetFlag(V)==1)
    {
        PC=absolute_address;    //branching means setting the absolute address
    }
    return 0;
}; 
uint8_t CPU::CLC()
{
    SetFlag(C, 0);
    return 0;
}; 
uint8_t CPU::CLD()
{
    SetFlag(D, 0);
    return 0;
}; 
uint8_t CPU::CLI()
{
    SetFlag(I, 0);
    return 0;
};
uint8_t CPU::CLV()
{
    SetFlag(V, 0);
    return 0;
}; 

uint8_t CPU::CMP()  //sets flags as if a subtration took place. 
{

		//do a subtraction and store it in temp. set flags according to temp
		uint16_t operand=ram->read(absolute_address);
		uint16_t temp=A-operand;
		SetFlag(C,A>=operand);
		SetFlag(Z,(temp & 0x00FF)==0x0000);
		SetFlag(N,temp & 0x0080);
}; 
uint8_t CPU::CPX()
{
    
		uint16_t operand=ram->read(absolute_address);
		uint16_t temp=X-operand;
		SetFlag(C,X>=operand);
		SetFlag(Z,(temp & 0x00FF)==0x0000);
		SetFlag(N,temp & 0x0080);
}; 
uint8_t CPU::CPY()
{

		uint16_t operand=ram->read(absolute_address);
		uint16_t temp=Y-operand;
		SetFlag(C,Y>=operand);
		SetFlag(Z,(temp & 0x00FF)==0x0000);
		SetFlag(N,temp & 0x0080);
};
uint8_t CPU::DEC() //decrement
{
    uint16_t temp=ram->read(absolute_address)-1;
    ram->write(absolute_address,temp);
	SetFlag(Z,(temp & 0x00FF)==0x0000);
	SetFlag(N,temp & 0x0080);
}; 
uint8_t CPU::DEX()
{
    uint16_t temp=X-1;
    X=temp;
	SetFlag(Z,(temp & 0x00FF)==0x0000);
	SetFlag(N,temp & 0x0080);
}; 
uint8_t CPU::DEY()
{
    uint16_t temp=Y-1;
    Y=temp;
	SetFlag(Z,(temp & 0x00FF)==0x0000);
	SetFlag(N,temp & 0x0080);
}; 
uint8_t CPU::EOR()  //exclusive or of operand and accumulator
{
		
		uint16_t operand=ram->read(absolute_address);
		A=A^operand;
		SetFlag(Z, A == 0x00);
		SetFlag(N, A & 0x80); //and with 1000 0000. if negative it will return non 0. 
		return 0;
};

uint8_t CPU::INC() //increment memory location
{  
    uint16_t temp=ram->read(absolute_address)+1;
    ram->write(absolute_address,temp);
	SetFlag(Z,(temp & 0x00FF)==0x0000);
	SetFlag(N,temp & 0x0080);
}; 
uint8_t CPU::INX()
{
    uint16_t temp=X-1;
    X=temp;
	SetFlag(Z,(temp & 0x00FF)==0x0000);
	SetFlag(N,temp & 0x0080);
}; 
uint8_t CPU::INY()
{
    uint16_t temp=Y-1;
    Y=temp;
	SetFlag(Z,(temp & 0x00FF)==0x0000);
	SetFlag(N,temp & 0x0080);
}; 
uint8_t CPU::JMP()
{
    PC=absolute_address;
    return 0;
};
uint8_t CPU::JSR() //jump to sub routine
{

}; 

uint8_t CPU::LDX()  //load into register X
{

		uint16_t operand=ram->read(absolute_address);
		X=operand;
		SetFlag(Z,(operand==0));
		SetFlag(N,!(operand&10000000==0));
		return 0;
}; 

uint8_t CPU::LDY()
{

		uint16_t operand=ram->read(absolute_address);
		Y=operand;
		SetFlag(Z,(operand==0));
		SetFlag(N,!(operand&10000000==0));
		return 0;
};

uint8_t CPU::LSR()
{

}; 
uint8_t CPU::NOP() //no operation
{
    return 0;
}; 
uint8_t CPU::ORA()  //bitwise or with accum.
{

		uint16_t operand=ram->read(absolute_address);
		A=A | operand;
		SetFlag(Z,(A==0));
		SetFlag(N,!(A&10000000==0));
};
uint8_t CPU::PHA()  //push accum to stack
{

};
uint8_t CPU::PHP()  //push processor status
{

}; 
uint8_t CPU::PLA() //pull accum 
{

}; 
uint8_t CPU::PLP() //pull processor status
{

}; 

uint8_t CPU::TSX() //Transfer stack ptr to x
{

}; 
uint8_t CPU::TXS() //Transfer x to stack ptr
{

};


uint8_t CPU::ROL() //ROL shifts all bits left one position. The Carry is shifted into bit 0 and the original bit 7 is shifted into the Carry.
{

};

uint8_t CPU::ROR() //ROR shifts all bits right one position. The Carry is shifted into bit 7 and the original bit 0 is shifted into the Carry.
{

}; 
uint8_t CPU::RTI()
{

}; 
uint8_t CPU::RTS()
{

}; 
uint8_t CPU::SBC()
{

};
uint8_t CPU::SEC()
{

}; 
uint8_t CPU::SED()
{

}; 
uint8_t CPU::SEI()
{

}; 
uint8_t CPU::STA() //store accum in memory
{
    write(absolute_address,A);
};
uint8_t CPU::STX()
{
    write(absolute_address,X);
}; 
uint8_t CPU::STY()
{
    write(absolute_address,Y);
}; 
uint8_t CPU::TAX() //transfer accum to X
{
    X=A;
    SetFlag(N,(X&0x80)>0);
    SetFlag(Z,(X==0));
}; 
uint8_t CPU::TAY()
{
    Y=A;
    SetFlag(N,(Y&0x80)>0);
    SetFlag(Z,(Y==0));
};

uint8_t CPU::TXA()  //transfer X to accum
{
    A=X;
    SetFlag(N,(A&0x80)>0);
    SetFlag(Z,(A==0));
}; 

uint8_t CPU::TYA()
{
    A=Y;
    SetFlag(N,(Y&0x80)>0);
    SetFlag(Z,(Y==0));
};
uint8_t CPU::XXX()
{

}; //illegal Opcodes




CPU::CPU(Memory *_ram)
{
	lookup = //these values have to be hardcoded. there is no other way around it. Each op code has a few possible adderssing mode and number of clocks
    {
		{ "BRK", &CPU::BRK, &CPU::IMM, 7 },{ "ORA", &CPU::ORA, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::ZP0, 3 },{ "ASL", &CPU::ASL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHP", &CPU::PHP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::IMM, 2 },{ "ASL", &CPU::ASL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABS, 4 },{ "ASL", &CPU::ASL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BPL", &CPU::BPL, &CPU::REL, 2 },{ "ORA", &CPU::ORA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ZPX, 4 },{ "ASL", &CPU::ASL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLC", &CPU::CLC, &CPU::IMP, 2 },{ "ORA", &CPU::ORA, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABX, 4 },{ "ASL", &CPU::ASL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "JSR", &CPU::JSR, &CPU::ABS, 6 },{ "AND", &CPU::AND, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "BIT", &CPU::BIT, &CPU::ZP0, 3 },{ "AND", &CPU::AND, &CPU::ZP0, 3 },{ "ROL", &CPU::ROL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLP", &CPU::PLP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::IMM, 2 },{ "ROL", &CPU::ROL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "BIT", &CPU::BIT, &CPU::ABS, 4 },{ "AND", &CPU::AND, &CPU::ABS, 4 },{ "ROL", &CPU::ROL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BMI", &CPU::BMI, &CPU::REL, 2 },{ "AND", &CPU::AND, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ZPX, 4 },{ "ROL", &CPU::ROL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEC", &CPU::SEC, &CPU::IMP, 2 },{ "AND", &CPU::AND, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ABX, 4 },{ "ROL", &CPU::ROL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTI", &CPU::RTI, &CPU::IMP, 6 },{ "EOR", &CPU::EOR, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::ZP0, 3 },{ "LSR", &CPU::LSR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHA", &CPU::PHA, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::IMM, 2 },{ "LSR", &CPU::LSR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::ABS, 3 },{ "EOR", &CPU::EOR, &CPU::ABS, 4 },{ "LSR", &CPU::LSR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVC", &CPU::BVC, &CPU::REL, 2 },{ "EOR", &CPU::EOR, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ZPX, 4 },{ "LSR", &CPU::LSR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLI", &CPU::CLI, &CPU::IMP, 2 },{ "EOR", &CPU::EOR, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ABX, 4 },{ "LSR", &CPU::LSR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTS", &CPU::RTS, &CPU::IMP, 6 },{ "ADC", &CPU::ADC, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ADC", &CPU::ADC, &CPU::ZP0, 3 },{ "ROR", &CPU::ROR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLA", &CPU::PLA, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::IMM, 2 },{ "ROR", &CPU::ROR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::IND, 5 },{ "ADC", &CPU::ADC, &CPU::ABS, 4 },{ "ROR", &CPU::ROR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVS", &CPU::BVS, &CPU::REL, 2 },{ "ADC", &CPU::ADC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ZPX, 4 },{ "ROR", &CPU::ROR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEI", &CPU::SEI, &CPU::IMP, 2 },{ "ADC", &CPU::ADC, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ABX, 4 },{ "ROR", &CPU::ROR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZP0, 3 },{ "STA", &CPU::STA, &CPU::ZP0, 3 },{ "STX", &CPU::STX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "DEY", &CPU::DEY, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "TXA", &CPU::TXA, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "STY", &CPU::STY, &CPU::ABS, 4 },{ "STA", &CPU::STA, &CPU::ABS, 4 },{ "STX", &CPU::STX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCC", &CPU::BCC, &CPU::REL, 2 },{ "STA", &CPU::STA, &CPU::IZY, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZPX, 4 },{ "STA", &CPU::STA, &CPU::ZPX, 4 },{ "STX", &CPU::STX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "TYA", &CPU::TYA, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::ABY, 5 },{ "TXS", &CPU::TXS, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::NOP, &CPU::IMP, 5 },{ "STA", &CPU::STA, &CPU::ABX, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::IMM, 2 },{ "LDA", &CPU::LDA, &CPU::IZX, 6 },{ "LDX", &CPU::LDX, &CPU::IMM, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "LDY", &CPU::LDY, &CPU::ZP0, 3 },{ "LDA", &CPU::LDA, &CPU::ZP0, 3 },{ "LDX", &CPU::LDX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "TAY", &CPU::TAY, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::IMM, 2 },{ "TAX", &CPU::TAX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "LDY", &CPU::LDY, &CPU::ABS, 4 },{ "LDA", &CPU::LDA, &CPU::ABS, 4 },{ "LDX", &CPU::LDX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCS", &CPU::BCS, &CPU::REL, 2 },{ "LDA", &CPU::LDA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "LDY", &CPU::LDY, &CPU::ZPX, 4 },{ "LDA", &CPU::LDA, &CPU::ZPX, 4 },{ "LDX", &CPU::LDX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "CLV", &CPU::CLV, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::ABY, 4 },{ "TSX", &CPU::TSX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "LDY", &CPU::LDY, &CPU::ABX, 4 },{ "LDA", &CPU::LDA, &CPU::ABX, 4 },{ "LDX", &CPU::LDX, &CPU::ABY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "CPY", &CPU::CPY, &CPU::IMM, 2 },{ "CMP", &CPU::CMP, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPY", &CPU::CPY, &CPU::ZP0, 3 },{ "CMP", &CPU::CMP, &CPU::ZP0, 3 },{ "DEC", &CPU::DEC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INY", &CPU::INY, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::IMM, 2 },{ "DEX", &CPU::DEX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "CPY", &CPU::CPY, &CPU::ABS, 4 },{ "CMP", &CPU::CMP, &CPU::ABS, 4 },{ "DEC", &CPU::DEC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BNE", &CPU::BNE, &CPU::REL, 2 },{ "CMP", &CPU::CMP, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ZPX, 4 },{ "DEC", &CPU::DEC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLD", &CPU::CLD, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ABX, 4 },{ "DEC", &CPU::DEC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "CPX", &CPU::CPX, &CPU::IMM, 2 },{ "SBC", &CPU::SBC, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPX", &CPU::CPX, &CPU::ZP0, 3 },{ "SBC", &CPU::SBC, &CPU::ZP0, 3 },{ "INC", &CPU::INC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INX", &CPU::INX, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::IMM, 2 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::SBC, &CPU::IMP, 2 },{ "CPX", &CPU::CPX, &CPU::ABS, 4 },{ "SBC", &CPU::SBC, &CPU::ABS, 4 },{ "INC", &CPU::INC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BEQ", &CPU::BEQ, &CPU::REL, 2 },{ "SBC", &CPU::SBC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ZPX, 4 },{ "INC", &CPU::INC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SED", &CPU::SED, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ABX, 4 },{ "INC", &CPU::INC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
	};

    
    ram=_ram;

}

uint8_t CPU::read(uint16_t Address)
{
    return ram->read(Address);
}

void CPU::write(short int Address, uint8_t Data)
{
    ram->write(Address, Data);
}


void CPU::SetFlag(STATUS S, int value)
{
    if(value==0)
    {
        status=status&(~S); //bit mask to set off
    }
    else
    {
        status=status|S;  //bit mask to set on 
    }
}

void CPU::reset()
{

    for(int i=0; i<64*1024;i++)
    {
        if(i!=0xFFFC && i!=0xFFFD)  //dont reset part of memory that stores where the program starts
        {
            ram->write(i,0); //clears memory
        }
    }
    PC= ram->read(0xFFFC)|ram->read(0xFFFD)<<8; //program starts at address in 0xFFFC (See C64 startup routine)
    stackptr=(uint8_t)0x0100;    //stack pointer starts at 0x0100;

    SetFlag(C,0);   //reset all flags
    SetFlag(Z,0);
    SetFlag(I,0);
    SetFlag(D,0);
    SetFlag(B,0);
    SetFlag(U,0);
    SetFlag(V,0);
    SetFlag(N,0);
    A=X=Y=0; //clears registers
}



uint8_t CPU::fetch()
{
    fetched=(uint8_t)ram->read(PC);
    cycles=lookup[fetched].cycles;
    PC++;
    cycles--;
}

uint8_t CPU::getOperand()  
{
    /*for immidiate addressing, operand is already available in that address in the form of a literal
    sometimes, that is not the case, and the cpu must take several steps to locate the operand*/

    (this->*lookup[fetched].addressing_mode)();  //find the operand based on fetched instruction
    //store in helper variable for use in operation


}


void CPU::execute()
{
    fetch();
    current_opcode=lookup[fetched].opcode_name;
    getOperand();
    (this->*lookup[(uint8_t)fetched].opcode)();  //exectures opcode based on vector table
    cycles--;
    //maybe reset oprerand variable here?
}


void CPU::dumpData()
{
    printf("X reg: %X, Y reg: %X, A reg= %X \n PC=%X, STKPTR=%X",X,Y,A,PC,stackptr);
    printf("\n");
    for(int i=0;i<64*1024;i++)
    {
        printf("Address: %X, Data: %X\n", i,read(i));

    }
}

void CPU::dumpRegisters()
{
    printf("X: %X, Y: %X, A: %X\n PC:%X\n",X, Y, A,PC);
}


//**ADDRESSING MODES BELOW**/

uint8_t CPU::IMM()  //Next byte is the operand
{
    //operand=ram->read(PC);
    absolute_address=PC;
    PC++;
    cycles--;
}

uint8_t CPU::IMP()  //do nothing. address is implied in the function call
{
    return 0;
}

uint8_t CPU::REL()  //operand is the address the PC will jump to. Double check this. 
{
	//the read number could be negative. might cause a bug. 
     //Next address is PC offset.
    //rel addressing is only used in branch operation.
	uint16_t temp=ram->read(PC); //read the distance
	absolute_address=PC+temp*((-1)*(temp&0x80)==0x80);   //branch absolute address. also needs to check if address is backwards (negative)
	PC++;
	cycles--;
	return 0;
}

uint8_t CPU::ABS()  //specifies memory location explicilty over next 2 bytes
{

    absolute_address=ram->read(PC);
    PC++;
    cycles--;
    absolute_address|=ram->read(PC)<<8;  //to bit shift in hex, each position is 4 single binary shifts
    PC++;
    cycles--;
}


uint8_t CPU::ABY()
{

	//just adds Y or X to the absolute address read.
	//address is 16 bits, not 8, hence the 2 step process. 
    absolute_address=ram->read(PC);
    PC++;
    cycles--;
    absolute_address|=ram->read(PC)<<8;  //to bit shift in hex, each position is 4 single binary shifts
    absolute_address+=Y;
    PC++;
    cycles--;

    //operand=ram->read(absolute_address+Y);
}

uint8_t CPU::ABX()
{
    absolute_address=ram->read(PC);
    PC++;
    cycles--;
    absolute_address|=ram->read(PC)<<8;  //to bit shift in hex, each position is 4 single binary shifts
    absolute_address+=X;
    PC++;
    cycles--;

 //   operand=ram->read(absolute_address+X);
}





uint8_t CPU::ZP0()  //same as absolute addressing but only for first 256 bytes
                    //Hence there is no need for uppper and lower half, address is only 0xHH
{   
    absolute_address=ram->read(PC);
    PC++;
    cycles--;
    absolute_address&=0x00FF;	//address must be in the first page or else it will wrap around
}

uint8_t CPU::ZPX()
{
    absolute_address=(ram->read(PC)+X)&0x00FF; //read address, add X, remove carry (similar to mod function)
    PC++;
    cycles--;
}

uint8_t CPU::ZPY()  //adds Y register to absolute address in zero page. Result will always wrap around
{
    absolute_address=(ram->read(PC)+Y)&0x00FF; //read address, add Y, remove carry (similar to mod function)
    PC++;
    cycles--;
}


uint8_t CPU::IND() //like absolute, but the address stores a pointer, not a literal
{//only used in jump operations
    absolute_address=ram->read(PC);
    PC++;
    cycles--;

    absolute_address|=ram->read(PC)<<8;
    PC++;
    cycles--;

    absolute_address=ram->read(absolute_address)|ram->read(absolute_address+1);
    //read the address to get the actual address of the operand
}

uint8_t CPU::IZY() //"an 8 bit address identifies a pointer. get that pointer and add y to its value.
{
    absolute_address=ram->read(PC);
    PC++;
    cycles--;

	absolute_address=ram->read(absolute_address)|ram->read(absolute_address+1)<<8;

	absolute_address+=Y;

}

uint8_t CPU::IZX()  //gets address pointed to by memory and adds X to it. 
{
    //IZX gets pointer from PC+X
    absolute_address=ram->read(PC);
    PC++;
    cycles--;

    absolute_address=ram->read(absolute_address+X)|ram->read(absolute_address+X+1)<<8;
}


uint8_t CPU::GetFlag(STATUS S)
{
    return((status&S)>0);
}
