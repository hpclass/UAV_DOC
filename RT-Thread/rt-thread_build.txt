   
 1. 安装gcc-arm-none-eabi
    $sudo apt-get install gcc-arm-none-eabi 
    $ls
    $arm-none-eabi-gcc
    $arm-none-eabi-gcc -v
 
2. 进入stm32f10x目录下,进行编译
   $cd stm32f10x
   $ls
   $sudo scons


3 编译过程
scons: Reading SConscript files ...
scons: done reading SConscript files.
scons: Building targets ...
scons: building associated VariantDir targets: build
AS build/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_hd.o
CC build/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.o
CC build/Libraries/STM32F10x_StdPeriph_Driver/src/misc.o
CC build/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.o
CC build/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.o
CC build/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.o
CC build/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.o
CC build/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.o
CC build/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.o
CC build/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f

LINK rtthread-stm32.axf
arm-none-eabi-objcopy -O binary rtthread-stm32.axf rtthread.bin
arm-none-eabi-size rtthread-stm32.axf
   text	   data	    bss	    dec	    hex	filename
  89688	    932	   5704	  96324	  17844	rtthread-stm32.axf
scons: done building targets.

