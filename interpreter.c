#include "interpreter.h"
#include "error.h"
#include "string.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

void interpret( struct Runtime *runtime, struct Node *node ) {
    
    switch (node->node_type) {

    case TOKEN_EOP: {
        return;
    } break;
    case NODE_COMPOUND_STATEMENT: {
        
    } break;
    case NODE_FN_DECLARATION: {
        struct Declaration_Function fn = node->contents.function_declaration;
        if (fn.body) {
            interpret_statement(runtime, fn.body); 
        }
    } break;
    case NODE_FN_CALL:
    case NODE_SYMBOL:
    case NODE_FIELD_ACCESS:
    case NODE_ARRAY_ACCESS:
    case NODE_VARIABLE_DECLARATION:
    case NODE_ARRAY_DECLARATION:
    case NODE_TYPE_DECLARATION:
    case NODE_STRUCT_DECLARATION:
    case NODE_ASSIGNMENT:
    case NODE_ADDRESS_OF:
    case NODE_DEREF:
    case NODE_BINARY_OPERATION:
    case NODE_PARAMETER_LIST:
    case NODE_ARGUMENT_LIST:
    case NODE_FOR:
    case NODE_EACH:
    case NODE_SCOPE:
    
    default: {
        print_string( String( .str = "Top Level Interpreter Unhandled case.\n", .length = 38));
        printf("%d\n", node->node_type);
        exit(EXIT_FAILURE);
    } break;
    }
}

void interpret_statement( struct Runtime *runtime, struct Node *some_statement ) {
    switch (some_statement->node_type) {
        case NODE_COMPOUND_STATEMENT: {
            struct Compound_Statement this = some_statement->contents.compound_statement;
            interpret_statement( runtime, this.left);
            interpret_statement( runtime, this.right);
        } break;
        case NODE_VARIABLE_DECLARATION: {
            struct Declaration_Variable this = some_statement->contents.variable_declaration;
            PUSHQ(runtime, 1);
            POPQ(runtime, RBX(runtime));            
        } break;
        case NODE_ASSIGNMENT: {
            struct Assignment this = some_statement->contents.assignment;
            struct Number_D value = this.rhs->contents.decimal_number;
            RAX(runtime) = value.inum;
        } break;
        case NODE_SCOPE: {
            struct Expression this = some_statement->contents.scope; 
            interpret_statement(runtime, this.expression);
        } break;
        default: {
            print_string( String( .str = "Unhandled statement case.\n", .length = 26));
            printf("%d\n", some_statement->node_type);
            exit(EXIT_FAILURE);
        } break;
    }
}
