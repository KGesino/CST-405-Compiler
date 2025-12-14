.data

.text
.globl _start
_start:
 jal main
 li $v0, 10
 syscall


.globl check
check:
 addi $sp, $sp, -8
 sw $ra, 4($sp)
 sw $fp, 0($sp)
 move $fp, $sp
 addi $sp, $sp, -8
 sw $a0, 0($sp)
 # decl y at 4
 lw $t0, 0($sp)
 li $t1, 1
 add $t2, $t0, $t1
 sw $t2, 4($sp)
 lw $t3, 4($sp)
 li $t4, 5
 li $t5, 0
 beqz $t5, L_if_false_0
 lw $t6, 4($sp)
 li $t7, 1
 sub $t8, $t6, $t7
 sw $t8, 4($sp)
 j L_if_end_0
L_if_false_0:
 li $t9, 0
 sw $t9, 4($sp)
L_if_end_0:
 lw $s0, 4($sp)
 move $v0, $s0
 j check_epilogue
check_epilogue:
 move $sp, $fp
 lw $fp, 0($sp)
 lw $ra, 4($sp)
 addi $sp, $sp, 8
 jr $ra

.globl loopfun
loopfun:
 addi $sp, $sp, -8
 sw $ra, 4($sp)
 sw $fp, 0($sp)
 move $fp, $sp
 addi $sp, $sp, -8
 sw $a0, 0($sp)
 # decl i at 4
 li $t0, 0
 sw $t0, 4($sp)
L_while_start_0:
 lw $t1, 4($sp)
 lw $t2, 0($sp)
 li $t3, 0
 beqz $t3, L_while_end_0
 lw $t4, 4($sp)
 li $t5, 1
 add $t6, $t4, $t5
 sw $t6, 4($sp)
 j L_while_start_0
L_while_end_0:
 lw $t7, 4($sp)
 move $v0, $t7
 j loopfun_epilogue
loopfun_epilogue:
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
 addi $sp, $sp, -8
 # decl a at 0
 # decl b at 4
 li $t0, 0
 sw $t0, 0($sp)
 li $t1, 0
 sw $t1, 4($sp)
main_epilogue:
 move $sp, $fp
 lw $fp, 0($sp)
 lw $ra, 4($sp)
 addi $sp, $sp, 8
 jr $ra
