.text
main:
    addi $sp, $sp -4
    sw $ra, 0($sp)

    li $v0, 4
    la $a0, prompt      #print prompt
    syscall

    li $v0, 5
    syscall             #read input and assign to t0
    move $t0, $v0

    addi $sp, $sp -4
    sw $t6, 0($sp)
    move $a0, $t0
    jal recurse
    move $t1, $v0
    lw $t6, 0($sp)
    addi $sp, $sp 4

    li $v0, 1
    move $a0, $t1          #print mersenne value
    syscall

    lw $ra, 0($sp)
    addi $sp, $sp 4

    jr $ra

recurse:
    addi $sp, $sp -20
    sw $ra, 0($sp)
    sw $s2, 4($sp)
    sw $s3, 8($sp)
    sw $s4, 12($sp)
    sw $s5, 16($sp)
 
    
    move $t6, $a0

    beqz $a0, base_case    #if n is 0 jump to basecase

    addi $sp, $sp -4
    sw $t6, 0($sp)

    addi $a0, $a0 -1     #increment by -1
    jal recurse

    lw $t6, 0($sp)
    addi $sp, $sp 4

    li $s3, 3       
    li $s4, -2          #create -2
    mult $s3, $t6       #multiply n by 3 and assign to s0
    mflo $s0
    add $s0, $s0, $s4   #create constant to be added

    li $s2, 2
    mult $v0, $s2

    mflo $s5

    add $v0, $s5, $s0

    lw $ra, 0($sp)
    lw $s2, 4($sp)
    lw $s3, 8($sp)
    lw $s4, 12($sp)
    lw $s5, 16($sp)
    addi $sp, $sp 20
    jr $ra

base_case:
    lw $ra, 0($sp)
    lw $s2, 4($sp)
    lw $s3, 8($sp)
    lw $s4, 12($sp)
    lw $s5, 16($sp)
    addi $sp, $sp 20
    li $v0, -2
    jr $ra



.data
prompt: .asciiz "Please enter data:"


