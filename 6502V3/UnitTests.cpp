#include "CPU.h"
#include "CPU.cpp"

#include "Memory.h"
#include "Memory.cpp"
#include <iostream>


void LDA_ABS()
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF);   //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0xAD);
    a.write(0xFFF1,0x45);
    a.write(0xFFF2,0x42);
    a.write(0x4245, 0x09);
    //a.dumpData();
    //printf("%X\n",a.read(0x4245));
    a.execute();

    std::cout<<"Expected: X: 0, Y: 0 , A: 9"<<"\nActual: ";
    a.dumpRegisters();
}

void LDA_IMM()
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF);   //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0xA9);
    a.write(0xFFF1,0x75);   
    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();

    std::cout<<"Expected: X: 0, Y: 0 , A: 75"<<"\nActual: ";
    a.dumpRegisters();
}




void LDA_ZP0_NO_MOD()
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF);   //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0xA5);
    a.write(0xFFF1,0x75); 
    a.write(0x75,0xa0); 
    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    std::cout<<"Expected: X: 0, Y: 0 , A: A0"<<"\nActual: ";
    a.dumpRegisters();
}


void LDX_POS_NO_OVERFLOW() 
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF);   //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0xA2);
    a.write(0xFFF1,0x05); 
    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    std::cout<<"Expected: X: 5, Y: 0 , A: 0"<<"\nActual: ";
    a.dumpRegisters();
}

void LDA_Xind_ABS() 
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF);   //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0xA2);   //loads 5 into X reg
    a.write(0xFFF1,0x05); 

    a.write(0xFFF2,0xBD);   //LDA X abs
    a.write(0xFFF3,0xF5);
    a.write(0xFFF4,0xFF);
    a.write(0xFFFA,0x05);


    a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    a.execute();    //execute 2 opcodes
    std::cout<<"Expected: X: 5, Y: 0 , A: 5"<<"\nActual: ";
    a.dumpRegisters();


}




int main()
{
    LDA_ABS();
    std::cout<<"====\n";
    LDA_IMM();
    std::cout<<"====\n";
    LDA_ZP0_NO_MOD();
    std::cout<<"====\n";
    LDX_POS_NO_OVERFLOW();
    std::cout<<"====\n";
    LDA_Xind_ABS();


}