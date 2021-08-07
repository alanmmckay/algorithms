# --- fib(n)
# ---     if n == 0
# ---         return 0
# ---     if n == 1
# ---         return 1
# ---     else
# ---         first = fib(n - 1)
# ---         return first + fib(n-2)

# Within the scope of fib(n), use the following registers:
# $s0 stores the current argument, n. (not n-1 and not n-2)
# $s1 stores the result of the first recursive call; fib(n-1)
# $ra stores the caller's return address

.data
result: .word 0
argument: .word 7

.text
.globl main

main:
lw $a0, argument
jal fib
sw $v0, result

#print statement
lw $a0, result
li $v0, 1
syscall

#halt
li $v0, 10
syscall

fib:

#allocate memory for call frame
addi $sp, $sp, -12
#save registers caller may have been using:
sw $s1, 12($sp)
sw $s0, 8($sp)
#save $ra if another procedure is to be called
sw $ra, 4($sp)
move $s0, $a0 #place the current argument into s0
addi $a0, $s0, -1 #prime the next argument to be sent

if:
bne $s0, 0, else_if
li $v0, 0
j end_if
else_if:
bne $s0, 1, else
li $v0, 1
j end_if
else:

jal fib #first call to fib; fib(n-1)
move $s1, $v0 #stores the result of the first execution of fib
addi $a0, $s0, -2 #prime the next argument to be sent
jal fib #second call to fib; fib(n-2)
add $v0, $s1, $v0 #reslt of fib(n-1) + result of fib(n-2)

end_if:
#restore registers caller may have been using:
lw $ra, 4($sp)
lw $s0, 8($sp)
lw $s1, 12($sp)
#move stack pointer to initial position:
addi $sp, $sp, 12
jr $ra