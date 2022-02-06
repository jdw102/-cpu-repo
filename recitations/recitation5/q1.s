.text
main:
    addi $sp, $sp -4
    sw $ra, 0($sp)

    li $t0, 1
    li $t1, 2
    
    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1 4($sp)

    move $a0, $t0
    move $a1, $t1

    jal foo
    move $t3, $v0

    lw $t0, 0($sp)
    lw $t1, 4($sp)

    add $t3, $t3, $t0
    add $t3, $t3, $t1

    li $v0, 1
    move $a0, $t3
    syscall

    addi $sp, $sp 8

    lw $ra, 0($sp)
    addi $sp, $sp 4

    jr $ra
foo:
    add $v0, $a0, $a1
    jr $ra
