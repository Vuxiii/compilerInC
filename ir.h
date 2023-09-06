#pragma once
#include <stdint.h>
#include "context.h"
#include "string.h"
struct Context;
enum IR_Opcode {
    ADD,
    SUB,
    IDIV,
    DIV,
    MUL,
    LOAD,
    MOVE,
    STORE,

};

enum IR_Opcode_Kind {
    IR_REGISTER,
    IR_DIRECT_OFFSET,
    IR_MEMORY,
    IR_RELATIVE_OFFSET,
};

struct IR_Direct_Offset {
    int64_t offset;
    int64_t address;
};

struct IR_Relative_Offset {
    int64_t base_offset;
    int64_t relative_offset;
    int64_t address;
};

struct IR_Instruction {
    enum IR_Opcode opcode;
    enum IR_Opcode_Kind first_kind;
    enum IR_Opcode_Kind second_kind;
    enum IR_Opcode_Kind third_kind;
    union {
        int64_t reg;
        int64_t memory;
        struct IR_Direct_Offset direct_memory;
        struct IR_Relative_Offset relative_memory;
    } first;
};

struct IR_Block {
    struct IR_Instruction *instructions;
    int64_t count;
    struct String *label;
};

void convert_to_ir( struct Node *root, struct Context *context );

uint64_t get_next_ir_block(struct Context *context );

struct IR_Block *get_ir_block( struct Context *context, uint64_t descriptor );
void convert_expression_to_ir( struct Context *context, uint64_t block, struct Node *expression );
