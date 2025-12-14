/* MINIMAL C COMPILER - EDUCATIONAL VERSION
 * Demonstrates all phases of compilation with a simple language
 * Supports: int variables, addition, assignment, print
 * NOW INCLUDES PERFORMANCE METRICS
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>          /* <-- ADDED for timing */
#include "ast.h"
#include "codegen.h"
#include "tac.h"
#include "symtab.h"

const char* g_input_filename = NULL;
extern int yyparse();
extern FILE* yyin;
extern ASTNode* root;

/* Utility to convert clock ticks to seconds */
static double elapsed_seconds(clock_t start, clock_t end) {
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]) {
    clock_t compiler_start, compiler_end;

    /* Start total compilation timer */
    compiler_start = clock();

    if (argc != 3) {
        printf("Usage: %s <input.c> <output.s>\n", argv[0]);
        printf("Example: ./minicompiler test.c output.s\n");
        return 1;
    }

    /* Initialize symbol table BEFORE parsing */
    initSymTab();

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", argv[1]);
        return 1;
    }

    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║          MINIMAL C COMPILER - EDUCATIONAL VERSION         ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");

    g_input_filename = argv[1];

    /* ============================= */
    /* PHASE 1: Parsing & AST Build */
    /* ============================= */
    clock_t phase1_start = clock();

    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 1: LEXICAL & SYNTAX ANALYSIS                       │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");

    if (yyparse() != 0) {
        printf("✗ Parse failed - check your syntax!\n");
        fclose(yyin);
        return 1;
    }

    clock_t phase1_end = clock();
    printf("✓ Parse successful\n");
    printf("  Time: %.6f seconds\n\n",
           elapsed_seconds(phase1_start, phase1_end));

    /* ============================= */
    /* PHASE 2: AST Display         */
    /* ============================= */
    clock_t phase2_start = clock();

    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 2: ABSTRACT SYNTAX TREE (AST)                      │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    printAST(root, 0);
    printf("\n");

    clock_t phase2_end = clock();
    printf("  Time: %.6f seconds\n\n",
           elapsed_seconds(phase2_start, phase2_end));

    /* ============================= */
    /* PHASE 3: TAC Generation      */
    /* ============================= */
    clock_t phase3_start = clock();

    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 3: INTERMEDIATE CODE GENERATION                    │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    initTAC();
    generateTAC(root);
    printTAC();
    printf("\n");

    clock_t phase3_end = clock();
    printf("  Time: %.6f seconds\n\n",
           elapsed_seconds(phase3_start, phase3_end));

    /* ============================= */
    /* PHASE 4: Optimization        */
    /* ============================= */
    clock_t phase4_start = clock();

    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 4: CODE OPTIMIZATION                               │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    optimizeTAC();
    printOptimizedTAC();
    printf("\n");

    clock_t phase4_end = clock();
    printf("  Time: %.6f seconds\n\n",
           elapsed_seconds(phase4_start, phase4_end));

    /* ============================= */
    /* PHASE 5: MIPS Codegen        */
    /* ============================= */
    clock_t phase5_start = clock();

    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 5: MIPS CODE GENERATION                            │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    generateMIPS(root, argv[2]);
    printf("✓ Output written to: %s\n\n", argv[2]);

    clock_t phase5_end = clock();
    printf("  Time: %.6f seconds\n\n",
           elapsed_seconds(phase5_start, phase5_end));

    /* ============================= */
    /* TOTAL COMPILATION TIME       */
    /* ============================= */
    compiler_end = clock();

    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                 PERFORMANCE METRICS                        ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ Compilation time (total):  %.6f seconds                  ║\n",
           elapsed_seconds(compiler_start, compiler_end));
    printf("║ Execution time (compiler): %.6f seconds                  ║\n",
           elapsed_seconds(compiler_start, compiler_end));
    printf("╚════════════════════════════════════════════════════════════╝\n");

    fclose(yyin);
    return 0;
}
