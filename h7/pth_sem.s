#void Sem_post(long* sem);
#void Sem_wait(long* sem);


        .section .text
        .global Sem_wait
        .global Sem_post
Sem_wait:

#rdi == sem
#rsi == the lock

		push %rbp
        mov  %rsp, %rbp
		
		mov $0, %rsi 	#put a 0 into this reg

		xchg %rdi, %rsi #try to swap

		cmp $1, %rsi  #check if the lock is 1
		jne Sem_wait #if not equal to 1 go to wait

		jmp done #go to done

Sem_post:
		
		push %rbp
        mov  %rsp, %rbp
        
		mov $1, %rsi #set the reg up with 1

		xchg %rdi, %rsi #swap the two regs to unlock

done:
		leave

		ret