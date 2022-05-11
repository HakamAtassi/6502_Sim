# 6502 Simulator


## Specifications

### Capabilties 

### Instruction set
The 6502 is capable of 56 different instructions, with most involving at least one deticated addressing mode. In total, there are 151 possible combinations (opcodes) of instrucitons and addressing modes. 

The following table lists all possible combinations of  addressing modes and instructions:
![image](https://user-images.githubusercontent.com/83780720/167928531-5e34e9ef-eef6-4553-a680-f741fa19dacf.png)

[source]

#### Instructions

The set of all possible instructions is too lengthly and repetetive to explain in detail. Foretunetly, the name of each instruction gives away a good deal about what it does.
Some of the major instructions are:
- ADC
  - add with carry
- AND
  - and memory location with Accumulator
- BCC/BCS
  - branch on carry clear/set
- BEQ/BNE
  - branch on equal/not-equal (zero bit is set/cleared)
- BVS/BVC
  - branch on overflow/not-overflow (overflow bit is set/cleared)
- CLC/CLD/CLI/CLV
  - clear carry/decimal/interrupt/overflow bit
- SEC/SED/SEI
  - set carry/decimal/interrupt bit
- LDA/LDX/LDY
  - load accumulator, X register, Y register
- ROL/ROR
  - rotate left/right | carry enters bit 7, bit 0 enters carry and vice versa. 
- LSR
  - shifts in a 0 on the left
- ASL 
  - shifts in a 0 on the right
- DEC/DEX/DEY
  - decrement accumulator, X register, Y register
- INC/INX/INY
  - increment accumulator, X register, Y register

#### Addressing modes
An adressing mode defines how the microprocessor will locate the operand for that particular instruction. The 6502 has 13 addressing modes

- Implied
  - The instruction has no real addressing mode. The operand is implied in the instruction or is not needed. Ex: NOP (no operation) or DEC (deceremnt accumulator).

- Immediate 
  - The next byte of data is the operand. Ex: 0xA9 0x05 will load 0x05 into the accumulator. 

- Relative
  - The next byte indicates the location of the operand relative to the current position of the program counter (PC). Only used in branch operations. The offset is signed and is therefore limited to numbers between -127 and 128.

- Absolute 
  - The next two bytes indicate the exact location of the operand in memory. Slightly slow since an address is 2 bytes and ram is 1 byte wide. This requires an extra memory read which calls for an additional clock. 
  
- Absolute, X/Y
  - Works exactly like absolute addressing, except the contents of the X/Y register(s) are added to the absolute address that follows the instruction.
 
 
- Zero page
  - Think of this as high speed memory. Since addresses are 2 bytes long and memory is 1 byte wide, it would typically take 2 clocks to fetch a complete address from memory. This is not the case if that address starts with 0x00 (or is in the first page). If the address is assumed to be in page one, its absolute address can be fetched in 1 clock. EX: 0xA5 0xF0 will load the value at location 0xF0 (1 byte long absolute address) into the accumulator. 
- Zero page, X/Y
  - Works just like zero page, except the value of the X/Y register is added to the zero page address. if the address exceeds the first page, the address will loop around (mod function)

- Indicrect
  - Used only for for the jump instruction. The 2 bytes following the instruction indicate the address to a pointer (address to an address). The PC is set to pointer (or address's address)

- Indirect, X 
  - Reads a 1 byte long (zero page) adds X to that address. The PC is set to the 2 byte long pointer stored in that address.

- Indirect, Y 
  - Reads a 1 byte long (zero page). The PC is set to the pointer stored at that address + Y.



### To Build and Run



<img align="right" src="https://user-images.githubusercontent.com/83780720/165873944-c7f24080-adb7-450c-8e1c-7b6cb7d84c1c.png">

#### Registers
The 6502 Microprocessor has 6 major registers: the Accumulator, Index registers (X & Y), Stack pointer, Program counter, and Status register. 
- Accumulator
  - Stores results of ALU on chip
- Index registers (X & Y)
  - Used in Indexed and Zero Page Addressing. Particularly useful for instructions that are 2 and 3 Bytes long. 
- Stack pointer
  - Stores pointer to stack that stores current machine state information
- Program counter
  - Stores address to next instruction to be excecuted
- Status register
  - Stores processor 




#### Status Register
The Status Register is 8 bits long, with each bit (except for unused bit 5) indicating a certain flag. The register is configured as follows:



<img align="right" src="https://user-images.githubusercontent.com/83780720/165876735-cdc260b7-1aaf-4d1f-99c0-4384522bef58.png">

- C
  - Carry bit
- Z 
  - Zero bit
- I
  - Interrupts
- D
  - Decimal Mode
- B 
  - Break
- U
  - Unused
- O
  - Overflow
- N
  - Negative




#### The Stack

The stack stores information relavant to the current state of the CPU when JSR is called. The stack for the 6502 exists between the addresses 0x100 and 0x1FF. The stackptr always points to the next availabole position and is decrementing (starts at 0x1FF and moves downward). 


