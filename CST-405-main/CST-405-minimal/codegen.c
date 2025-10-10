#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"
#include "symtab.h"

FILE* output;
int tempReg = 0;

int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 7) tempReg = 0;  // Reuse $t0-$t7
    return reg;
}

/* Helper: Get number of columns for 2D array */
static int getArray2DCols(const char* name) {
    int rows, cols;
    getArray2DSizes(name, &rows, &cols);
    return cols;
}

/* ===================== predeclare symbols (1D + 2D arrays) ===================== */
static void predeclareSymbols(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_DECL:
            (void)addVar(node->data.name);
            break;
        case NODE_ARRAY_DECL:
            (void)addArray(node->data.arrdecl.name, node->data.arrdecl.size);
            break;
        case NODE_ARRAY2D_DECL:
            (void)addArray2D(node->data.arr2d_decl.name,
                             node->data.arr2d_decl.rows,
                             node->data.arr2d_decl.cols);
            break;
        case NODE_STMT_LIST:
            predeclareSymbols(node->data.stmtlist.stmt);
            predeclareSymbols(node->data.stmtlist.next);
            break;
        default:
            break;
    }
}
/* =================================================================================== */

void genExpr(ASTNode* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_NUM:
            fprintf(output, "    li $t%d, %d\n", getNextTemp(), node->data.num);
            break;
            
        case NODE_VAR: {
            int offset = getVarOffset(node->data.name);
            if (offset == -1) {
                fprintf(stderr, "Error: Variable %s not declared\n", node->data.name);
                exit(1);
            }
            fprintf(output, "    lw $t%d, %d($sp)\n", getNextTemp(), offset);
            break;
        }
        
        case NODE_BINOP: {
            genExpr(node->data.binop.left);
            int leftReg = tempReg - 1;
            genExpr(node->data.binop.right);
            int rightReg = tempReg - 1;
            if (node->data.binop.op == '+')
                fprintf(output, "    add $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
            else if (node->data.binop.op == '-')
                fprintf(output, "    sub $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
            else {
                fprintf(stderr, "Error: unsupported binop '%c'\n", node->data.binop.op);
                exit(1);
            }
            tempReg = leftReg + 1;
            break;
        }

        /* ===== 1D array access ===== */
        case NODE_ARRAY_ACCESS: {
            int base = getVarOffset(node->data.arraccess.name);
            if (base == -1) {
                fprintf(stderr, "Error: Array %s not declared\n", node->data.arraccess.name);
                exit(1);
            }
            genExpr(node->data.arraccess.index);
            int idxReg = tempReg - 1;

            int addrReg = getNextTemp();
            fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, base);
            fprintf(output, "    sll $t%d, $t%d, 2\n", idxReg, idxReg);
            fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, idxReg);
            fprintf(output, "    lw $t%d, 0($t%d)\n", addrReg, addrReg);
            tempReg = addrReg + 1;
            break;
        }

        /* ===== NEW: 2D array element access ===== */
        case NODE_ARRAY2D_ACCESS: {
            int base = getVarOffset(node->data.arr2d_access.name);
            int cols = getArray2DCols(node->data.arr2d_access.name);
            if (base == -1) {
                fprintf(stderr, "Error: Array %s not declared\n", node->data.arr2d_access.name);
                exit(1);
            }

            /* Evaluate row and col indices */
            genExpr(node->data.arr2d_access.row);
            int rowReg = tempReg - 1;
            genExpr(node->data.arr2d_access.col);
            int colReg = tempReg - 1;

            /* Compute linearized index: (row * cols) + col */
            fprintf(output, "    li $t%d, %d\n", getNextTemp(), cols);
            int colsReg = tempReg - 1;
            fprintf(output, "    mul $t%d, $t%d, $t%d\n", rowReg, rowReg, colsReg);
            fprintf(output, "    add $t%d, $t%d, $t%d\n", rowReg, rowReg, colReg);

            /* Compute address = base + 4 * index */
            int addrReg = getNextTemp();
            fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, base);
            fprintf(output, "    sll $t%d, $t%d, 2\n", rowReg, rowReg);
            fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, rowReg);
            fprintf(output, "    lw $t%d, 0($t%d)\n", addrReg, addrReg);

            tempReg = addrReg + 1;
            break;
        }

        default:
            break;
    }
}

