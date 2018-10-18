
/* Processor Exceptions */

	.word	IDLE_STACK			/* Vector  0: Reset stack pointer */
	.word	__start				/* Vector  1: Reset vector */
	.word	stm32_nmi			/* Vector  2: Non-Maskable Interrupt (NMI) */
	.word	stm32_hardfault		/* Vector  3: Hard fault */
	.word	stm32_mpu			/* Vector  4: Memory management (MPU) */
	.word	stm32_busfault		/* Vector  5: Bus fault */
	.word	stm32_usagefault	/* Vector  6: Usage fault */
	.word	stm32_reserved		/* Vector  7: Reserved */
	.word	stm32_reserved		/* Vector  8: Reserved */
	.word	stm32_reserved		/* Vector  9: Reserved */
	.word	stm32_reserved		/* Vector 10: Reserved */
	.word	stm32_svcall		/* Vector 11: SVC call */
	.word	stm32_dbgmonitor	/* Vector 12: Debug monitor */
	.word	stm32_reserved		/* Vector 13: Reserved */
	.word	stm32_pendsv		/* Vector 14: Pendable system service request */
	.word	stm32_systick		/* Vector 15: System tick */

	
	
#elif defined(CONFIG_STM32_STM32F40XX)
#  include "chip/stm32f40xxx_vectors.h"
#else
#  error "No vectors for STM32 chip"
#endif
	
中断地址 ：复位向量


unsigned _vectors[] __attribute__((section(".vectors"))) =
  {
    /* Initial stack */

    IDLE_STACK,

    /* Reset exception handler */

    (unsigned)&__start,

    /* Vectors 2 - n point directly at the generic handler */

    [2 ... (15 + ARMV7M_PERIPHERAL_INTERRUPTS)] = (unsigned)&exception_common
  };

  
  
arm/up_head.S:231:__start:
arm/up_head.S:484:	.size	__start, .-__start


备调用:
#ifdef CONFIG_DEBUG
        .macro  showprogress, code
        mov     r0, #\code
        bl      up_lowputc
        .endm
#else
        .macro  showprogress, code
        .endm
#endif


stm32/stm32_start.c:86:void __start(void) __attribute__ ((no_instrument_function));
stm32/stm32_start.c:191:void __start(void)



armv7-m/nvic.h:177:#define NVIC_VECTAB_OFFSET              0x0d08 /* Vector table offset register */
armv7-m/nvic.h:350:#define NVIC_VECTAB                     (ARMV7M_NVIC_BASE + NVIC_VECTAB_OFFSET)


ifeq ($(CONFIG_ARCH_CORTEXA5),y)        # Cortex-A5 is ARMv7-A
ARCH_SUBDIR = armv7-a
else ifeq ($(CONFIG_ARCH_CORTEXA8),y)   # Cortex-A8 is ARMv7-A
ARCH_SUBDIR = armv7-a
else ifeq ($(CONFIG_ARCH_CORTEXA9),y)   # Cortex-A9 is ARMv7-A
ARCH_SUBDIR = armv7-a
else ifeq ($(CONFIG_ARCH_CORTEXR4),y)   # Cortex-R4 is ARMv7-R
ARCH_SUBDIR = armv7-r
else ifeq ($(CONFIG_ARCH_CORTEXR4F),y)  # Cortex-R4F is ARMv7-R
ARCH_SUBDIR = armv7-r
else ifeq ($(CONFIG_ARCH_CORTEXR5),y)   # Cortex-R5 is ARMv7-R
ARCH_SUBDIR = armv7-r
else ifeq ($(CONFIG_ARCH_CORTEXR5F),y)  # Cortex-R5F is ARMv7-R
ARCH_SUBDIR = armv7-r
else ifeq ($(CONFIG_ARCH_CORTEXR7),y)   # Cortex-R7 is ARMv7-R
ARCH_SUBDIR = armv7-r
else ifeq ($(CONFIG_ARCH_CORTEXR7F),y)  # Cortex-R7F is ARMv7-R
ARCH_SUBDIR = armv7-r
else ifeq ($(CONFIG_ARCH_CORTEXM3),y)   # Cortex-M3 is ARMv7-M
ARCH_SUBDIR = armv7-m
else ifeq ($(CONFIG_ARCH_CORTEXM4),y)   # Cortex-M4 is ARMv7E-M
ARCH_SUBDIR = armv7-m
else ifeq ($(CONFIG_ARCH_CORTEXM7),y)   # Cortex-M4 is ARMv7E-M????注释有问题.
ARCH_SUBDIR = armv7-m
else ifeq ($(CONFIG_ARCH_CORTEXM0),y)   # Cortex-M0 is ARMv6-M
ARCH_SUBDIR = armv6-m

//从中看出：只有M0是armv6-m



#if defined(__ICCARM__)
  putreg32((uint32_t)__vector_table, NVIC_VECTAB);
#else
  putreg32((uint32_t)_vectors, NVIC_VECTAB);
#endif

arch/arm/src/stm32/stm32_irq.c:119:          getreg32(NVIC_INTCTRL), getreg32(NVIC_VECTAB));
arch/arm/src/stm32/stm32_irq.c:330:  putreg32((uint32_t)__vector_table, NVIC_VECTAB);
arch/arm/src/stm32/stm32_irq.c:332:  putreg32((uint32_t)_vectors, NVIC_VECTAB);


stm32_rcc.h:88:extern uint32_t _vectors[];  /* See stm32_vectors.S */

//有时候要搜搜grep -rn "up_irqinitialize()


NuttX/nuttx/sched/init/os_start.c:690:  up_initialize();
   -> common/up_initialize.c:161:  up_irqinitialize();
      -> arch/arm/src/stm32/stm32_irq.c:332:  putreg32((uint32_t)_vectors, NVIC_VECTAB);
	  
//备变异到



这里看到是绝对定位:
.text           0x08004000    0xd5ff4
                0x08004000                _stext = ABSOLUTE (.)
 *(.vectors)
 .vectors       0x08004000      0x19c /home/yangang/work/px4/theone-mc/build_theone/px4fmu-v2/NuttX/nuttx-export/libs/libnuttx.a(arch-up_vectors.o)
                0x08004000                _vectors
                0x080041a0                . = ALIGN (0x20)
 *fill*         0x0800419c        0x4
                0x080041a0                _bootdelay_signature = ABSOLUTE (.)
 FILL mask 0xffecc2925d7d05c5
                0x080041a8                . = (. + 0x8)
				

	//48Kbin文件
-rwxrwxr-x 1 yangang yangang 48K  5月 15 22:52 ./src/modules/px4iofirmware/px4io-v2.bin

.text           0x08001000     0xbd04
                0x08001000                _stext = ABSOLUTE (.)
 *(.vectors)
 .vectors       0x08001000      0x134 /home/yangang/work/px4/theone-mc/build_theone/px4io-v2/NuttX/nuttx-export/libs/libnuttx.a(arch-up_vectors.o)
                0x08001000                _vectors
