;-------------------------------------------------------------------------------
; Initialize Stack Pointers

    .global  _coreBackupStackPointer_
    .global  _coreRestoreStackPointer_
    .asmfunc

_coreBackupStackPointer_:

        ldr   r0,       r1_bkup        
        str   r1,       [r0]
        ldr   r0,       r2_bkup        
        str   r2,       [r0]

        msr   cpsr_c,   #0xD1
        ldr   r0,       fiq_bkup        
        str   sp,       [r0]
        msr   cpsr_c,   #0xD2
        ldr   r0,       irq_bkup
        str   sp,       [r0]
        msr   cpsr_c,   #0xD7
        ldr   r0,       abort_bkup
        str   sp,       [r0]
        msr   cpsr_c,   #0xDB
        ldr   r0,       undef_bkup
        str   sp,       [r0]
        msr   cpsr_c,   #0xDF
        ldr   r0,       user_bkup
        str   sp,       [r0]
        msr   cpsr_c,   #0xD3
        ldr   r0,       svc_bkup
        str   sp,       [r0]
        bx    lr

;    .endasmfunc

;-------------------------------------------------------------------------------
; Recover Stack Pointers

;    .global  _coreRestoreStackPointer_
;    .asmfunc

_coreRestoreStackPointer_:

        ldr   r0,       r1_bkup        
        ldr   r1,       [r0]
        ldr   r0,       r2_bkup        
        ldr   r2,       [r0]

        msr   cpsr_c,   #0xD1
        ldr   r0,       fiq_bkup        
        ldr   sp,       [r0]
        msr   cpsr_c,   #0xD2
        ldr   r0,       irq_bkup
        ldr   sp,       [r0]
        msr   cpsr_c,   #0xD7
        ldr   r0,       abort_bkup
        ldr   sp,       [r0]
        msr   cpsr_c,   #0xDB
        ldr   r0,       undef_bkup
        ldr   sp,       [r0]
        msr   cpsr_c,   #0xDF
        ldr   r0,       user_bkup
        ldr   sp,       [r0]
        msr   cpsr_c,   #0xD3
        ldr   r0,       svc_bkup
        ldr   sp,       [r0]
;
        bx    lr

user_bkup:   .word 0x08001000
svc_bkup:    .word 0x08001004
fiq_bkup:    .word 0x08001008
irq_bkup:    .word 0x0800100C
abort_bkup:  .word 0x08001010
undef_bkup:  .word 0x08001014
r0_bkup:   	 .word 0x08001018
r1_bkup:     .word 0x0800101C
r2_bkup:     .word 0x08001020


    .endasmfunc  
    