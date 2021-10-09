# Gameboy-Disassembler-Generator

First I downloaded the html from https://izik1.github.io/gbops/ which is supposedly the most accurate info. Then I parsed it with Python to extract each opcode's relevant information: the text string representing the instruction, and its size in bytes. Then I printed some C++ switch cases which will go into the main .cpp file. For instructions that have immediate values, I used sprintf to put those immediate values into the string at runtime. 
