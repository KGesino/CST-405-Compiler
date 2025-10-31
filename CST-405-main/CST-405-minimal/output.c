.data

.text

.globl getPi
getPi:
  addi $sp, $sp, -8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  move $fp, $sp
  # float literal 3.141590
  li.s $f0, 3.141590
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

.globl addFloats
addFloats:
  addi $sp, $sp, -8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -12
  sw $a0, 0($sp)
  sw $a1, 4($sp)
  # decl result at 8
  lw $t1, 0($sp)
  lw $t2, 4($sp)
  add $t3, $t3, $t3
  sw $t3, 8($sp)
  lw $t4, 8($sp)
  move $v0, $t4
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
  addi $sp, $sp, -56
  # decl i at 0
  # decl x at 4
  # decl y at 8
  # decl z at 12
  # decl r at 16
  # array arr[3] base 20
  # array2D mat[2][3] base 32
  # float literal 1.500000
  li.s $f5, 1.500000
  sw $t5, 4($sp)
  # float literal 2.250000
  li.s $f6, 2.250000
  sw $t6, 8($sp)
  lw $t7, 4($sp)
  lw $t0, 8($sp)
  add $t1, $t1, $t1
  sw $t1, 12($sp)
  lw $t2, 12($sp)
  move $a0, $t2
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t3, 12($sp)
  # float literal 1.000000
  li.s $f4, 1.000000
  sub.s $f5, $f3, $f4
  sw $t5, 16($sp)
  lw $t6, 16($sp)
  move $a0, $t6
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t7, 0
  # float literal 3.500000
  li.s $f0, 3.500000
  addi $t1, $sp, 20
  sll $t7, $t7, 2
  add $t1, $t1, $t1
  sw $t0, 0($t0)
  li $t2, 1
  # float literal 4.500000
  li.s $f3, 4.500000
  addi $t4, $sp, 20
  sll $t2, $t2, 2
  add $t4, $t4, $t4
  sw $t3, 0($t3)
  li $t5, 2
  li $t6, 0
  addi $t7, $sp, 20
  sll $t6, $t6, 2
  add $t7, $t7, $t7
  lw $t7, 0($t7)
  li $t0, 1
  addi $t1, $sp, 20
  sll $t0, $t0, 2
  add $t1, $t1, $t1
  lw $t1, 0($t1)
  add $t2, $t2, $t2
  addi $t3, $sp, 20
  sll $t5, $t5, 2
  add $t3, $t3, $t3
  sw $t2, 0($t2)
  li $t4, 2
  addi $t5, $sp, 20
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
  # float literal 1.100000
  li.s $f0, 1.100000
  li $t1, 3
  mul $t6, $t6, $t6
  add $t6, $t6, $t6
  addi $t2, $sp, 32
  sll $t6, $t6, 2
  add $t2, $t2, $t2
  sw $t0, 0($t0)
  li $t3, 0
  li $t4, 1
  # float literal 2.200000
  li.s $f5, 2.200000
  li $t6, 3
  mul $t3, $t3, $t3
  add $t3, $t3, $t3
  addi $t7, $sp, 32
  sll $t3, $t3, 2
  add $t7, $t7, $t7
  sw $t5, 0($t5)
  li $t0, 0
  li $t1, 2
  # float literal 3.300000
  li.s $f2, 3.300000
  li $t3, 3
  mul $t0, $t0, $t0
  add $t0, $t0, $t0
  addi $t4, $sp, 32
  sll $t0, $t0, 2
  add $t4, $t4, $t4
  sw $t2, 0($t2)
  li $t5, 1
  li $t6, 0
  # float literal 4.400000
  li.s $f7, 4.400000
  li $t0, 3
  mul $t5, $t5, $t5
  add $t5, $t5, $t5
  addi $t1, $sp, 32
  sll $t5, $t5, 2
  add $t1, $t1, $t1
  sw $t7, 0($t7)
  li $t2, 1
  li $t3, 1
  # float literal 5.500000
  li.s $f4, 5.500000
  li $t5, 3
  mul $t2, $t2, $t2
  add $t2, $t2, $t2
  addi $t6, $sp, 32
  sll $t2, $t2, 2
  add $t6, $t6, $t6
  sw $t4, 0($t4)
  li $t7, 1
  li $t0, 2
  # float literal 6.600000
  li.s $f1, 6.600000
  li $t2, 3
  mul $t7, $t7, $t7
  add $t7, $t7, $t7
  addi $t3, $sp, 32
  sll $t7, $t7, 2
  add $t3, $t3, $t3
  sw $t1, 0($t1)
  li $t4, 0
  li $t5, 1
  li $t6, 3
  mul $t4, $t4, $t4
  add $t4, $t4, $t4
  addi $t7, $sp, 32
  sll $t4, $t4, 2
  add $t7, $t7, $t7
  lw $t7, 0($t7)
  li $t0, 1
  li $t1, 2
  li $t2, 3
  mul $t0, $t0, $t0
  add $t0, $t0, $t0
  addi $t3, $sp, 32
  sll $t0, $t0, 2
  add $t3, $t3, $t3
  lw $t3, 0($t3)
  add $t4, $t4, $t4
  sw $t4, 4($sp)
  lw $t5, 4($sp)
  move $a0, $t5
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  # float literal 0.000000
  li.s $f6, 0.000000
  sw $t6, 8($sp)
  # float literal 1.000000
  li.s $f7, 1.000000
  sw $t7, 12($sp)
  li $t0, 0
  li $t1, 1
  li $t2, 0
  li $t3, 0
  li $t4, 3
  mul $t2, $t2, $t2
  add $t2, $t2, $t2
  addi $t5, $sp, 32
  sll $t2, $t2, 2
  add $t5, $t5, $t5
  lw $t5, 0($t5)
  li $t6, 1
  li $t7, 1
  li $t0, 3
  mul $t6, $t6, $t6
  add $t6, $t6, $t6
  addi $t1, $sp, 32
  sll $t6, $t6, 2
  add $t1, $t1, $t1
  lw $t1, 0($t1)
  add $t2, $t2, $t2
  li $t3, 3
  mul $t0, $t0, $t0
  add $t0, $t0, $t0
  addi $t4, $sp, 32
  sll $t0, $t0, 2
  add $t4, $t4, $t4
  sw $t2, 0($t2)
  li $t5, 0
  li $t6, 1
  li $t7, 3
  mul $t5, $t5, $t5
  add $t5, $t5, $t5
  addi $t0, $sp, 32
  sll $t5, $t5, 2
  add $t0, $t0, $t0
  lw $t0, 0($t0)
  move $a0, $t0
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t1, 1
  li $t2, 0
  li $t3, 3
  mul $t1, $t1, $t1
  add $t1, $t1, $t1
  addi $t4, $sp, 32
  sll $t1, $t1, 2
  add $t4, $t4, $t4
  lw $t4, 0($t4)
  li $t5, 1
  li $t6, 1
  li $t7, 3
  mul $t5, $t5, $t5
  add $t5, $t5, $t5
  addi $t0, $sp, 32
  sll $t5, $t5, 2
  add $t0, $t0, $t0
  lw $t0, 0($t0)
  add $t1, $t1, $t1
  li $t2, 1
  li $t3, 2
  li $t4, 3
  mul $t2, $t2, $t2
  add $t2, $t2, $t2
  addi $t5, $sp, 32
  sll $t2, $t2, 2
  add $t5, $t5, $t5
  lw $t5, 0($t5)
  add $t6, $t6, $t6
  sw $t6, 16($sp)
  lw $t7, 16($sp)
  move $a0, $t7
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t0, 1
  li $t1, 2
  li $t2, 3
  mul $t0, $t0, $t0
  add $t0, $t0, $t0
  addi $t3, $sp, 32
  sll $t0, $t0, 2
  add $t3, $t3, $t3
  lw $t3, 0($t3)
  move $a0, $t3
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  jal getPi
  move $t4, $v0
  sw $t4, 12($sp)
  lw $t5, 12($sp)
  move $a0, $t5
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  # float literal 1.250000
  li.s $f6, 1.250000
  # float literal 2.750000
  li.s $f7, 2.750000
  move $a0, $t6
  move $a1, $t7
  jal addFloats
  move $t0, $v0
  sw $t0, 4($sp)
  lw $t1, 4($sp)
  move $a0, $t1
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t2, 4($sp)
  # float literal 2.000000
  li.s $f3, 2.000000
