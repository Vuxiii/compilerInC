#pragma once
#include "lexer.h"
#include "token.h"
#include "context.h"
#include <stdint.h>

enum INSTRUCTION {
    INSTR_MOVE,
    INSTR_ADD,
    INSTR_SUB,
    INSTR_IDIV,
    INSTR_IMUL,
    INSTR_LEA,
    INSTR_ENTER,
    INSTR_LEAVE,
    INSTR_RET,
    INSTR_CALL,
    INSTR_PUSH,
    INSTR_POP,

};

enum REGISTER {
    REG_RAX = 0,
    REG_RBX = 1,
    REG_RCX = 2,
    REG_RDX = 3,
    REG_RSI = 4,
    REG_RDI = 5,
    REG_RBP = 6,
    REG_RSP = 7,
    REG_R8  = 8,
    REG_R9  = 9,
    REG_R10 = 10,
    REG_R11 = 11,
    REG_R12 = 12,
    REG_R13 = 13,
    REG_R14 = 14,
    REG_R15 = 15
};

enum SIZE {
    BYTES_8 = 8,
    BYTES_4 = 4,
    BYTES_2 = 2,
    BYTES_1 = 1,
};

enum REGISTER_MODE {
    IMMEDIATE,
    RELATIVE_OFFSET,
    DIRECT_OFFSET,
    REGISTER,
};

struct ASM_Instruction {
    enum INSTRUCTION      instr;
    enum SIZE             instr_size;

    enum REGISTER         from_reg;
    enum REGISTER_MODE    from_mode;

    enum REGISTER         to_reg;
    enum REGISTER_MODE    to_mode;

    int64_t               data;
    int64_t               offset;
    enum SIZE             offset_size;
};

#define APPEND_ASM_STATEMENT(context, ...) ((context)->ASM_INSTRUCTION_BUFFER[(context)->instruction_index++]) = (struct ASM_Instruction) {__VA_ARGS__}


void convert_to_ir( struct Context *context, struct Node *AST );

void gen_function_decl( struct Context *context, struct Declaration_Function *fn );

struct ASM_Instruction *get_empty_asm_instruction( struct Context *context );

void gen_statement( struct Context *context, struct Node *statement );

void gen_expression( struct Context *context, struct Node *expr );
