1. 反汇编所有段
arm-none-eabi-objdump -D  firmware_nuttx > elf_to.txt


2. 利用elfread工具进行阅读

./build_px4fmu-v5_default/src/firmware/nuttx/firmware_nuttx:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0011af68  08008000  08008000  00008000  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .init_section 000001c0  08122f68  08122f68  00122f68  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 __param       00002c44  08123128  08123128  00123128  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .ARM.exidx    00000008  08125d6c  08125d6c  00125d6c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .data         00001608  20020000  08125d74  00130000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  5 .bss          00005aac  20021700  0812737c  00131700  2**8
                  ALLOC
  6 .comment      0000006e  00000000  00000000  00131608  2**0
                  CONTENTS, READONLY
  7 .ARM.attributes 00000035  00000000  00000000  00131676  2**0
                  CONTENTS, READONLY
  8 .debug_abbrev 000a1977  00000000  00000000  001316ab  2**0
                  CONTENTS, READONLY, DEBUGGING
  9 .debug_info   006bddac  00000000  00000000  001d3022  2**0
                  CONTENTS, READONLY, DEBUGGING
 10 .debug_line   00157b20  00000000  00000000  00890dce  2**0
                  CONTENTS, READONLY, DEBUGGING
 11 .debug_aranges 00015118  00000000  00000000  009e88f0  2**3
                  CONTENTS, READONLY, DEBUGGING
 12 .debug_str    00150026  00000000  00000000  009fda08  2**0
                  CONTENTS, READONLY, DEBUGGING
 13 .debug_loc    0014b86f  00000000  00000000  00b4da2e  2**0
                  CONTENTS, READONLY, DEBUGGING
 14 .debug_ranges 00038138  00000000  00000000  00c9929d  2**0
                  CONTENTS, READONLY, DEBUGGING
 15 .debug_frame  0003af18  00000000  00000000  00cd13d8  2**2

