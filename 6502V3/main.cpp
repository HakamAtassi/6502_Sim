
#include "CPU.h"
#include "CPU.cpp"

#include "Memory.h"
#include "Memory.cpp"
#include <iostream>


int main()
{
    Memory ram;
    CPU a(&ram);
    a.reset();
    //a.dumpData();
    a.write(0xFFFD,0xF9);
    a.write(0xFFFE,0x42);
    //a.dumpData();
    //a.write(0xFFFD, 0x15);
    printf("%X\n",a.read(0xFFFD));

}
