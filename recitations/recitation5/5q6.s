.text
main:
    addi $sp, $sp -4
    sw $ra, 0($sp)

    li $t0, 1
    li $t1, 5

    li $s0, 5
    li $s1, 6

    move $a0, $t0
    move $a1, $t1

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)

    jal foo

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    move $t5, $v0

    li $v0, 1
    move $a0, $t5
    syscall

    lw $ra, 0($sp)
    addi $sp, $sp 4

    jr $ra
foo:
    addi $sp, $sp, -12
    sw $s0, 0($sp)
    sw $s1, 4($sp)
    sw $ra, 8($sp)

    add $t2, $a0, $a1
    li $t3, 10

    move $v0, $t2

    bge $t2, $t3, return

    addi $a0, $a0, 1
    addi $a1, $a1, 1

    addi $sp, $sp -4
    sw $t2, 0($sp)

    jal foo

    lw $t2, 0($sp)
    addi $sp, $sp 4

    add $v0, $v0, $t2

return:
    lw $s0, 0($sp)
    lw $s1, 4($sp)
    lw $ra, 8($sp)
    addi $sp, $sp, 12

    jr $ra
