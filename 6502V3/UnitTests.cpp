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

    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    a.execute();    //execute 2 opcodes
    std::cout<<"Expected: X: 5, Y: 0 , A: 5"<<"\nActual: ";
    a.dumpRegisters();


}

void LDY_POS_NO_OVERFLOW() 
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF);   //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0xA0);
    a.write(0xFFF1,0x05); 
    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    std::cout<<"Expected: X: 0, Y: 5 , A: 0"<<"\nActual: ";
    a.dumpRegisters();
}

void LDA_Yind_ABS() 
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF);   //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0xA0);   //loads 5 into X reg
    a.write(0xFFF1,0x05); 

    a.write(0xFFF2,0xB9);   //LDA X abs
    a.write(0xFFF3,0xF5);
    a.write(0xFFF4,0xFF);
    a.write(0xFFFA,0x05);


    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    a.execute();    //execute 2 opcodes
    std::cout<<"Expected: X: 0, Y: 5 , A: 5"<<"\nActual: ";
    a.dumpRegisters();
}
void ADD_IMP_To_Empty() 
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF); //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0x69);   //add 5 to accum
    a.write(0xFFF1,0x05); 


    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    std::cout<<"Expected: X: 0, Y: 0, A: 5"<<"\nActual: ";
    a.dumpRegisters();
}


void ADD_IMP_TWICE() 
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF); //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0x69);   //add 5 to accum
    a.write(0xFFF1,0x05); 
    //a.dumpData();
    a.write(0xFFF2,0x69);   //add 5 to accum
    a.write(0xFFF3,0x05); 

    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    a.execute();    
    std::cout<<"Expected: X: 0, Y: 0, A: A"<<"\nActual: ";
    a.dumpRegisters();
}


void ADC_TWICE_WITH_JMP() 
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF); //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0x69);   //add 5 to accum
    a.write(0xFFF1,0x05); 
    //a.dumpData();
    a.write(0xFFF2,0x4C);   //jump to 0xFFF0
    a.write(0xFFF3,0xF0);
    a.write(0xFFF4,0xFF); 

    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();    //add 5 the first time
    a.execute();    //jump back to add 5
    a.execute();    //do the initial add 5 operation
    std::cout<<"Expected: X: 0, Y: 0, A: A"<<"\nActual: ";
    a.dumpRegisters();
}

void BNE_TEST() 
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF); //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0x69);   //add 5 to accum
    a.write(0xFFF1,0x05); 
    //a.dumpData();
    a.write(0xFFF2,0xE9);   //Subtract 5 from accum
    a.write(0xFFF3,0x05);


    a.write(0xFFF4,0xD0);   //BNE
    a.write(0xFFF5,0x05);


    a.write(0xFFFA,0xA9);   //load F into A if branched 
    a.write(0xFFFB,0x0F);

    a.write(0xFFF6,0xA9);   //if not branched, do this instead,
    a.write(0xFFF7,0x01);

    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    a.execute();
    a.execute();
    a.execute();

    std::cout<<"Expected: X: 0, Y: 0, A: 1"<<"\nActual: ";
    a.dumpRegisters();
}

void BEQ_TEST() 
{
    Memory ram;
    CPU a(&ram);
    a.write(0xFFFC,0xF0);
    a.write(0xFFFD,0xFF); //Program starts at 0xFFF0
    a.reset();
    //a.dumpData();
    a.write(0xFFF0,0x69);   //add 5 to accum
    a.write(0xFFF1,0x05); 
    //a.dumpData();
    a.write(0xFFF2,0xE9);   //Subtract 5 from accum
    a.write(0xFFF3,0x05);


    a.write(0xFFF4,0xF0);   //BNE
    a.write(0xFFF5,0x05);

    a.write(0xFFFA,0xA9);   //load F into A
    a.write(0xFFFB,0x0F);


    //a.dumpData();
    //printf("%X\n",a.read(0xFFFD));
    a.execute();
    a.execute();
    a.execute();
    a.execute();

    std::cout<<"Expected: X: 0, Y: 0, A: F"<<"\nActual: ";
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
    std::cout<<"====\n";
    LDY_POS_NO_OVERFLOW();
    std::cout<<"====\n";
    LDA_Yind_ABS();
    std::cout<<"====\n";
    ADD_IMP_To_Empty();
    std::cout<<"====\n";
    ADD_IMP_TWICE();
    std::cout<<"====\n";
    ADC_TWICE_WITH_JMP();
    std::cout<<"====\n";
    BNE_TEST(); 
    std::cout<<"====\n";
    BEQ_TEST(); 
}
