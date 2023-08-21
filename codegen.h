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
    REG_RAX,
    REG_RBX,
    REG_RCX,
    REG_RDX,
    REG_RSI,
    REG_RDI,
    REG_RBP,
    REG_RSP,
    REG_R8,
    REG_R9,
    REG_R10,
    REG_R11,
    REG_R12,
    REG_R13,
    REG_R14,
    REG_R15
};

enum REG_SIZE {
    BYTES_8,
    BYTES_4,
    BYTES_2,
    BYTES_1,
};

enum INSTRUCTION_MODE {
    IMMEDIATE,
    RELATIVE_OFFSET,
    DIRECT_OFFSET,
    REGISTER,
};

struct ASM_Instruction {
    enum INSTRUCTION      instr;
    enum INSTRUCTION_MODE mode;
    enum REGISTER         from_reg;
    enum REG_SIZE         from_size;
    enum REGISTER         to_reg;
    enum REG_SIZE         to_size;
    int64_t               data;
};


void convert_to_ir( struct Context *context, struct Node *AST );

void gen_function_decl( struct Context *context, struct Declaration_Function *fn );

struct ASM_Instruction *get_empty_asm_instruction( struct Context *context );

void gen_statement( struct Context *context, struct Node *statement );

void gen_expression( struct Context *context, struct Node *expr );

void append_asm_statement( struct Context *context, struct ASM_Instruction *instruction );
