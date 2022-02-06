.text
main:
    li $v0, 4
    la $a0, name_prompt
    syscall
    
    li $v0, 8
    la $a0, name
    li $a1, 16
    syscall

    li $v0, 4
    la $a0, age_prompt
    syscall

    li $v0, 5
    syscall
    move $t5, $v0

    la $t1, name
    la $t3, 10

    string_loop:
    lb $t2, 0($t1)
    beq $t2, $t3, equal_to_newline
    addi $t1, $t1, 1
    j string_loop

    equal_to_newline:
    sb $zero, 0($t1)

    li $v0, 4
    la $a0, name
    syscall

    li $v0, 4
    la $a0, answer
    syscall

    li $t0, 50
    sub $t0, $t0, $t5
    addi $t0, $t0, 2021

    li $v0, 1
    move $a0, $t0
    syscall

    jr $ra





.data
name_prompt: .asciiz "Enter name: "
age_prompt: .asciiz "Enter age: "
answer: .asciiz " will turn 50 years old in "
name: .space 16