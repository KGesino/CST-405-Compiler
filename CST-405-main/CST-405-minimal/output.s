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
  addi $sp, $sp, -76
  # decl i at 0
  # decl j at 4
  # decl k at 8
  # decl x at 12
  # decl y at 16
  # decl z at 20
  # decl r at 24
  # decl flag1 at 64
  # decl flag2 at 68
  # decl resultBool at 72
  .data
L_fconst_1: .float 1.500000
.text
  l.s $f5, L_fconst_1
  sw $t5, 12($sp)
  .data
L_fconst_2: .float 2.250000
.text
  l.s $f6, L_fconst_2
  sw $t6, 16($sp)
  lw $t7, 12($sp)
  lw $t0, 16($sp)
  add $t1, $t1, $t1
  sw $t1, 20($sp)
  lw $t2, 20($sp)
  move $a0, $t2
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t3, 20($sp)
  .data
L_fconst_3: .float 1.000000
.text
  l.s $f4, L_fconst_3
  mtc1 $t3, $f3
  cvt.s.w $f3, $f3
  sub.s $f5, $f5, $f5
  sw $t5, 24($sp)
  lw $t6, 24($sp)
  move $a0, $t6
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t7, 12($sp)
  lw $t0, 16($sp)
  mul $t1, $t1, $t1
  sw $t1, 20($sp)
  lw $t2, 20($sp)
  move $a0, $t2
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t3, 20($sp)
  .data
L_fconst_4: .float 2.000000
.text
  l.s $f4, L_fconst_4
  mtc1 $t3, $f3
  cvt.s.w $f3, $f3
  div.s $f5, $f5, $f5
  sw $t5, 24($sp)
  lw $t6, 24($sp)
  move $a0, $t6
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  .data
L_fconst_5: .float 10.000000
.text
  l.s $f7, L_fconst_5
  sw $t7, 12($sp)
  .data
L_fconst_6: .float 2.000000
.text
  l.s $f0, L_fconst_6
  sw $t0, 16($sp)
  lw $t1, 12($sp)
  lw $t2, 16($sp)
  div $t3, $t3, $t3
  sw $t3, 20($sp)
  lw $t4, 20($sp)
  move $a0, $t4
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t5, 20($sp)
  .data
L_fconst_7: .float 2.000000
.text
  l.s $f6, L_fconst_7
  mtc1 $t5, $f5
  cvt.s.w $f5, $f5
  div.s $f7, $f7, $f7
  sw $t7, 20($sp)
  lw $t0, 20($sp)
  move $a0, $t0
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t1, 0
  move $a0, $t1
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t2, 0
  move $a0, $t2
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t3, 0
  move $a0, $t3
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t4, 0
  li $t5, 0
  add $t6, $t6, $t6
  sw $t6, 12($sp)
  lw $t7, 12($sp)
  move $a0, $t7
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  .data
L_fconst_8: .float 0.000000
.text
  l.s $f0, L_fconst_8
  sw $t0, 16($sp)
  .data
L_fconst_9: .float 1.000000
.text
  l.s $f1, L_fconst_9
  sw $t1, 20($sp)
  li $t2, 0
  move $a0, $t2
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t3, 0
  li $t4, 0
  add $t5, $t5, $t5
  li $t6, 0
  add $t7, $t7, $t7
  sw $t7, 24($sp)
  lw $t0, 24($sp)
  move $a0, $t0
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t1, 0
  move $a0, $t1
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t2, 0
  move $a0, $t2
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t3, 0
  move $a0, $t3
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  li $t4, 0
  sw $t4, 20($sp)
  lw $t5, 20($sp)
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
  li $t0, 10
  sw $t0, 0($sp)
  li $t1, 2
  sw $t1, 4($sp)
  lw $t2, 0($sp)
  lw $t3, 4($sp)
  mul $t4, $t4, $t4
  sw $t4, 8($sp)
  lw $t5, 8($sp)
  move $a0, $t5
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t6, 0($sp)
  lw $t7, 4($sp)
  div $t0, $t0, $t0
  sw $t0, 8($sp)
  lw $t1, 8($sp)
  move $a0, $t1
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t2, 0($sp)
  .data
L_fconst_10: .float 2.500000
.text
  l.s $f3, L_fconst_10
  mtc1 $t2, $f2
  cvt.s.w $f2, $f2
  mul.s $f4, $f4, $f4
  sw $t4, 12($sp)
  lw $t5, 12($sp)
  move $a0, $t5
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  .data
L_fconst_11: .float 7.500000
.text
  l.s $f6, L_fconst_11
  lw $t7, 0($sp)
  mtc1 $t7, $f7
  cvt.s.w $f7, $f7
  mul.s $f0, $f0, $f0
  sw $t0, 16($sp)
  lw $t1, 16($sp)
  move $a0, $t1
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t2, 12($sp)
  .data
