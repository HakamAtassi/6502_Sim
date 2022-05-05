
#include "CPU.h"
#include "CPU.cpp"

#include "Memory.h"
#include "Memory.cpp"
#include <iostream>


int main()
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF);   //Program starts at 0xFFF0
    a.reset();
    a.dumpRegisters();
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
