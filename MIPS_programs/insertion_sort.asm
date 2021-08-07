.data
values: .word 100, 30, 45, 2, 15, 3
length: .word 6
output1: .asciiz "\n The array prior to insertion sort: "
output2: .asciiz "\n The array after the insertion sort: "
output3: .asciiz " "
.text
.globl main

#register usage:
# $t0 : Base address of values
# $t1 : Length - 1
# $t2 : i
# $t3 : j
# $t4 : address of A[j]
# $t5 : value of A[j]
# $t6 : address of A[j-1]
# $t7 : value of A[j-1]
# $t8 : j - 1

main:
li $v0, 4
la $a0, output1
syscall
jal print_array
jal insertion_sort
li $v0, 4
la $a0, output2
syscall
jal print_array
li $v0, 10
syscall


insertion_sort:
la $t0, values
lw $t1, length
addi $t1, $t1, -1
li $t2, 1
outer_loop:
bgt $t2, $t1, end_outer_loop
move $t3, $t2

inner_loop:
blt $t3, $zero, end_inner_loop
beq $t3, $zero, end_inner_loop

mul $t4, $t3, 4 # j * 4
add $t4, $t4, $t0 # baseAddress + (j*4)
lw $t5, 0($t4) # value of A[j]

addi $t8, $t3, -1 # j - 1
mul $t6, $t8, 4 # (j-1) * 4
add $t6, $t6, $t0 # baseAddress + ((j-1) * 4)
lw $t7, 0($t6) #value of A[j-1]

bgt $t5, $t7, end_inner_loop
beq $t5, $t7, end_inner_loop

sw $t7, 0($t4)
sw $t5, 0($t6)

addi $t3, $t3, -1
j inner_loop

end_inner_loop:
addi $t2, $t2, 1

j outer_loop
end_outer_loop:
jr $ra

print_array:
la $t0, values
lw $t1, length
addi $t1, $t1, -1
move $t2, $zero
print_loop:
bgt $t2, $t1, end_print
mul $t3, $t2, 4
add $t3, $t3, $t0
lw $a0, 0($t3)
li $v0, 1
syscall
la $a0, output3
li $v0, 4
syscall
addi $t2, $t2, 1
j print_loop
end_print:
jr $ra