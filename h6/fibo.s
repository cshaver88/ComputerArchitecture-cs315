# Author:       Cayla Shaver
# Function:     Fibo
# Purpose:      Return the nth Fibonacci number, where
#
#                     Fibo(0) = 0
#                     Fibo(1) = 1
#                     Fibo(n) = Fibo(n-1) + Fibo(n-2), n >= 2
#
# C Prototype:  long Fibo (long n)
# Args:         n = rdi
# Return val:   Fibo(n) = rax
# 

        .section .text
        .global Fibo

Fibo:
        push %rbp
        mov  %rsp, %rbp   #I don't think we need to move this if we are supposed to use callee saved 
        sub  $16, %rsp          # We may need to store n and a return 
                                #    val from a recursive call

        # Is n = 0?
        
        #also the first return from fibo
    
        cmp  $0, %rdi           # Is n = rdi == 0?  Note that the immediate
                                #    must come first here
        jne  n_gt_0             # Look at the flags register to see whether
                                #    the previous comparison result is != 0
        mov  $0, %rax           # Return 0
        jmp  done               # Go to done

n_gt_0:
        # Is n = 1?
        cmp  $1, %rdi           # Is n = rdi == 1?

        jne  n_gt_1             # Look at the flags register to see whether
                               #    the previous comparison result is != 1
        mov  $1, %rax           # Return 1
        jmp  done               # Go to done
        
n_gt_1:
    	mov  %rbx, 8(%rsp)      # store the callers n for the callee to use
        mov  %r12, (%rsp)      # also the first return from fibo

        # n >= 2
	mov %rdi, %rbx
        sub  $1, %rdi           # n = n-1
        call Fibo
        mov  %rax, %r12         # Save Fibo(n-1) on the stack
	mov %rbx, %rdi
        sub  $2, %rdi           # n = n-2
        call Fibo
        add  %r12, %rax         # return Fibo(n-1) + Fibo(n-2)
        mov 8(%rsp), %rbx       #get the rbx
        mov  0(%rsp), %r12      #get the r12 

done:
        
        leave                   # Assigns rbp to rsp:  no need to
                                #    add 16 to rsp
        ret
