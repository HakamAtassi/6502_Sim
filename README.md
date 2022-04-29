# 6502-NES-Emulator
## Microprocessor Architecture 

54 opp codes
64kB memory




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
  - E/N Interrupts
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

#### Op codes
TODO

#### The Stack
TODO