void genStmt(ASTNode* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_DECL: {
            int offset = getVarOffset(node->data.name);
            fprintf(output, "    # Declared %s at offset %d\n", node->data.name, offset);
            break;
        }
        case NODE_ARRAY_DECL: {
            int base = getVarOffset(node->data.arrdecl.name);
            fprintf(output, "    # Declared array %s[%d] at offset %d (bytes %d)\n",
                    node->data.arrdecl.name,
                    node->data.arrdecl.size,
                    base,
                    node->data.arrdecl.size * 4);
            break;
        }

        /* ===== NEW: 2D array declaration ===== */
        case NODE_ARRAY2D_DECL: {
            int base = getVarOffset(node->data.arr2d_decl.name);
            fprintf(output, "    # Declared 2D array %s[%d][%d] at offset %d (bytes %d)\n",
                    node->data.arr2d_decl.name,
                    node->data.arr2d_decl.rows,
                    node->data.arr2d_decl.cols,
                    base,
                    node->data.arr2d_decl.rows * node->data.arr2d_decl.cols * 4);
            break;
        }

        case NODE_ASSIGN: {
            int offset = getVarOffset(node->data.assign.var);
            genExpr(node->data.assign.value);
            fprintf(output, "    sw $t%d, %d($sp)\n", tempReg - 1, offset);
            tempReg = 0;
            break;
        }

        /* ===== 1D array element assignment ===== */
        case NODE_ARRAY_ASSIGN: {
            int base = getVarOffset(node->data.arrassign.var);
            genExpr(node->data.arrassign.index);
            int idxReg = tempReg - 1;
            genExpr(node->data.arrassign.value);
            int valReg = tempReg - 1;

            int addrReg = getNextTemp();
            fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, base);
            fprintf(output, "    sll $t%d, $t%d, 2\n", idxReg, idxReg);
            fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, idxReg);
            fprintf(output, "    sw $t%d, 0($t%d)\n", valReg, addrReg);

            tempReg = 0;
            break;
        }

        /* ===== NEW: 2D array element assignment ===== */
        case NODE_ARRAY2D_ASSIGN: {
            int base = getVarOffset(node->data.arr2d_assign.var);
            int cols = getArray2DCols(node->data.arr2d_assign.var);

            genExpr(node->data.arr2d_assign.row);
            int rowReg = tempReg - 1;
            genExpr(node->data.arr2d_assign.col);
            int colReg = tempReg - 1;
            genExpr(node->data.arr2d_assign.value);
            int valReg = tempReg - 1;

            /* Compute index = row * cols + col */
            fprintf(output, "    li $t%d, %d\n", getNextTemp(), cols);
            int colsReg = tempReg - 1;
            fprintf(output, "    mul $t%d, $t%d, $t%d\n", rowReg, rowReg, colsReg);
            fprintf(output, "    add $t%d, $t%d, $t%d\n", rowReg, rowReg, colReg);

            int addrReg = getNextTemp();
            fprintf(output, "    addi $t%d, $sp, %d\n", addrReg, base);
            fprintf(output, "    sll $t%d, $t%d, 2\n", rowReg, rowReg);
            fprintf(output, "    add $t%d, $t%d, $t%d\n", addrReg, addrReg, rowReg);
            fprintf(output, "    sw $t%d, 0($t%d)\n", valReg, addrReg);

            tempReg = 0;
            break;
        }

        case NODE_PRINT:
            genExpr(node->data.expr);
            fprintf(output, "    move $a0, $t%d\n", tempReg - 1);
            fprintf(output, "    li $v0, 1\n");
            fprintf(output, "    syscall\n");
            fprintf(output, "    li $v0, 11\n");
            fprintf(output, "    li $a0, 10\n");
            fprintf(output, "    syscall\n");
            tempReg = 0;
            break;

        case NODE_STMT_LIST:
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;
    }
}

void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) {
        fprintf(stderr, "Cannot open output file %s\n", filename);
        exit(1);
    }
    
    initSymTab();
    predeclareSymbols(root);
    int frameBytes = getTotalStackBytes();
    if (frameBytes < 0) frameBytes = 0;

    fprintf(output, ".data\n\n.text\n.globl main\nmain:\n");
    fprintf(output, "    addi $sp, $sp, -%d\n\n", frameBytes);
    
    genStmt(root);
    
    fprintf(output, "\n    addi $sp, $sp, %d\n", frameBytes);
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");
    
    fclose(output);
}
