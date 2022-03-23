.data
done: .asciiz "DONE\n"
target: .space 30
infector: .space 30
victim: .space 30
i_prompt: .asciiz "Please enter infector:"
v_prompt: .asciiz "Please enter victim:"
check: .asciiz ""
newline: .asciiz "\n"
space: .asciiz " "
test: .asciiz "test"
placeholder: .space 30


.text
main:
    addi $sp, $sp, -4
    sw $ra, 0($sp)
  
    move $t7, $zero     #t7 will hold last node added, and will initially be 0

    loop:
    addi $sp, $sp -4
    sw $t0, 0($sp)
    la $a0, victim
    jal strclr
    lw $t0, 0($sp)
    addi $sp, $sp 4

    addi $sp, $sp -4
    sw $t0, 0($sp)
    la $a0, infector
    jal strclr
    lw $t0, 0($sp)
    addi $sp, $sp 4

    addi $sp, $sp -4
    sw $t0, 0($sp)
    la $a0, target
    jal strclr
    lw $t0, 0($sp)
    addi $sp, $sp 4

    li $v0, 4
    la $a0, v_prompt   #ask for victim name
    syscall
        
    li $v0, 8
    la $a0, victim      #assign victim name to victim
    li $a1, 30
    syscall

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, victim
    la $a1, done            #check if the entered name is DONE
    jal strcmp
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8
        
    beq $zero, $v0, exit_main       #if so exit the loop

    li $v0, 4
    la $a0, i_prompt     #ask for infector name
    syscall
    
    li $v0, 8
    la $a0, infector      #assign infector name to infector
    li $a1, 30
    syscall


    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, target
    la $a1, infector       #assign infector to target to remove newline for grabnode check
    jal strcpy
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    la $a0, victim
    jal createnode         #create victim node
    la $t0, 0($v0)

    la $a0, 0($t7)
    la $a1, 0($t0)
    jal placenode

    la $a0, target
    la $a1, 0($t7)             #check if current node with infector name already exists
    jal grabnode

    move $t5, $v0

    beqz $t5, infector_dne  #if it does not exist jump to infector_dne

    la $t1, 0($v1)          #load grabbed node address into t1 and jump to add_victim
    j add_victim

    infector_dne:
    la $a0, infector
    jal createnode         #create infector node
    la $t1, 0($v0)

    la $a0, 0($t7)
    la $a1, 0($t1)
    jal placenode

    add_victim:

    la $a0, 0($t1)
    la $a1, victim          #add victim name to infector node
    jal addvictim


    j loop

    exit_main:
    la $a0, 0($t7)          #load last linked node and print the list
    jal printnodes

    lw $ra, 0($sp)
    addi $ra, $ra 4
    jr $ra


createnode:
    addi $sp, $sp -12
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)

    la $s0, 0($a0)           #move node name into s0
    
    li $v0, 9
    li $a0, 96              #allocate 96 bytes of memory and set s1 = to address
    syscall
    la $s1, 0($v0)

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 0($s1)
    la $a1, 0($s0)           #copy node name into the appropriate memory location
    jal strcpy
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 30($s1)
    la $a1, check           #initialize first victim to empty string
    jal strcpy
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 60($s1)
    la $a1, check           #intialize second victim to empty string
    jal strcpy
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    sw $zero, 92($s1)        #set pointer to point to zero

    la $v0, 0($s1)           #move node address into v0

    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    addi $sp, $sp 12

    jr $ra

grabnode:
    addi $sp, $sp -16
    sw $s0, 0($sp)
    sw $s1, 4($sp)
    sw $s2, 8($sp)
    sw $ra, 12($sp)

    la $s0, 0($a0)      #load target name into s0
    la $s1, 0($a1)  #load current node adddress into s1

    check_loop:
    beqz $s1, exit_loop     #if current node = 0 exit loop

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 0($s0)
    la $a1, 0($s1)     #compare strings
    jal strcmp
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    beqz $v0, node_found  #if strcmp produces zero jump to conditonal exit

    lw $s1, 92($s1)
    j check_loop                 #set s1 equal to next node

    exit_loop:
    li $v0, 0      #if node not found, return 0

    lw $s0, 0($sp)
    lw $s1, 4($sp)      #return
    lw $s2, 8($sp)
    lw $ra, 12($sp)
    addi $sp, $sp 16
    jr $ra


    node_found:
    li $v0, 1
    la $v1, 0($s1)      #if node found, return address to node in v1 and 1 in v0

    lw $s0, 0($sp)
    lw $s1, 4($sp)
    lw $s2, 8($sp)
    lw $ra, 12($sp)
    addi $sp, $sp 16
    jr $ra