L_fconst_12: .float 2.000000
.text
  l.s $f3, L_fconst_12
  mtc1 $t2, $f2
  cvt.s.w $f2, $f2
  c.le.s $f3, $f3
  bc1t 1f
  li $t4, 1
  j 2f
1: li $t4, 0
2:
  beqz $t4, L_if_false_0
  .data
L_fconst_13: .float 100.000000
.text
  l.s $f5, L_fconst_13
  mov.s $f12, $f5
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_0
L_if_false_0:
L_if_end_0:
  lw $t6, 12($sp)
  .data
L_fconst_14: .float 3.000000
.text
  l.s $f7, L_fconst_14
  mtc1 $t6, $f6
  cvt.s.w $f6, $f6
  c.lt.s $f6, $f6
  bc1t 1f
  li $t0, 0
  j 2f
1: li $t0, 1
2:
  beqz $t0, L_if_false_1
  .data
L_fconst_15: .float 200.000000
.text
  l.s $f1, L_fconst_15
  mov.s $f12, $f1
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_1
L_if_false_1:
  .data
L_fconst_16: .float 300.000000
.text
  l.s $f2, L_fconst_16
  mov.s $f12, $f2
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_1:
  lw $t3, 24($sp)
  .data
L_fconst_17: .float 10.000000
.text
  l.s $f4, L_fconst_17
  mtc1 $t3, $f3
  cvt.s.w $f3, $f3
  c.le.s $f4, $f4
  bc1t 1f
  li $t5, 1
  j 2f
1: li $t5, 0
2:
  beqz $t5, L_if_false_2
  lw $t6, 24($sp)
  .data
L_fconst_18: .float 20.000000
.text
  l.s $f7, L_fconst_18
  mtc1 $t6, $f6
  cvt.s.w $f6, $f6
  c.lt.s $f6, $f6
  bc1t 1f
  li $t0, 0
  j 2f
1: li $t0, 1
2:
  beqz $t0, L_if_false_3
  .data
L_fconst_19: .float 400.000000
.text
  l.s $f1, L_fconst_19
  mov.s $f12, $f1
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_3
L_if_false_3:
  .data
L_fconst_20: .float 500.000000
.text
  l.s $f2, L_fconst_20
  mov.s $f12, $f2
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_3:
  j L_if_end_2
L_if_false_2:
  .data
L_fconst_21: .float 600.000000
.text
  l.s $f3, L_fconst_21
  mov.s $f12, $f3
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_2:
  lw $t4, 0($sp)
  li $t5, 10
  seq $t6, $t6, $t6
  beqz $t6, L_if_false_4
  .data
L_fconst_22: .float 700.000000
.text
  l.s $f7, L_fconst_22
  mov.s $f12, $f7
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_4
L_if_false_4:
  .data
L_fconst_23: .float 800.000000
.text
  l.s $f0, L_fconst_23
  mov.s $f12, $f0
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_4:
  lw $t1, 12($sp)
  lw $t2, 16($sp)
  add $t3, $t3, $t3
  lw $t4, 24($sp)
  .data
L_fconst_24: .float 10.000000
.text
  l.s $f5, L_fconst_24
  mtc1 $t4, $f4
  cvt.s.w $f4, $f4
  sub.s $f6, $f6, $f6
  sgt $t7, $t7, $t7
  beqz $t7, L_if_false_5
  .data
L_fconst_25: .float 900.000000
.text
  l.s $f0, L_fconst_25
  mov.s $f12, $f0
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_5
L_if_false_5:
  .data
L_fconst_26: .float 1000.000000
.text
  l.s $f1, L_fconst_26
  mov.s $f12, $f1
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_5:
  li $t2, 1
  sw $t2, 64($sp)
  li $t3, 0
  sw $t3, 68($sp)
  lw $t4, 68($sp)
  seq $t4, $t4, $zero
  sw $t4, 72($sp)
  lw $t5, 72($sp)
  beqz $t5, L_if_false_6
  .data
L_fconst_27: .float 1100.000000
.text
  l.s $f6, L_fconst_27
  mov.s $f12, $f6
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_6
L_if_false_6:
L_if_end_6:
  lw $t7, 64($sp)
  lw $t0, 68($sp)
  sne $t7, $t7, $zero
  sne $t0, $t0, $zero
  and $t1, $t1, $t1
  beqz $t1, L_if_false_7
  .data
