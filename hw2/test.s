.data 
done: .asciiz "DONE"
victim: .space 30
v_prompt: .asciiz "Please enter victim:"
newline: .asciiz "\n"

.text
main:
    li $v0, 4
    la $a0, v_prompt   #ask for victim name
    syscall

    li $v0, 8
    la $a0, victim      #assign victim name to victim
    li $a1, 30
    syscall

    li $v0, 4
    la $a0, victim       #test print victim
    syscall

    li $v0, 4
    la $a0, newline      #test print victim
    syscall

    la $a0, victim
    la $a1, done
    jal strcmp
    move $t0, $v0

    li $v0, 1
    move $a0, $t0
    syscall


strcmp:
	lb $t0, 0($a0)
	lb $t1, 0($a1)

	bne $t0, $t1, done_with_strcmp_loop
	addi $a0, $a0, 1
	addi $a1, $a1, 1
	bnez $t0, strcmp
	li $v0, 0
	jr $ra
		

	done_with_strcmp_loop:
	sub $v0, $t0, $t1
	jr $ra
    

placenode:
    addi $sp, $sp -4
    sw $ra, 0($sp)

    la $s0, 0($a0)          #load head node into s0 and new node into s1
    la $s1, 0($a1)          #set s2 equal to head node to keep track of previous
    la $s2, 0($a0)

    beqz $t7, add_reg

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)

    jal strcmp              #compare head node to new node

    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    bgtz $v0, add_reg       #if the head node is greater than the new node then jump to add_reg

    place_loop: 
    beqz $s0, exit_placenode

    la $a0, 0($s0)
    la $a1, 0($s1)          #compare current node to new node
    jal strcmp

    bltz $v0, found_place      #if current node is less than the new node then jump to found_place

    bne $s1, $s2, update_previous       #if after first iteration jump to update_previous

    update_head:
    lw $s1, 92($s1)     #update head node then loop
    j check_loop 

    found_place:
    sw $s1, 92($s2)         #let the previous node point to the new node

    sw $s0, 92($s1)         #let the new node point to the current node
    
    lw $ra, 0($sp)
    addi $sp, $sp 4         #restore sp and return
    jr $ra

    update_previous:
    lw $s2, 92($s2)         #update the previous node and jump to update_head
    j update_head

    add_reg:
    sw $t7, 92($s1)        #link node and set tracking register to the last created node
    move $t7, $s1

    lw $ra, 0($sp)
    addi $sp, $sp 4         #restore sp and return
    jr $ra

    exit_placenode:
    la $s3, 0($s1)
    sw $s3, 92($s2)         #let the previous node point to the new node

    lw $ra, 0($sp)
    addi $sp, $sp 4
    jr $ra