#ifndef ADDRESSES_H
#define ADDRESSES_H

#define RAM_END		      0x00030000
#define STACK_SIZE_COMB   0x00001000
#define SYSTEM_STACK_SIZE 0x00000B00
#define INTERRUPT_STACK_SIZE  0x00000100
#define SYSTEM_SP         (RAM_END)
#define FIQ_SP	          (SYSTEM_SP - SYSTEM_STACK_SIZE)
#define IRQ_SP            (FIQ_SP - INTERRUPT_STACK_SIZE)
#define SUPER_SP          (IRQ_SP - INTERRUPT_STACK_SIZE)
#define ABORT_SP	      (SUPER_SP - INTERRUPT_STACK_SIZE)
#define UNDEF_SP	      (ABORT_SP - INTERRUPT_STACK_SIZE)


#endif
