.data

.text

.globl getPi
getPi:
  addi $sp, $sp, -8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  move $fp, $sp
  .data
L_fconst_0: .float 3.141590
.text
  l.s $f0, L_fconst_0
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
  addi $sp, $sp, -68
  # decl i at 0
  # decl x at 4
  # decl y at 8
  # decl z at 12
  # decl r at 16
  # decl flag1 at 56
  # decl flag2 at 60
  # decl resultBool at 64
  .data
L_fconst_1: .float 1.500000
.text
  l.s $f5, L_fconst_1
  sw $t5, 4($sp)
  .data
L_fconst_2: .float 2.250000
.text
  l.s $f6, L_fconst_2
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
  .data
L_fconst_3: .float 1.000000
.text
  l.s $f4, L_fconst_3
  sub.s $f5, $f5, $f5
  sw $t5, 16($sp)
  lw $t6, 16($sp)
  move $a0, $t6
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t7, 0
  move $a0, $t7
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t0, 0
  li $t1, 0
  add $t2, $t2, $t2
  sw $t2, 4($sp)
  lw $t3, 4($sp)
  move $a0, $t3
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  .data
L_fconst_4: .float 0.000000
.text
  l.s $f4, L_fconst_4
  sw $t4, 8($sp)
  .data
L_fconst_5: .float 1.000000
.text
  l.s $f5, L_fconst_5
  sw $t5, 12($sp)
  li $t6, 0
  move $a0, $t6
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t7, 0
  li $t0, 0
  add $t1, $t1, $t1
  li $t2, 0
  add $t3, $t3, $t3
  sw $t3, 16($sp)
  lw $t4, 16($sp)
  move $a0, $t4
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t5, 0
  move $a0, $t5
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t6, 0
  sw $t6, 12($sp)
  lw $t7, 12($sp)
  move $a0, $t7
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t0, 0
  sw $t0, 4($sp)
  lw $t1, 4($sp)
  move $a0, $t1
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t2, 4($sp)
  .data
L_fconst_6: .float 2.000000
.text
  l.s $f3, L_fconst_6
  c.lt.s $f3, $f3
  li $t5, 0
  bc1f L_false_0
  li $t5, 1
L_false_0:
  beqz $t5, L_if_false_0
  .data
L_fconst_7: .float 100.000000
.text
  l.s $f6, L_fconst_7
  mov.s $f12, $f6
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_0
L_if_false_0:
L_if_end_0:
  lw $t7, 4($sp)
  .data
L_fconst_8: .float 3.000000
.text
  l.s $f0, L_fconst_8
  c.lt.s $f7, $f7
  li $t2, 0
  bc1f L_false_1
  li $t2, 1
L_false_1:
  beqz $t2, L_if_false_1
  .data
L_fconst_9: .float 200.000000
.text
  l.s $f3, L_fconst_9
  mov.s $f12, $f3
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_1
L_if_false_1:
  .data
L_fconst_10: .float 300.000000
.text
  l.s $f4, L_fconst_10
  mov.s $f12, $f4
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_1:
  lw $t5, 16($sp)
  .data
L_fconst_11: .float 10.000000
.text
  l.s $f6, L_fconst_11
  c.lt.s $f6, $f6
  li $t0, 0
  bc1f L_false_2
  li $t0, 1
L_false_2:
  beqz $t0, L_if_false_2
  lw $t1, 16($sp)
  .data
L_fconst_12: .float 20.000000
.text
  l.s $f2, L_fconst_12
  c.lt.s $f1, $f1
  li $t4, 0
  bc1f L_false_3
  li $t4, 1
L_false_3:
  beqz $t4, L_if_false_3
  .data
L_fconst_13: .float 400.000000
.text
  l.s $f5, L_fconst_13
  mov.s $f12, $f5
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_3
L_if_false_3:
  .data
L_fconst_14: .float 500.000000
.text
  l.s $f6, L_fconst_14
  mov.s $f12, $f6
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_3:
  j L_if_end_2
L_if_false_2:
  .data
L_fconst_15: .float 600.000000
.text
  l.s $f7, L_fconst_15
  mov.s $f12, $f7
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_2:
  li $t0, 5
  sw $t0, 0($sp)
  lw $t1, 0($sp)
  li $t2, 5
  seq $t3, $t3, $t3
  beqz $t3, L_if_false_4
  .data
L_fconst_16: .float 700.000000
.text
  l.s $f4, L_fconst_16
  mov.s $f12, $f4
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_4
L_if_false_4:
  .data
