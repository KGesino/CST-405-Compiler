# CST-405-Compiler

**CST-405: Compiler Design**  
A complete compiler implementation for a C-style language that translates source programs into **MIPS assembly**.  
This compiler supports lexical analysis, parsing, semantic analysis, three-address code (TAC) generation, basic optimizations, and MIPS code output.

---

## Overview

This project builds a fully functional compiler from scratch using:

- **Flex** for lexical scanning
- **Bison** for parsing
- Hand-written C for AST construction, semantic analysis, code generation, and optimization

The compiler processes source `.c` files and produces MIPS assembly (`.s`) that can be executed in SPIM/QtSPIM.

---

## Language Features

The language supports:

### **Data Types**
- `int`  
- `float`  
- `bool` (boolean)  
- `char`  
- 1D and 2D arrays

### **Statements**
- Variable declarations (`int x;`)  
- Array declarations (`int arr[10];`)  
- Assignment (`x = 5;`, `arr[i] = 10;`)  
- `if / else` statements  
- `while` loops  
- Function declarations and calls  
- `return` statements  
- I/O: `print(expr)`, `write(expr)`, `writeln;`
- Swap statement: `swap(x, y);`
- Parallel race construct

### **Expressions**
- Arithmetic: `+`, `-`, `*`, `/`
- Relational: `>`, `<`, `>=`, `<=`, `==`, `!=`
- Boolean logic: `&&`, `||`, `!`
- Array indexing (`arr[i]`, `mat[r][c]`)
- Function calls inside expressions

---

## Compiler Phases

1. **Lexical Analysis (Scanner)**
   - Tokenizes source into identifiers, literals, operators, and keywords.

2. **Syntax Analysis (Parser)**
   - Bison builds a parse tree based on defined grammar.

3. **AST Construction**
   - Parser builds an Abstract Syntax Tree (AST) for semantic analysis.

4. **Semantic Analysis**
   - Type checking  
   - Symbol table population (variables, arrays, functions)  
   - Scope management for nested blocks

5. **TAC Generation**
   - AST → Three-Address Code (simplified IR)

6. **Optimization**
   - Constant folding and propagation  
   - Dead code elimination  
   - Common subexpression elimination

7. **Target Code Generation**
   - MIPS assembly

---

## Project Structure
```
CST-405-Compiler/
├── Makefile
├── README.md
├── parser.y # Bison grammar
├── scanner.l # Flex lexer
├── ast.c / ast.h # AST and constructors
├── symtab.c / symtab.h # Symbol table and scope
├── codegen.c # Code generation (TAC and MIPS)
├── tac.c / tac.h # TAC and optimizations
├── main.c # Entry point
├── test1.c
├── test2.c
├── test4.c
├── output.s # Example MIPS output
└── tests/ # Optional test suite
```

## Installation and Build

### **Prerequisites**
Install on Linux/Ubuntu:
```bash
sudo apt update
sudo apt install build-essential flex bison spim
```
Clone & Build
```bash
git clone https://github.com/KGesino/CST-405-Compiler
cd CST-405-Compiler
make
```
Clean Build Files
```bash
make clean
```
## Using the Compiler
Compile Source to MIPS
```bash
./minicompiler <source_file.c> <output_file.s>
```
Example:
```bash
./minicompiler test4.c output.s
```
Run in SPIM or QtSPIM
```bash
spim -file output.s
```
## Performance Metrics
1. Compilation Time
Measure how long the compiler takes:
```bash
time ./minicompiler test4.c output.s
```
Record:
- real (total elapsed time)
- user (CPU time in user mode)
- sys (system calls time)

2. Execution Time
Measure the execution time of the compiled MIPS:
```bash
time spim -file output.s
```
Alternatively, add timer syscalls in MIPS (if desired) for finer measurement.

### Example Source Usage
Example input:
```c
int main() {
    int x;
    x = 5;
    print(x);
    return 0;
}
```
Produces MIPS that:
- sets up stack frame
- loads/stores variables
- prints values using SPIM syscalls

## Symbol Table & Scope
- Global scope includes functions and global variables
- Each function has its own scope
- Nested blocks (if, while) open new scopes
### Symbol entries include:
- name
- type
- kind (var, param, function)
- stack offset
Scope is managed by using:
- enterScope()
- exitScope()

## Troubleshooting
### “Parser conflicts”
Use %prec declarations and fix grammar rules.

### “Undefined reference” errors
Ensure function prototypes in .h match definitions in .c.

### SPIM crashes
Check stack pointer and frame setup:
```asm
addi $sp, $sp, -8
sw $ra, 4($sp)
sw $fp, 0($sp)
move $fp, $sp
```
### Future Enhancements
- Support for loops
- More built-in functions and I/O
- Float arithmetic improvements
- Register allocation passes
- Better error recovery in parsing

## References
- Aho, Sethi & Ullman – Dragon Book (Compilers)
- Flex & Bison manuals
- MIPS assembly language reference

## Contributors
Matthew Edelson & Kai Gesino
