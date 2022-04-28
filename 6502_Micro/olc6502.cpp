#include "headers/olc6502.h"
#include <cstdint>
#include "headers/Bus.h"


olc6502::olc6502()
{

}

olc6502::~olc6502()
{
}


uint8_t olc6502::read(uint16_t a)
{
	return bus->read(a,false); //reads from the provided address the data on the bus
}


void olc6502::write(uint16_t address,uint8_t d)
{
	bus->write(address,d);
}
