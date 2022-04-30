#pragma once
#include <cstdint>
#include "olc6502.h"
#include <array>

class Bus
{
	public:
		Bus();
		~Bus();
	public: //devices on bus using SPI 
		olc6502 cpu; //6502 is the cpu

		std::array<std::uint8_t,64*1024> ram; //64kB temporary ram


	public: //reading and writing from the bus 
		void write(uint16_t addr, uint8_t data);
		uint8_t read(uint16_t addr, bool bReadOnly=false);


};