L_fconst_17: .float 800.000000
.text
  l.s $f5, L_fconst_17
  mov.s $f12, $f5
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_4:
  lw $t6, 4($sp)
  lw $t7, 8($sp)
  add $t0, $t0, $t0
  lw $t1, 16($sp)
  .data
L_fconst_18: .float 10.000000
.text
  l.s $f2, L_fconst_18
  sub.s $f3, $f3, $f3
  sgt $t4, $t4, $t4
  beqz $t4, L_if_false_5
  .data
L_fconst_19: .float 900.000000
.text
  l.s $f5, L_fconst_19
  mov.s $f12, $f5
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_5
L_if_false_5:
  .data
L_fconst_20: .float 1000.000000
.text
  l.s $f6, L_fconst_20
  mov.s $f12, $f6
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_5:
  li $t7, 1
  sw $t7, 56($sp)
  li $t0, 0
  sw $t0, 60($sp)
  lw $t1, 60($sp)
  seq $t1, $t1, $zero
  sw $t1, 64($sp)
  lw $t2, 64($sp)
  beqz $t2, L_if_false_6
  .data
L_fconst_21: .float 1100.000000
.text
  l.s $f3, L_fconst_21
  mov.s $f12, $f3
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_6
L_if_false_6:
L_if_end_6:
  lw $t4, 56($sp)
  lw $t5, 60($sp)
  sne $t4, $t4, $zero
  sne $t5, $t5, $zero
  and $t6, $t6, $t6
  beqz $t6, L_if_false_7
  .data
L_fconst_22: .float 1200.000000
.text
  l.s $f7, L_fconst_22
  mov.s $f12, $f7
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_7
L_if_false_7:
  .data
L_fconst_23: .float 1300.000000
.text
  l.s $f0, L_fconst_23
  mov.s $f12, $f0
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_7:
  lw $t1, 56($sp)
  lw $t2, 60($sp)
  or $t3, $t3, $t3
  sne $t3, $t3, $zero
  beqz $t3, L_if_false_8
  .data
L_fconst_24: .float 1400.000000
.text
  l.s $f4, L_fconst_24
  mov.s $f12, $f4
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_8
L_if_false_8:
  .data
L_fconst_25: .float 1500.000000
.text
  l.s $f5, L_fconst_25
  mov.s $f12, $f5
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_8:
  lw $t6, 56($sp)
  lw $t7, 4($sp)
  .data
L_fconst_26: .float 0.000000
.text
  l.s $f0, L_fconst_26
  c.lt.s $f0, $f0
  li $t2, 0
  bc1f L_false_4
  li $t2, 1
L_false_4:
  sne $t6, $t6, $zero
  sne $t2, $t2, $zero
  and $t3, $t3, $t3
  lw $t4, 16($sp)
  .data
L_fconst_27: .float 5.000000
.text
  l.s $f5, L_fconst_27
  c.lt.s $f4, $f4
  li $t7, 0
  bc1f L_false_5
  li $t7, 1
L_false_5:
  or $t0, $t0, $t0
  sne $t0, $t0, $zero
  sw $t0, 64($sp)
  lw $t1, 64($sp)
  beqz $t1, L_if_false_9
  .data
L_fconst_28: .float 1600.000000
.text
  l.s $f2, L_fconst_28
  mov.s $f12, $f2
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_9
L_if_false_9:
  .data
L_fconst_29: .float 1700.000000
.text
  l.s $f3, L_fconst_29
  mov.s $f12, $f3
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_9:
  lw $t4, 4($sp)
  lw $t5, 16($sp)
  slt $t6, $t6, $t6
  sw $t6, 56($sp)
  lw $t7, 12($sp)
  lw $t0, 8($sp)
  sgt $t1, $t1, $t1
  seq $t1, $t1, $zero
  sw $t1, 60($sp)
  lw $t2, 56($sp)
  lw $t3, 60($sp)
  sne $t2, $t2, $zero
  sne $t3, $t3, $zero
  and $t4, $t4, $t4
  beqz $t4, L_if_false_10
  .data
L_fconst_30: .float 1800.000000
.text
  l.s $f5, L_fconst_30
  mov.s $f12, $f5
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_10
L_if_false_10:
  .data
L_fconst_31: .float 1900.000000
.text
  l.s $f6, L_fconst_31
  mov.s $f12, $f6
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_10:
  li $t7, 0
  move $v0, $t7
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
