#include "codegen.h"
#include "context.h"
#include "token.h"
#include "lexer.h"

#include <stdlib.h>


void convert_to_ir( struct Context *context, struct Node *AST) {
    switch (AST->node_type) {
        case NODE_FN_DECLARATION: {

            struct Declaration_Function *fn = &AST->contents.function_declaration;

            gen_function_decl(context, fn);

        } break;
        default: exit(1);
    }
}


void gen_function_decl( struct Context *context, struct Declaration_Function *fn) {

    if (fn->body) {
        gen_statement( context, (struct Node *)fn->body);
    }

}

void gen_statement( struct Context *context, struct Node *statement ) {
  
    switch (statement->node_type) {
        case NODE_COMPOUND_STATEMENT: {
            struct Node *left = statement->contents.compound_statement.left;
            struct Node *right = statement->contents.compound_statement.right;
            gen_statement( context, left );
            gen_statement( context, right );
        } break;
        case NODE_ASSIGNMENT: {
            // struct Node *lhs = statement->contents.assignment.lhs;
            struct Node *rhs = statement->contents.assignment.rhs;
            gen_expression(context, rhs);
        } break;
        case NODE_SCOPE: {
            struct Node *body = statement->contents.scope.expression;
            gen_statement( context, body );
        } break;
        default: {

        } break;
    }

}

void gen_expression( struct Context *context, struct Node *expr ) {
    switch (expr->node_type) {
        case TOKEN_NUMBER_D: {
            APPEND_ASM_STATEMENT(context, 
                                 .instr = INSTR_PUSH,
                                 .instr_size = BYTES_8,
                                 .from_mode = IMMEDIATE,
                                 .data = expr->contents.decimal_number.inum
                                 );
        } break;
        case NODE_BINARY_OPERATION: {
            gen_expression( context, expr->contents.binary_operation.left );
            gen_expression( context, expr->contents.binary_operation.right );

            
            APPEND_ASM_STATEMENT(context, 
                                 .instr = INSTR_POP,
                                 .instr_size = BYTES_8,
                                 .from_reg = REG_RAX,
                                 .from_mode = REGISTER);
            APPEND_ASM_STATEMENT(context, 
                                 .instr = INSTR_POP,
                                 .instr_size = BYTES_8,
                                 .from_reg = REG_RBX,
                                 .from_mode = REGISTER);
            switch (expr->contents.binary_operation.op) {
                case TOKEN_PLUS: {
                    APPEND_ASM_STATEMENT(context, 
                                 .instr = INSTR_ADD,
                                 .instr_size = BYTES_8,
                                 .from_reg = REG_RBX,
                                 .from_mode = REGISTER,
                                 .to_reg = REG_RAX,
                                 .to_mode = REGISTER);
                    APPEND_ASM_STATEMENT(context, 
                                 .instr = INSTR_PUSH,
                                 .instr_size = BYTES_8,
                                 .from_reg = REG_RAX,
                                 .from_mode = REGISTER);
                } break;
                case TOKEN_MINUS: {
                    APPEND_ASM_STATEMENT(context, 
                                 .instr = INSTR_SUB,
                                 .instr_size = BYTES_8,
                                 .from_reg = REG_RBX,
                                 .from_mode = REGISTER,
                                 .to_reg = REG_RAX,
                                 .to_mode = REGISTER);
                    APPEND_ASM_STATEMENT(context, 
                                 .instr = INSTR_PUSH,
                                 .instr_size = BYTES_8,
                                 .from_reg = REG_RAX,
                                 .from_mode = REGISTER);
                } break;
                case TOKEN_TIMES: {
                } break;
                case TOKEN_DIV: {
                } break;
                default: {
                    // Insert error here
                } break;
            }
                    } break;
        default: {

        } break;
    }
}

struct ASM_Instruction *get_empty_asm_instruction( struct Context *context ) {
    if (context->instruction_index == context->instruction_size) {
        // For now just realloc....

        context->ASM_INSTRUCTION_BUFFER = realloc(context->ASM_INSTRUCTION_BUFFER, context->instruction_size * 2);
        if (context->ASM_INSTRUCTION_BUFFER == NULL) {
            print_string(String( .str = "Out of memory\n", .length = 14));
            _Exit(3);
        }
        context->instruction_size *= 2;
    }
    return &context->ASM_INSTRUCTION_BUFFER[context->instruction_index++];
}

