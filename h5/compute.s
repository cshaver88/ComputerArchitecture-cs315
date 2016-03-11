# Function       compute
# Purpose:       Subtract two long ints and use the result to add another to it
# C prototype:   long Compute(long a, long b, long c)
#
# Notes:
# 1. gcc expects a function called "Compute"
# 2. This code assumes the x86-64 System V AMD64 calling conventions:
#    - The first six args are passed in registers RDI, RSI, RDX, RCX, 
#      R8, and R9, respectively.
#    - Additional arguments are passed on the stack.
#    - The return address is on the top of the stack.
#    - Registers RBX, RBP (the frame or base pointer), and R12-R15
#      should be saved by the called function (callee)
#    - The return value is stored in RAX.  A second return value can
#      be returned in RDX

        .section        .text

        .global  Compute

Compute:
        push    %rbp            # At the start of the function it's 
                                #    customary to push the base pointer
                                #    onto the stack.
        mov     %rsp, %rbp      # Now the base and the top of the stack 
                                #    frame are the same.     
        sub     %rsi, %rdi      # rsi 2st arg -= rdi 1nd arg
        add     %rdx, %rdi      # rsi result of subtraction += rdx 3rd arg
        mov     %rdi, %rax      # rax = rsi
        leave                   # Set stack pointer to base pointer 
                                #    and pop old base pointer
        ret                     # Pop return address and jump to it