addvictim:
    addi $sp, $sp -16
    sw $s0, 0($sp)
    sw $s1, 4($sp)
    sw $s2, 8($sp)
    sw $ra, 12($sp)

    la $s0, 0($a0)      #load node address into s0 and victim name address into s1      
    la $s1, 0($a1)
    
    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 30($s0)
    la $a1, check       #check if first victim is empty
    jal strcmp
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    beqz $v0, addfirst      #if so jump to add first

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 30($s0)
    la $a1, 0($s1)         #strcmp the first victim with the new victim
    jal strcmp
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    bgtz $v0, switch        #if the first victim is greater alphabetically than the second victim jump to switch

    addsecond:
    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 60($s0)
    la $a1, 0($s1)           #copy victim name into second victim memory location of node
    jal strcpy
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8
    
    j return_add

    addfirst:
    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 30($s0)
    la $a1, 0($s1)           #copy victim name into first victim memory location of node
    jal strcpy
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    j return_add

    switch:
    la $a0, placeholder     #clear placeholder 
    jal strclr

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, placeholder
    la $a1, 30($s0)           #copy first victim name into placeholder
    jal strcpy
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    addi $sp, $sp -4
    sw $t0, 0($sp)
    la $a0, 30($s0)            #clear first victim from node
    jal strclr
    lw $t0, 0($sp)
    addi $sp, $sp 4

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 30($s0)
    la $a1, 0($s1)           #copy victim name into first victim memory location of node
    jal strcpy
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 60($s0)
    la $a1, placeholder           #copy victim name into second victim memory location of node
    jal strcpy
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    return_add:
    lw $s0, 0($sp)
    lw $s1, 4($sp)
    lw $s2, 8($sp)
    lw $ra, 12($sp)
    addi $sp, $sp 16
    jr $ra

strcpy:
	lb $t0, 0($a1)
    lb $t1, newline
	beq $t0, $zero, done_copying
    beq $t0, $t1, done_copying
	sb $t0, 0($a0)
	addi $a0, $a0, 1
	addi $a1, $a1, 1
	j strcpy

	done_copying:
	jr $ra

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

strclr:
	lb $t0, 0($a0)
	beq $t0, $zero, done_clearing
	sb $zero, 0($a0)
	addi $a0, $a0, 1
	j strclr

	done_clearing:
	jr $ra

printnodes:
    addi $sp, $sp -16
    sw $s1, 0($sp)
    sw $s4, 4($sp)
    sw $s5, 8($sp)
    sw $ra, 12($sp)

    la $s1, 0($a0)      #load node into s1

    print_loop:

    li $v0, 4
    la $a0, 0($s1)          #print node name
    syscall

    li $v0, 4
    la $a0, space        #print space
    syscall

    li $v0, 4
    la $a0, 30($s1)          #print first victim name
    syscall

    li $v0, 4
    la $a0, space        #print space
    syscall

    li $v0, 4
    la $a0, 60($s1)          #print second victim name
    syscall

    li $v0, 4
    la $a0, newline        #print newline
    syscall

    la $s4, 92($s1)      #load name into s4 to see if it equals 0
    lw $s5, 0($s4)
    beq $s5, $zero, exit_print      #if s4 = 0 then break out of loop

    lw $s1, 92($s1)        #move to next node
    j print_loop            #jumpt to start of loop
    
    exit_print:
    lw $s1, 0($sp)
    lw $s4, 4($sp)
    lw $s5, 8($sp)
    lw $ra, 12($sp)
    addi $sp, $sp 16

    jr $ra


placenode:
    addi $sp, $sp -16
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    sw $s2, 12($sp)

    la $s0, 0($a0)          #load head node into s0 and new node into s1
    la $s1, 0($a1)          #set s2 equal to head node to keep track of previous
    la $s2, 0($a0)

    beqz $t7, add_reg

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 0($s0)
    la $a1, 0($s1)
    jal strcmp              #compare head node to new node
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    bgtz $v0, add_reg       #if the head node is greater than the new node then jump to add_reg

    place_loop: 
    beqz $s0, exit_placenode

    addi $sp, $sp -8
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    la $a0, 0($s0)
    la $a1, 0($s1)          #compare current node to new node
    jal strcmp
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    addi $sp, $sp 8

    bgtz $v0, found_place      #if current node is less than the new node then jump to found_place

    bne $s0, $s2, update_previous       #if after first iteration jump to update_previous

    update_head:
    lw $s0, 92($s0)     #update head node then loop
    j place_loop

    found_place:
    sw $s1, 92($s2)         #let the previous node point to the new node

    sw $s0, 92($s1)         #let the new node point to the current node
    
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
    addi $sp, $sp 16
    jr $ra

    update_previous:
    lw $s2, 92($s2)         #update the previous node and jump to update_head
    j update_head

    add_reg:
    sw $t7, 92($s1)        #link node and set tracking register to the last created node
    move $t7, $s1

    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
    addi $sp, $sp 16
    jr $ra

    exit_placenode:
    sw $s1, 92($s2)         #let the previous node point to the new node

    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
    addi $sp, $sp 16
    jr $ra
    
