#ifndef MEMORY_H_
#define MEMORY_H_

#include <array>

class Memory
{

//    char mem[64*1024]; //64kB memory
    std::array<char,64*1024> mem;

    public:
    int size=sizeof(mem)/sizeof(char);
    uint8_t read(uint16_t Address);
    void write(uint16_t Address,uint8_t Data);
    void print_size();

};


#endif