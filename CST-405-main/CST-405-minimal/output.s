.data

.text
.globl _start
_start:
  jal main
  li $v0, 10
  syscall


.globl main
main:
  addi $sp, $sp, -8
  sw $ra, 4($sp)
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -16
  # decl a at 0
  # decl b at 4
  # decl c at 8
  # decl d at 12
  li $t0, 10
  sw $t0, 0($sp)
  li $t1, 5
  sw $t1, 4($sp)
  li $t2, 20
  sw $t2, 8($sp)
  li $t3, 10
  sw $t3, 12($sp)
L_while_start_0:
  lw $t4, 0($sp)
  lw $t5, 4($sp)
  sgt $t6, $t4, $t5
  lw $t7, 8($sp)
  lw $t8, 12($sp)
  sgt $t9, $t7, $t8
  mul $s0, $t6, $t9
  beqz $s0, L_while_end_0
  li $s1, 114
  li $v0, 11
  move $a0, $s1
  syscall
  li $s2, 61
  li $v0, 11
  move $a0, $s2
  syscall
  lw $s3, 0($sp)
  lw $s4, 4($sp)
  sgt $s5, $s3, $s4
  lw $s6, 8($sp)
  lw $s7, 12($sp)
  sgt $t9, $s6, $s7
  mul $t9, $s5, $t9
  li $v0, 1
  move $a0, $t9
  syscall
  li $v0, 11
  li $a0, 10
  syscall
  lw $t0, 0($sp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, 0($sp)
  j L_while_start_0
L_while_end_0:
  li $t3, 0
  move $v0, $t3
  j main_epilogue
main_epilogue:
  move $sp, $fp
  lw $fp, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  jr $ra
