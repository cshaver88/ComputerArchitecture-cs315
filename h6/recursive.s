# Author:       Cayla Shaver 
# Function:     Recursive
# Purpose:  Print values of the function R(i,j) defined by
#           the formulas
#         
#              R(i,j) = i - j, if i or j is < 0
#              R(i,j) = R(i-1, j) + R(i, j-1), otherwise
#
#           Values of R computed using x86 assembler
# C Prototype:  long Recursive(long i, long j);
# Args:         i = rdi
#               j = rsi
# Return val:   Recursive(i, j) = rax
# 

        .section .text
        .global Recursive

Recursive:
        push %rbp
        mov  %rsp, %rbp
        sub  $24, %rsp          # We need to store i, j and a return 
                                #    val from a recursive call

        # If i < 0   i = rdi and j = rsi return = rax
        cmp $0, %rdi
        jl subtract_i_j

        # Else if j < 0
        cmp $0, %rsi
        jl subtract_i_j
        

        # Else do recursive
        mov %rdi, 0(%rsp) # save the i
	mov %rsi, 8(%rsp) #save the j
        sub $1, %rdi #calculate the i - 1
        call Recursive
        mov %rax, 16(%rsp)

	mov 0(%rsp), %rdi
	mov 8(%rsp), %rsi
        sub $1, %rsi #calculate the j - 1
        call Recursive 

        add 16(%rsp), %rax      
                                           
        jmp  done                  

subtract_i_j:
        # r = i - j
        # put i - j into return?
        #save i into rdx
        mov %rdi, %rax
        # do subtract
        sub  %rsi, %rax        

done:
        leave                   
                                
        ret
