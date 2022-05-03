#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using Byte = unsigned char; //8 bits
using Word = unsigned short; // 16 bits | Address size 

using u32=unsigned int;

struct Mem
{
    static constexpr u32 MAX_MEM=1024*64; //64kb memory max
    Byte Data[MAX_MEM]; //create ram of type Byte that is 64kB long and 8 bits wide 


    void init()
    {
        for(u32 i=0;i<MAX_MEM;i++)
        {
            Data[i]=0;  //clears memory
        }
    }
    Byte operator[](u32 Address) const  //defines [] operator 
    {
        return Data[Address]; //just an index to Data array
    }

    Byte read(u32 Address)
    {
        return Data[Address];
    }

    void write(u32 Address,Byte _Data)
    {
        Data[Address]=_Data; //writes 1 byte of data to memory 
    }

};



struct CPU
{






    u32 cycles=0; //number of cycles to excecute instrcution.





    struct Instruction  //every possible instruction has a function (branch, load, etc) has a name, addressing mode, and number of cycles. 
    {
        std::string name;
        

		uint8_t(CPU::*addrmode)(void)=nullptr;
		uint8_t cycles=0;
    };






    Word PC; // Program counter is 16 bits (1 word | 1 address width)
    Word SP; //Stack pointer

    Byte A; //The accumulator (stores result of ALU)
    Byte X,Y; //other registers

    Byte C:1; //Carry biy
    Byte Z:1; //Zero bit
    Byte I:1; //Disable Interrupts
    Byte D:1; //Decimal Mode
    Byte B:1; //Break
    Byte U:1; //Unused
    Byte V:1; //Overflow
    Byte N:1; //Negative



    void Reset(Mem& memory)
    {
        PC= 0xFFFC;
        SP=0x0100;
        C=Z=I=D=B=U=V=N=0;  //clears status
        A=X=Y=0; //clears registers

        memory.init();
    }

    Byte Fetch(u32& Cycles, Mem& memory) //fetches one byte at a time
    {
        Byte Data = memory[PC]; 
        PC++;
        Cycles--;
        return Data;
    }

    void dump_registers()   //prints all the registers of the cpu
    {
        std::cout<<A<<"\n"<<X<<"\n"<<Y<<"\n";
    }



    //opcodes
    static constexpr Byte INS_LDA_IM=0xA9;
    static constexpr Byte INS_LDA_ZP=0xA5;

    void Execute(u32 Cycles,Mem& memory)    // executes that cycle
    {
        while(Cycles>0)
        {

            Byte instruction = Fetch(Cycles, memory);
            switch (instruction)
            {
                case INS_LDA_IM:
                {                    
                    Byte Value=Fetch(Cycles,memory);
                    A=Value;
                    Z=(A==0);
                    N=(A&0b10000000)>0;
                    break;
                }
                case INS_LDA_ZP:
                {
                    Byte ZeroPageAddress=Fetch(Cycles,memory);   
                }
                

            default:
                std::cout<<"instruction not handled\n";
                break;
            
            }
        }
    }

};


int main()
{
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    mem.write(0xFFFC,0xA9);
    mem.write(0xFFFD,0x42);
    std::cout<<(int)mem.read(0xFFFC);
    cpu.Execute(2,mem);




}
