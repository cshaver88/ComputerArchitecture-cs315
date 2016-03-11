	.test
	.globl main

main:
    subu $sp, $sp, 8 #create space on stack
    sw $ra, 0($sp)  #save the return addy

    li $t2, 1 #put the 1 into a temp
    sw $t2, 4($sp)  #put a 1 into sem which is below ret addy on stack

    add $t3, $sp, 4 #addy of the sem
    move $a0, $t3 #put t3 into arg0 
    jal wait

    li $v0, 1 #print code
    lw $v0, 4($sp) # print this thing
    syscall

    move $a0, $t3 #put t3 into arg0 
    jal post

    li $v0, 1 #print code
    lw $v0, 4($sp) # print this thing
    syscall

wait:
    subu $sp, $sp, 8 #create space on stack
    sw $ra, 0($sp)  #save the return addy
    #1 = unlock
    #0 = lock

    li $t1, 0 #place holder
    ll  $t1, 0($a0) #load the lock 
    sc $t0, 0($a0) #store the lock
    beq $t0, 0, wait # if t0 is 0 go to wait

    lw  $ra, 0($sp) #get the return addy 
    addu $sp, $sp, 8    #put the stack space back
    jr $ra  #return 

post:
    subu $sp, $sp, 8 #create stack space
    sw $ra, 0($sp)  #save the return addy

    li $t1, 1   #store the 0 in t0
    ll $t1, 0($a0) #load the lock
    sc $t0, 0($a0)    #store the lock

    lw  $ra, 0($sp) #get the return stuff
    addu $sp, $sp, 8    #return the stack space
    jr $ra  #return 