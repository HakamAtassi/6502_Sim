#include "headers/Bus.h"
#include <cstdint>


Bus::~Bus()
{
}


Bus::Bus()
{
	for(auto &i :ram) 
	{
		i=0x0; //clear ram
	}
	cpu.ConnectBus(this); //connects cpu to bus
}



void Bus::write(uint16_t addr, uint8_t data)
{
	if(addr >= 0x0000 && addr <= 0xFFFF) //checks min and max addresses of ram
	{
		ram[addr]=data;
	}	

}


uint8_t Bus::read(uint16_t addr,bool bReadOnly)
{
	if (addr >= 0x0 && addr <= 0xFFFF)
	{
		return ram[addr];
	}
	return 0x0; //if addr is out of range, return 0. 
}


