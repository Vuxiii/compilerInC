//
// Created by William Juhl on 05/09/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <printf.h>
#include "ir.h"
#include "context.h"
#include "lexer.h"

void convert_to_ir( struct Node *AST, struct Context *context ) {
    switch (AST->node_type) {
        case NODE_FN_DECLARATION: {

            struct Declaration_Function *fn = &AST->contents.function_declaration;

            uint64_t block_descriptor = get_next_ir_block(context);

            struct IR_Block *block = get_ir_block(context, block_descriptor);
            block->label = fn->function_name;
            struct Node *current = fn->body;

            int run = 1;
            while (run) {
                switch (current->node_type) {
                    case NODE_ASSIGNMENT: {
                        struct Assignment *assignment = &current->contents.assignment;


                    } break;
                    default: run = 0;
                }
            }

        } break;
        default: exit(1);
    }
}

void convert_expression_to_ir( struct Context *context, uint64_t block, struct Node *expression ) {
    switch (expression->node_type) {
        case NODE_BINARY_OPERATION: {
            // Three cases
            // [1] Left is literal & right is binary
            // [2] Left is binary  & right is literal
            // [3] Left is literal & right is literal

            struct Binary_Operation *binop = &expression->contents.binary_operation;

            if (binop->left->node_type != NODE_BINARY_OPERATION
            && binop->right->node_type == NODE_BINARY_OPERATION) {
                // Case [1]
            } else if (binop->left->node_type == NODE_BINARY_OPERATION
                    && binop->right->node_type != NODE_BINARY_OPERATION) {
                // Case [2]

            } else {
                // Case [3]
            }

        } break;
        default: {
            printf("Unimplemented token %d\n", expression->node_type);
            exit(1);
        }
    }
}

struct IR_Block *get_ir_block( struct Context *context, uint64_t descriptor ) {
    return &context->ir_blocks[descriptor];
}

uint64_t get_next_ir_block(struct Context *context ) {
    if (context->ir_blocks_count == context->ir_blocks_size) {
        context->ir_blocks = realloc(context->ir_blocks, sizeof(struct IR_Block) * context->ir_blocks_size * 2);
        if (context->ir_blocks == NULL) {
            printf("Not enough memory to realloc ir blocks\n");
            exit(1);
        }
        context->ir_blocks_size *= 2;
    }
    return context->ir_blocks_count++;
}