L_fconst_28: .float 1200.000000
.text
  l.s $f2, L_fconst_28
  mov.s $f12, $f2
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_7
L_if_false_7:
  .data
L_fconst_29: .float 1300.000000
.text
  l.s $f3, L_fconst_29
  mov.s $f12, $f3
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_7:
  lw $t4, 64($sp)
  lw $t5, 68($sp)
  or $t6, $t6, $t6
  sne $t6, $t6, $zero
  beqz $t6, L_if_false_8
  .data
L_fconst_30: .float 1400.000000
.text
  l.s $f7, L_fconst_30
  mov.s $f12, $f7
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_8
L_if_false_8:
  .data
L_fconst_31: .float 1500.000000
.text
  l.s $f0, L_fconst_31
  mov.s $f12, $f0
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_8:
  lw $t1, 64($sp)
  lw $t2, 12($sp)
  .data
L_fconst_32: .float 0.000000
.text
  l.s $f3, L_fconst_32
  mtc1 $t2, $f2
  cvt.s.w $f2, $f2
  c.le.s $f3, $f3
  bc1t 1f
  li $t4, 1
  j 2f
1: li $t4, 0
2:
  sne $t1, $t1, $zero
  sne $t4, $t4, $zero
  and $t5, $t5, $t5
  lw $t6, 24($sp)
  .data
L_fconst_33: .float 5.000000
.text
  l.s $f7, L_fconst_33
  mtc1 $t6, $f6
  cvt.s.w $f6, $f6
  c.lt.s $f6, $f6
  bc1t 1f
  li $t0, 0
  j 2f
1: li $t0, 1
2:
  or $t1, $t1, $t1
  sne $t1, $t1, $zero
  sw $t1, 72($sp)
  lw $t2, 72($sp)
  beqz $t2, L_if_false_9
  .data
L_fconst_34: .float 1600.000000
.text
  l.s $f3, L_fconst_34
  mov.s $f12, $f3
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_9
L_if_false_9:
  .data
L_fconst_35: .float 1700.000000
.text
  l.s $f4, L_fconst_35
  mov.s $f12, $f4
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_9:
  lw $t5, 12($sp)
  lw $t6, 24($sp)
  slt $t7, $t7, $t7
  sw $t7, 64($sp)
  lw $t0, 20($sp)
  lw $t1, 16($sp)
  sgt $t2, $t2, $t2
  seq $t2, $t2, $zero
  sw $t2, 68($sp)
  lw $t3, 64($sp)
  lw $t4, 68($sp)
  sne $t3, $t3, $zero
  sne $t4, $t4, $zero
  and $t5, $t5, $t5
  beqz $t5, L_if_false_10
  .data
L_fconst_36: .float 1800.000000
.text
  l.s $f6, L_fconst_36
  mov.s $f12, $f6
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_10
L_if_false_10:
  .data
L_fconst_37: .float 1900.000000
.text
  l.s $f7, L_fconst_37
  mov.s $f12, $f7
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_10:
  li $t0, 0
  sw $t0, 0($sp)
L_while_start_0:
  lw $t1, 0($sp)
  li $t2, 3
  slt $t3, $t3, $t3
  beqz $t3, L_while_end_0
  .data
L_fconst_38: .float 3000.000000
.text
  l.s $f4, L_fconst_38
  lw $t5, 0($sp)
  mtc1 $t5, $f5
  cvt.s.w $f5, $f5
  add.s $f6, $f6, $f6
  move $a0, $t6
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t7, 0($sp)
  li $t0, 1
  add $t1, $t1, $t1
  sw $t1, 0($sp)
  j L_while_start_0
L_while_end_0:
  li $t2, 5
  sw $t2, 4($sp)
L_while_start_1:
  lw $t3, 4($sp)
  li $t4, 0
  sgt $t5, $t5, $t5
  beqz $t5, L_while_end_1
  .data
L_fconst_39: .float 4000.000000
.text
  l.s $f6, L_fconst_39
  lw $t7, 4($sp)
  mtc1 $t7, $f7
  cvt.s.w $f7, $f7
  add.s $f0, $f0, $f0
  move $a0, $t0
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t1, 4($sp)
  li $t2, 1
  sub $t3, $t3, $t3
  sw $t3, 4($sp)
  j L_while_start_1
L_while_end_1:
  li $t4, 0
  sw $t4, 0($sp)
