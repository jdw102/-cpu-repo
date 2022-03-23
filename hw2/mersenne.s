.text
main:
    li $v0, 4
    la $a0, prompt      #print prompt
    syscall

    li $v0, 5
    syscall             #read input and assign to t0
    move $t0, $v0

    li $t1, 0           #set t1 (iteration counter) to 0
    li $t2, 1           #set t2 (return value) to 1
    li $t3, 2           #set t3 to 2

    loop:
    beq $t1, $t0, equal_to_n       #break if the iteration counter surpasses input
    mult $t2, $t3                  #multiply return value by 2
    mflo $t2                       #set result equal to return value
    addi $t1, $t1, 1
    j loop

    equal_to_n:

    addi $t2, $t2, -1       #subtract 1 to calculate mersenne value

    li $v0, 1
    move $a0, $t2           #print mersenne value
    syscall
    jr $ra

.data
prompt: .asciiz "Please enter data:"