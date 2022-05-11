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
- 

#### Addressing modes


56 opp codes
64kB memory

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


#### Memory Addressing modes
TODO


#### The Stack
TODO