L_while_start_2:
  lw $t5, 0($sp)
  li $t6, 2
  slt $t7, $t7, $t7
  beqz $t7, L_while_end_2
  li $t0, 0
  sw $t0, 4($sp)
L_while_start_3:
  lw $t1, 4($sp)
  li $t2, 2
  slt $t3, $t3, $t3
  beqz $t3, L_while_end_3
  lw $t4, 0($sp)
  lw $t5, 4($sp)
  seq $t6, $t6, $t6
  beqz $t6, L_if_false_11
  .data
L_fconst_40: .float 5000.000000
.text
  l.s $f7, L_fconst_40
  lw $t0, 0($sp)
  li $t1, 10
  mul $t2, $t2, $t2
  mtc1 $t2, $f2
  cvt.s.w $f2, $f2
  add.s $f3, $f3, $f3
  lw $t4, 4($sp)
  add $t5, $t5, $t5
  move $a0, $t5
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_11
L_if_false_11:
  .data
L_fconst_41: .float 5100.000000
.text
  l.s $f6, L_fconst_41
  lw $t7, 0($sp)
  li $t0, 10
  mul $t1, $t1, $t1
  mtc1 $t1, $f1
  cvt.s.w $f1, $f1
  add.s $f2, $f2, $f2
  lw $t3, 4($sp)
  add $t4, $t4, $t4
  move $a0, $t4
  li $v0, 1
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_11:
  lw $t5, 4($sp)
  li $t6, 1
  add $t7, $t7, $t7
  sw $t7, 4($sp)
  j L_while_start_3
L_while_end_3:
  lw $t0, 0($sp)
  li $t1, 1
  add $t2, $t2, $t2
  sw $t2, 0($sp)
  j L_while_start_2
L_while_end_2:

  # --- Begin race block ---
  # Strategy: first_wins
  li $t7, 0        # race_flag = 0
  j L_race_left_0
L_race_left_0:
  .data
L_fconst_42: .float 2000.000000
.text
  l.s $f3, L_fconst_42
  mov.s $f12, $f3
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  beqz $t7, L_race_end_0
  j L_race_right_0
L_race_right_0:
  .data
L_fconst_43: .float 2100.000000
.text
  l.s $f4, L_fconst_43
  mov.s $f12, $f4
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  beqz $t7, L_race_end_0
  j L_race_end_0
L_race_end_0:
  li $t7, 1        # first branch won
  # --- End race block ---


  # --- Begin race block ---
  # Strategy: first_wins
  li $t7, 0        # race_flag = 0
  j L_race_left_1
L_race_left_1:
  .data
L_fconst_44: .float 2200.000000
.text
  l.s $f5, L_fconst_44
  mov.s $f12, $f5
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  beqz $t7, L_race_end_1
  j L_race_right_1
L_race_right_1:
  .data
L_fconst_45: .float 2300.000000
.text
  l.s $f6, L_fconst_45
  mov.s $f12, $f6
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  .data
L_fconst_46: .float 2400.000000
.text
  l.s $f7, L_fconst_46
  mov.s $f12, $f7
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  beqz $t7, L_race_end_1
  j L_race_end_1
L_race_end_1:
  li $t7, 1        # first branch won
  # --- End race block ---


  # --- Begin race block ---
  # Strategy: first_wins
  li $t7, 0        # race_flag = 0
  j L_race_left_2
L_race_left_2:
  lw $t0, 12($sp)
  .data
L_fconst_47: .float 5.000000
.text
  l.s $f1, L_fconst_47
  mtc1 $t0, $f0
  cvt.s.w $f0, $f0
  c.le.s $f1, $f1
  bc1t 1f
  li $t2, 1
  j 2f
1: li $t2, 0
2:
  beqz $t2, L_if_false_12
  .data
L_fconst_48: .float 2500.000000
.text
  l.s $f3, L_fconst_48
  mov.s $f12, $f3
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  j L_if_end_12
L_if_false_12:
  .data
L_fconst_49: .float 2600.000000
.text
  l.s $f4, L_fconst_49
  mov.s $f12, $f4
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
L_if_end_12:
  beqz $t7, L_race_end_2
  j L_race_right_2
L_race_right_2:
  .data
L_fconst_50: .float 2700.000000
.text
  l.s $f5, L_fconst_50
  mov.s $f12, $f5
  li $v0, 2
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  beqz $t7, L_race_end_2
  j L_race_end_2
L_race_end_2:
  li $t7, 1        # first branch won
  # --- End race block ---

  li $t6, 0
  move $v0, $t6
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
