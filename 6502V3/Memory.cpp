#include "Memory.h"


uint8_t Memory::read(uint16_t Address)
{
    return mem[Address];
}

void Memory::write(uint16_t Address, unsigned char Data)
{

    mem[Address]=Data;
}

void Memory::print_size()
{
    std::cout<<size;
}