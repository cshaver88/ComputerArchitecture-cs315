# Author:       Cayla Shaver 
# Function:     Bubble 
# Purpose:      Sort an array of longs using bubble sort
# C Prototype:  void Bubble(long a[], long n)
#
# Args:         rdi = a
#               rsi = n 
#
        .section .text
        .global Bubble

Bubble:  
        push %rbp
        mov  %rsp, %rbp
        
        # store the i .
        # store the length
        mov  %rsi, %rdx  #this is storing the list length in the 3rd reg

bub:        #compare list length >= 2
        mov $0, %rcx #this is storing the i in 4th reg 
        cmp $2, %rdx
        sub $1, %rdx #subtract 1 from list length
        jge loop_1

        jmp done


loop_1:
        cmp %rcx, %rdx 	# rcx = i < rdx = list_lenth
        jg loop_2
	jmp bub
	

loop_2:
        mov %rcx, %r8 #save original i 
        add $1, %rcx #add 1 to i
        mov 0(%rdi, %r8, 8), %r9  # a[i]
        mov 0(%rdi, %rcx, 8), %r10     # a[i+1]
        cmp %r9, %r10  #a[i] > a[i + 1]
        jl Swap # jump to swap
	jmp loop_1

done:
        leave
        ret

Swap:
        mov %r9, 0(%rdi, %rcx, 8) # put r9(a[i]) value into temp 
        mov %r10, 0(%rdi, %r8, 8) # put r10 (a[i + 1]) value into r9
        jmp loop_1 