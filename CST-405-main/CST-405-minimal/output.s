.data

.text

.globl getNumber
getNumber:
  addi $sp, $sp, -8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  move $fp, $sp
  li $t0, 42
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  jr $ra
  move $sp, $fp
  lw $fp, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  jr $ra

.globl main
main:
  addi $sp, $sp, -8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -52
  # decl x at 0
  # decl y at 4
  # decl z at 8
  # decl r at 12
  # array arr[3] base 16
  # array2D mat[2][3] base 28
  li $t1, 10
  sw $t1, 0($sp)
  li $t2, 20
  sw $t2, 4($sp)
  lw $t3, 0($sp)
  lw $t4, 4($sp)
  add $t3, $t3, $t3
  sw $t3, 8($sp)
  lw $t5, 8($sp)
  move $a0, $t5
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t6, 8($sp)
  li $t7, 5
  add $t6, $t6, $t6
  sw $t6, 0($sp)
  lw $t0, 0($sp)
  move $a0, $t0
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t1, 0($sp)
  lw $t2, 4($sp)
  add $t1, $t1, $t1
  lw $t3, 8($sp)
  add $t1, $t1, $t1
  sw $t1, 4($sp)
  lw $t4, 4($sp)
  move $a0, $t4
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t5, 0($sp)
  li $t6, 2
  sub $t5, $t5, $t5
  sw $t5, 12($sp)
  lw $t7, 12($sp)
  move $a0, $t7
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t0, 0
  li $t1, 5
  addi $t2, $sp, 16
  sll $t0, $t0, 2
  add $t2, $t2, $t2
  sw $t1, 0($t1)
  li $t3, 1
  li $t4, 10
  addi $t5, $sp, 16
  sll $t3, $t3, 2
  add $t5, $t5, $t5
  sw $t4, 0($t4)
  li $t6, 2
  li $t7, 0
  addi $t0, $sp, 16
  sll $t7, $t7, 2
  add $t0, $t0, $t0
  lw $t0, 0($t0)
  li $t1, 1
  addi $t2, $sp, 16
  sll $t1, $t1, 2
  add $t2, $t2, $t2
  lw $t2, 0($t2)
  add $t0, $t0, $t0
  addi $t3, $sp, 16
  sll $t6, $t6, 2
  add $t3, $t3, $t3
  sw $t0, 0($t0)
  li $t4, 2
  addi $t5, $sp, 16
  sll $t4, $t4, 2
  add $t5, $t5, $t5
  lw $t5, 0($t5)
  move $a0, $t5
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t6, 0
  li $t7, 0
  li $t0, 1
  li $t1, 3
  mul $t6, $t6, $t6
  add $t6, $t6, $t6
  addi $t2, $sp, 28
  sll $t6, $t6, 2
  add $t2, $t2, $t2
  sw $t0, 0($t0)
  li $t3, 0
  li $t4, 1
  li $t5, 2
  li $t6, 3
  mul $t3, $t3, $t3
  add $t3, $t3, $t3
  addi $t7, $sp, 28
  sll $t3, $t3, 2
  add $t7, $t7, $t7
  sw $t5, 0($t5)
  li $t0, 0
  li $t1, 2
  li $t2, 3
  li $t3, 3
  mul $t0, $t0, $t0
  add $t0, $t0, $t0
  addi $t4, $sp, 28
  sll $t0, $t0, 2
  add $t4, $t4, $t4
  sw $t2, 0($t2)
  li $t5, 1
  li $t6, 0
  li $t7, 4
  li $t0, 3
  mul $t5, $t5, $t5
  add $t5, $t5, $t5
  addi $t1, $sp, 28
  sll $t5, $t5, 2
  add $t1, $t1, $t1
  sw $t7, 0($t7)
  li $t2, 1
  li $t3, 1
  li $t4, 5
  li $t5, 3
  mul $t2, $t2, $t2
  add $t2, $t2, $t2
  addi $t6, $sp, 28
  sll $t2, $t2, 2
  add $t6, $t6, $t6
  sw $t4, 0($t4)
  li $t7, 1
  li $t0, 2
  li $t1, 6
  li $t2, 3
  mul $t7, $t7, $t7
  add $t7, $t7, $t7
  addi $t3, $sp, 28
  sll $t7, $t7, 2
  add $t3, $t3, $t3
  sw $t1, 0($t1)
  li $t4, 0
  li $t5, 1
  li $t6, 3
  mul $t4, $t4, $t4
  add $t4, $t4, $t4
  addi $t7, $sp, 28
  sll $t4, $t4, 2
  add $t7, $t7, $t7
  lw $t7, 0($t7)
  li $t0, 1
  li $t1, 2
  li $t2, 3
  mul $t0, $t0, $t0
  add $t0, $t0, $t0
  addi $t3, $sp, 28
  sll $t0, $t0, 2
  add $t3, $t3, $t3
  lw $t3, 0($t3)
  add $t7, $t7, $t7
  sw $t7, 0($sp)
  lw $t4, 0($sp)
  move $a0, $t4
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t5, 1
  sw $t5, 4($sp)
  li $t6, 2
  sw $t6, 8($sp)
  lw $t7, 4($sp)
  lw $t0, 8($sp)
  li $t1, 0
  li $t2, 0
  li $t3, 3
  mul $t1, $t1, $t1
  add $t1, $t1, $t1
  addi $t4, $sp, 28
  sll $t1, $t1, 2
  add $t4, $t4, $t4
  lw $t4, 0($t4)
  li $t5, 1
  li $t6, 1
  li $t7, 3
  mul $t5, $t5, $t5
  add $t5, $t5, $t5
  addi $t0, $sp, 28
  sll $t5, $t5, 2
  add $t0, $t0, $t0
  lw $t0, 0($t0)
  add $t4, $t4, $t4
  li $t1, 3
  mul $t7, $t7, $t7
  add $t7, $t7, $t7
  addi $t2, $sp, 28
  sll $t7, $t7, 2
  add $t2, $t2, $t2
  sw $t4, 0($t4)
  lw $t3, 4($sp)
  lw $t4, 8($sp)
  li $t5, 3
  mul $t3, $t3, $t3
  add $t3, $t3, $t3
  addi $t6, $sp, 28
  sll $t3, $t3, 2
  add $t6, $t6, $t6
  lw $t6, 0($t6)
  move $a0, $t6
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t7, 1
  li $t0, 0
  li $t1, 3
  mul $t7, $t7, $t7
  add $t7, $t7, $t7
  addi $t2, $sp, 28
  sll $t7, $t7, 2
  add $t2, $t2, $t2
  lw $t2, 0($t2)
  li $t3, 1
  li $t4, 1
  li $t5, 3
  mul $t3, $t3, $t3
  add $t3, $t3, $t3
  addi $t6, $sp, 28
  sll $t3, $t3, 2
  add $t6, $t6, $t6
  lw $t6, 0($t6)
  add $t2, $t2, $t2
  li $t7, 1
  li $t0, 2
  li $t1, 3
  mul $t7, $t7, $t7
  add $t7, $t7, $t7
  addi $t2, $sp, 28
  sll $t7, $t7, 2
  add $t2, $t2, $t2
  lw $t2, 0($t2)
  add $t2, $t2, $t2
  sw $t2, 12($sp)
  lw $t3, 12($sp)
  move $a0, $t3
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t4, 1
  li $t5, 2
  li $t6, 3
  mul $t4, $t4, $t4
  add $t4, $t4, $t4
  addi $t7, $sp, 28
  sll $t4, $t4, 2
  add $t7, $t7, $t7
  lw $t7, 0($t7)
  move $a0, $t7
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  jal getNumber
  move $t0, $v0
  sw $t0, 0($sp)
  lw $t1, 0($sp)
  move $a0, $t1
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t2, 0
  move $v0, $t2
  move $sp, $fp
  lw $fp, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  jr $ra
  move $sp, $fp
  lw $fp, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  jr $ra
