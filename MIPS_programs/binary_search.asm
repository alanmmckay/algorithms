# Algorithm:
#    BinarySearch(A, size, target)
#	low = 0
#	high = size
#	while ( (low + 1) < high)
#	    test = (low + high) // 2
#	    if (A[test] > target)
#		high = test
#	    else
#		low = test
#	if (A[low] == target)
#	    return low
#	else
#	    return -1	

.data
values: .word 0, 1, 2, 4, 8, 10, 11, 15, 20
length: .word 9
target: .word 10
output1: .asciiz "Input value to search: "
output2: .asciiz "Value "
output2b: .asciiz " located at index: "

# Binary search register usage:
# $t0 : base address of array
# $t1 : length of array
# $t2 : low
# $t3 : low + 1
# $t4 : high
# $t5 : test
# $t6 : value of array[x]; access of array
# $t7 : target

.text
.globl main

main:

la $a0, output1
li $v0, 4
syscall

la $a0, values
lw $a1, length

li $v0, 5
syscall

move $s0, $v0
move $a2, $v0
jal binary_search

move $t1, $v0

li $v0, 4
la $a0, output2
syscall

li $v0, 1
move $a0, $s0
syscall

li $v0, 4
la $a0, output2b
syscall  

li $v0, 1
move $a0, $t1
syscall

li $v0, 10
syscall


binary_search:

move $t0, $a0 #address of array
move $t1, $a1 #length of array
move $t7, $a2 #value to find

move $t2, $zero #low = 0
move $t4, $t1 #high = size

loop:
addi $t3, $t2, 1 #low + 1
#conditional: if (low + 1) < high then execute body
bgt $t3, $t4, end_loop 
beq $t3, $t4, end_loop

add $t5, $t2, $t4 #test = low + high
div $t5, $t5, 2 #test = test // 2

mul $t6, $t5, 4 # test * 4
add $t6, $t6, $t0 # baseAddress + (test*4)
lw $t6, 0($t6) # A[test]

#conditional: if A[test] > target
bgt $t6, $t7, high #then...
move $t2, $t5 # else low = test
j loop
high:
move $t4, $t5 #... high = test
j loop

end_loop:
mul $t6, $t2, 4 # low * 4
add $t6, $t6, $t0 # baseAddress + (low * 4)
lw $t6, 0($t6) #A[low]

#conditional: if A[low] == target
beq $t6, $t7, return_target #then...
li $v0, -1 #else: return -1
jr $ra
return_target: # ... return target
move $v0, $t2
jr $ra