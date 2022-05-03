#ifndef MEMORY_H_
#define MEMORY_H_


class Memory
{

    char mem[64*2^10]; //64kB memory

    char read(short int Address);
    void write(short int Address, char Data);


};


#endif