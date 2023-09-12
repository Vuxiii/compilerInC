#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "string.h"
#include "token.h"
#include <stdlib.h>
#include <unistd.h>


extern struct Node *NODE_BUFFER;
static unsigned int NODE_BUFFER_INDEX = 0;
static unsigned int NODE_BUFFER_SIZE = NODE_BUFFER_INITIAL_SIZE;
struct Node *parse(struct Context *context) {
    next_token(context);
    struct Node *top_level = NULL;
    while (peek_token(context)->token_type != TOKEN_EOP) {
        if (top_level == NULL) {
            top_level = parse_toplevel_statement(context);
            continue;
        }

        // Compound toplevel statements
        struct Node *compound = get_empty_node();

        struct Node *rest = parse_toplevel_statement(context);

        compound->node_type = NODE_COMPOUND_STATEMENT;
        compound->left  = top_level->left;
        compound->right = rest->right;
        compound->line  = top_level->line;

        compound->contents.compound_statement = (struct Compound_Statement) {
            .left = top_level,
            .right = rest
        };
        top_level = compound;
    }
    return top_level;
}

struct Node *parse_toplevel_statement( struct Context *context ) {
       
    next_token(context);
    switch (current_token(context)->token_type) {
        case TOKEN_FN: {
            return parse_function_declaration(context);
        } break;
        default: {
            emit_error(context, 
                        .error_string = String( 
                            .str = "Unexpected top level Token.\n",
                            .length = 28),
                    .token = current_token(context) );
            return NULL;
        } break;

    }
}

struct Node *parse_function_declaration( struct Context *context ) {
    // Current: TOKEN_FN

    next_token(context);
    assert_token_type(context, .expected_token = TOKEN_IDENTIFIER, .which = CURRENT,
                             .error_string = String(
                              .str = "Unexpected Token. Expected Function Name\n", 
                              .length = 40));
  
    // Current: TOKEN_IDENTIFIER
    struct String *func_name = current_token(context)->data.str;

    next_token(context);
    // Current: TOKEN_LPAREN
    assert_token_type(context, .expected_token = TOKEN_LPAREN, .which = CURRENT,
                             .error_string = String( 
                                 .str = "Unexpected Token while parsing function declaration. Expected '('\n",
                                 .length = 66));
    
    struct Node *parameters = parse_parameter_list(context);

    assert_token_type(context, .expected_token = TOKEN_RPAREN, .which = CURRENT,
                             .error_string = String( 
                                 .str = "Unexpected Token while parsing function declaration. Expected ')'\n",
                                 .length = 66));
    
    struct Node *out = get_empty_node();

    struct Node *body = parse_statement(context);

    out->contents.function_declaration = (struct Declaration_Function){
        .function_name = func_name, 
        .parameters = parameters, // NULL IF ZERO PARAMETERS
        .body = body // NULL IF NO BODY
    };
    out->node_type = NODE_FN_DECLARATION;
    return out;
}

struct Node *parse_statement( struct Context *context ) {
    struct Node *some_statement = NULL;
    switch (peek_token(context)->token_type) {
        case TOKEN_LCURLY: {
            struct Node *scope = get_empty_node();
            next_token(context);
            scope->left = current_token(context)->left;
            scope->line = current_token(context)->line;
            do {
                if (some_statement) {
                    struct Node *compound = get_empty_node();
                    struct Node *rhs_statement = parse_statement(context);

                    compound->node_type = NODE_COMPOUND_STATEMENT;
                    compound->left = some_statement->left;
                    compound->right = rhs_statement->right;
                    compound->line = some_statement->line;

                    compound->contents.compound_statement = (struct Compound_Statement) {
                        .left = some_statement,
                        .right = rhs_statement
                    };
                    some_statement = compound;
                } else {
                    some_statement = parse_statement(context);
                }
            } while (peek_token(context)->token_type != TOKEN_RCURLY);
            next_token(context);

            scope->right = current_token(context)->right;
            scope->node_type = NODE_SCOPE;
            scope->contents.scope.expression = some_statement;
            some_statement = scope;
        } break;
        case TOKEN_LET: {
            next_token(context);
            some_statement = parse_declaration(context);
            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_SEMICOLON, .error_string = String( 
                .str = "Unexpected Token at the end of a 'let' statement. Missing ';'\n", 
                .length = 62 ));
            next_token(context);
        } break;
        case TOKEN_IDENTIFIER: {
            next_token(context);
            some_statement = parse_symbol(context);
            // some_statement can either be a function call or an assignment.
            // This is determined by the peek token.
            // case TOKEN_EQ        -> Assignment
            // case TOKEN_SEMICOLON -> FunctionCall

            switch (peek_token(context)->token_type) {
                case TOKEN_EQ: {
                    next_token(context);
                    // Current: TOKEN_EQ
                    struct Node *assignment = get_empty_node();
                    struct Node *expression = parse_expression(context);
                    
                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_SEMICOLON, .error_string = String( 
                        .str = "Unexpected Token at the end of an assignment. Expected ';'\n",
                        .length = 59 ));
                    next_token(context);
                    // Current: TOKEN_SEMICOLON

                    assignment->left = some_statement->left;
                    assignment->right = expression->right;
                    assignment->line = some_statement->line;
                    assignment->node_type = NODE_ASSIGNMENT;
                    
                    assignment->contents.assignment = (struct Assignment) {
                        .lhs = some_statement,
                        .rhs = expression
                    };

                    some_statement = assignment;
                } break;
                case TOKEN_LPAREN: {
                    // Must be a function call?
                    next_token(context);
                    
                    struct Node *function_call = get_empty_node();

                    struct Node *arguments = parse_argument_list(context);

                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_RPAREN, .error_string = String(
                        .str = "Unexpected Token while parsing a function call. Expected ')'\n",
                        .length = 61));
                    
                    next_token(context);
                    // Current: TOKEN_RPAREN

                    // TODO: Future Proof
                    // At this point it might actually return a reference to another object. So we could also see a TOKEN_DOT here

                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_SEMICOLON, .error_string = String(
                        .str = "Unexpected Token while parsing a function call. Expected ';'\n",
                        .length = 61));
                    next_token(context);
                    // Current: TOKEN_SEMICOLON

                    function_call->left = some_statement->left;
                    function_call->right = current_token(context)->right;
                    function_call->line = some_statement->line;
                    function_call->node_type = NODE_FN_CALL;

                    function_call->contents.function_call = (struct Function_Call) {
                        .lhs = some_statement,
                        .arguments = arguments // NULL IF ZERO ARGS
                    };
                    some_statement = function_call;
                } break;
                default: {
                    emit_error(context, .token = peek_token(context), .error_string = String(
                        .str = "Unexpected Token at the end of a statement.\n Expected either a ';' to indicate the end of the statement,\n              or a '=' to declare an assignment\n",
                        .length = 153 ) );
                } break;
            }

        } break;
        case TOKEN_FOR: {
            next_token(context);
            struct Token for_token = *current_token(context);
            struct Node *for_node = get_empty_node();

            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_LPAREN, .error_string = String( 
                .str = "Unexpected Token while trying to parse a for loop. Expected '('\n",
                .length = 64)); 
            next_token(context);
            
            struct Node *init = NULL;
            
            if (peek_token(context)->token_type != TOKEN_SEMICOLON) {
                init = parse_statement(context);
            }
            
            assert_token_type(context, .which = CURRENT, .expected_token = TOKEN_SEMICOLON, .error_string = String(
                .str = "Unexpected Token while trying to parse a for loop. Expected ';' before the guard\n",
                .length = 81));

            struct Node *guard = parse_expression(context);

            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_SEMICOLON, .error_string = String(
                .str = "Unexpected Token while trying to parse a for loop. Expected ';' after the guard\n",
                .length = 80));
            next_token(context);

            struct Node *advance = NULL;
            if (peek_token(context)->token_type != TOKEN_RPAREN) {
                advance = parse_statement(context);
            }

            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_RPAREN, .error_string = String(
                .str = "Unexpected Token while trying to parse a for loop. Expected a closing ')'\n",
                .length = 74 ));
            next_token(context);

            struct Node *body = parse_statement(context); 

            for_node->contents.for_loop = (struct For_Loop) {
                .init = init,       // NULLABLE
                .guard = guard,
                .advance = advance, // NULLABLE
                .body = body,
            };

            for_node->left = for_token.left;
            for_node->right = body->right;
            for_node->line = for_token.line;

            for_node->node_type = NODE_FOR;
            some_statement = for_node;
        } break;
        case TOKEN_WHILE: {
            next_token(context);
            struct Node *while_node = get_empty_node();
            while_node->left = current_token(context)->left;
            while_node->line = current_token(context)->line;
            
            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_LPAREN, .error_string = String( 
                .str = "Unexpected Token while trying to parse a while loop. Missing '('\n", 
                .length = 65));

            struct Node *guard = parse_expression(context);
            struct Node *body = parse_statement(context);

            while_node->right = body->right;
            while_node->node_type = NODE_FOR;
            while_node->contents.for_loop = (struct For_Loop) {
                .init = NULL,
                .advance = NULL,
                .body = body,
                .guard = guard,
            };  
            some_statement = while_node;
        } break;
        case TOKEN_EACH: {
            next_token(context);
            struct Node *each_node = get_empty_node();
            each_node->left = current_token(context)->left;
            each_node->line = current_token(context)->line;

            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_LPAREN, .error_string = String(
                .str = "Unexpected Token while trying to parse an Each loop. Expected '('\n",
                .length = 66 ));
            next_token(context);

            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_IDENTIFIER, .error_string = String(
                .str = "Unexpected Token while trying to parse an Each loop. Expected an identifier for the iterator symbol\n",
                .length = 100 ));
            next_token(context);
            struct String *symbol = current_token(context)->data.str;

            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_COLON, .error_string = String(
                .str = "Unexpected Token while trying to parse an Each loop. Expected ':'\n",
                .length = 66 ));

            next_token(context);
            // Current: TOKEN_COLON

            next_token(context);

            struct Node *container = parse_symbol(context);

            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_RPAREN, .error_string = String(
                .str = "Unexpected Token while trying to parse an Each loop. Expected closing ')'\n",
                .length = 74 )); 

            next_token(context);

            struct Node *body = parse_statement(context);

            each_node->contents.each_loop = (struct Each_Loop) {
                .body = body,
                .container = container,
                .iterator_symbol = symbol,
            };

            each_node->node_type = NODE_EACH;
            some_statement = each_node;
        } break;
        default: {
            return NULL; // This indicates that there are no more statements
        }
    }
    return some_statement;
}

struct Node *parse_symbol( struct Context *context ) {
    // [1] IDENTIFIER
    // [2] IDENTIFIER . parse_symbol
    // [3] IDENTIFIER [ expression ]
    // [4] IDENTIFIER [ expression ] . parse_symbol
    
    assert_token_type(context, .which = CURRENT, .expected_token = TOKEN_IDENTIFIER, .error_string = String(
        .str = "Unexpected Token while trying to parse a symbol expression. Expected an identifier\n",
        .length = 83 ));

    // Current: IDENTIFIER
    struct String *lhs_identifier = current_token(context)->data.str;
    if (peek_token(context)->token_type != TOKEN_DOT &&
        peek_token(context)->token_type != TOKEN_LBRACKET) {
        
        struct Node *sym = get_empty_node();
        sym->contents.symbol.str = lhs_identifier;
        sym->node_type = NODE_SYMBOL;
        return sym;
    }
    
    if ( peek_token(context)->token_type == TOKEN_DOT ) {
        next_token(context);
        // Current: '.'
        next_token(context);
        struct Node *field_access = get_empty_node();
        struct Node *lhs = get_empty_node();
        struct Node *rhs = parse_symbol( context );
        lhs->contents.symbol.str = lhs_identifier;
        field_access->contents.field_access = (struct Field_Access) {
            .lhs = lhs,
            .rhs = rhs
        };
        field_access->node_type = NODE_FIELD_ACCESS;
        return field_access;
    }
    
    if (peek_token(context)->token_type == TOKEN_LBRACKET) {
        next_token(context);
        // Current: '['

        struct Node *array_access = get_empty_node();
        struct Node *expression = parse_expression(context);
        array_access->contents.array_access = (struct Array_Access) {
            .lhs = lhs_identifier,
            .index = expression
        };

        assert_token_type(context, .which = PEEK, .expected_token = TOKEN_RBRACKET, .error_string = String(
                                    .str = "Unexpected Token. Expected ']'\n",
                                    .length = 31 ));
        
        next_token(context);
        // Current: ']'
        
        if (peek_token(context)->token_type != TOKEN_DOT) {
            array_access->node_type = NODE_ARRAY_ACCESS;
            return array_access;
        } else {
            next_token(context);
            // Current: TOKEN_DOT
            next_token(context);

            struct Node *field_access = get_empty_node();
            struct Node *rhs = parse_symbol(context);
            field_access->contents.field_access = (struct Field_Access) {
                .lhs = array_access,
                .rhs = rhs
            };
            field_access->node_type = NODE_FIELD_ACCESS;
            return field_access;
        }
        

    }

    emit_error(context, .token = peek_token(context), .error_string = String(
                .str = "Unexpected Token. Expected one of [ '.' , '[' ]\n",
                .length = 48));

    // We never reach here.
    return NULL;
}

struct Node *parse_declaration( struct Context *context ) {
    // [1] LET IDENTIFIER : IDENTIFIER
    // [2] LET IDENTIFIER : IDENTIFIER = expression
    // [3] LET IDENTIFIER : [ NUMBER ] IDENTIFIER
    // [4] LET IDENTIFIER :: IDENTIFIER
    // [5] LET IDENTIFIER :: STRUCT { parameter_list }
    
    // Current: LET
    struct Token let_token = *current_token(context);
    
    next_token(context);

    assert_token_type(context, .which = CURRENT, .expected_token = TOKEN_IDENTIFIER,
                             .error_string = String( 
                                 .str = "Unexpected Token while trying to parse a let declaration. Expected an Identifier\n",
                                 .length = 81));
    // Current: TOKEN_IDENTIFIER
    
    struct Token lhs_identifier = *current_token(context);
    next_token(context);

    switch (current_token(context)->token_type) {
        case TOKEN_COLON: {
            // Current: TOKEN_COLON
            next_token(context);
            switch (current_token(context)->token_type) {
                case TOKEN_IDENTIFIER: {
                    // Current: TOKEN_IDENTIFIER
                    struct String *type = current_token(context)->data.str;

                    switch (peek_token(context)->token_type) {
                        case TOKEN_EQ: {
                            // [2] LET IDENTIFIER : IDENTIFIER = expression

                            next_token(context);
                            // Current: TOKEN_EQ

                            struct Node *compound = get_empty_node();
                            struct Node *lhs = get_empty_node();
                            struct Node *decl = get_empty_node();
                            struct Node *assignment = get_empty_node();
                            struct Node *rhs = parse_expression( context );
    
                            // Fill decl
                            decl->contents.variable_declaration = (struct Declaration_Variable){
                                .variable_name = lhs_identifier.data.str,
                                .variable_type = type
                            };
                            decl->line = let_token.line;
                            decl->left = let_token.left;
                            decl->right = rhs->right;
                            decl->node_type = NODE_VARIABLE_DECLARATION;
                            lhs->contents.symbol.str = lhs_identifier.data.str;
                            assignment->contents.assignment = (struct Assignment){
                                .lhs = lhs,
                                .rhs = rhs
                            };
                            assignment->line = let_token.line;
                            assignment->left = let_token.left;
                            assignment->right = rhs->right;
                            assignment->node_type = NODE_ASSIGNMENT;
                            
                            compound->contents.compound_statement.left = decl;
                            compound->contents.compound_statement.right = assignment;
                            compound->left = decl->left;
                            compound->right = assignment->right;
                            compound->line = decl->line;
                            compound->node_type = NODE_COMPOUND_STATEMENT;
                            return compound;
                        } break;
                        default: {
                           // [1] LET IDENTIFIER : IDENTIFIER
                            struct Node *decl = get_empty_node();
                            decl->contents.variable_declaration = (struct Declaration_Variable){
                                .variable_name = lhs_identifier.data.str,
                                .variable_type = type
                            };
                            decl->line = let_token.line;
                            decl->left = let_token.left;
                            decl->right = current_token(context)->right;
                            decl->node_type = NODE_VARIABLE_DECLARATION;
                            return decl;
                        } break;
                    }

                } break;
                case TOKEN_LBRACKET: {
                    // [3] LET IDENTIFIER : [ NUMBER ] IDENTIFIER
                    // Current: TOKEN_LBRACKET
                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_NUMBER_D, .error_string = String( 
                                .str = "Unexpected Token while parsing a let array declaration. The length of the array MUST be literal number.\n", 
                                .length = 104 ));
                    next_token(context);
                    // Current: TOKEN_NUMBER_D

                    struct Token length = *current_token(context);
                    
                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_RBRACKET, .error_string = String(
                                .str = "Unexpected Token while parsing a let array declaration. Expected a ']'\n",
                                .length = 71));
                    next_token(context);
                    // Current: TOKEN_RBRACKET

                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_IDENTIFIER, .error_string = String(
                                .str = "Unexpected Token while parsing a let array declaration. Expected a Type\n",
                                .length = 72 ));
                    next_token(context);
                    // Current: TOKEN_IDENTIFIER

                    struct Token *type = current_token(context);

                    struct Node *array_decl = get_empty_node();
                    array_decl->contents.array_declaration = (struct Declaration_Array){
                        .array_name = lhs_identifier.data.str,
                        .array_type = type->data.str,
                        .length = length.data.inum
                    };
                    array_decl->left = lhs_identifier.left;
                    array_decl->right = length.right;
                    array_decl->line = lhs_identifier.line;
                    array_decl->node_type = NODE_ARRAY_DECLARATION;
                    return array_decl;
                } break;
                default: {
                    emit_error(context, .token = current_token(context), .error_string = String(
                                .str = "Unexpected Token while parsing a let declaration. Expected either an Identifier or '['\n",
                                .length = 87 ) );
                } break;
            }
        } break;
        case TOKEN_DOUBLE_COLON: {
             // [4] LET IDENTIFIER :: IDENTIFIER
             // [5] LET IDENTIFIER :: STRUCT { parameter_list }
             next_token(context);
             switch (current_token(context)->token_type) {
                case TOKEN_IDENTIFIER: {                     
                    // [4] LET IDENTIFIER :: IDENTIFIER
                    // TODO: IMPLEMENT ME
                }
                case TOKEN_STRUCT: { 
                    // [5] LET IDENTIFIER :: STRUCT { parameter_list }
                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_LCURLY, 
                            .error_string = String(
                                .str = "Unexpected Token while trying to parse a struct declaration. Expected '{'\n",
                                .length = 74 ));
                    next_token(context);

                    struct Node *struct_declaration = get_empty_node();

                    struct Node *parameter_list = parse_parameter_list(context);

                    assert_token_type(context, .which = CURRENT, .expected_token = TOKEN_RCURLY,
                            .error_string = String(
                                .str = "Unexpected Token while trying to parse a struct declaration. Expected '}'\n",
                                .length = 74 ));

                    struct_declaration->contents.struct_declaration = (struct Declaration_Struct) {
                        .struct_name = lhs_identifier.data.str,
                        .fields = parameter_list,
                        .count = -1
                    };

                    struct_declaration->node_type = NODE_STRUCT_DECLARATION;
                    struct_declaration->left = lhs_identifier.left;
                    struct_declaration->right = current_token(context)->right;
                    struct_declaration->line = lhs_identifier.line;
                    return struct_declaration;
                }
                default: {
                    emit_error(context, .token = current_token(context), .error_string = String(
                                .str = "Unexpected Token. Expected either an Identifier' or 'struct'\n",
                                .length = 61 ));
                }

             }

        } break;
        default: {
            emit_error(context, .token = current_token(context),
                            .error_string = String(
                                .str = "Unexpected Token in a let declaration. Expected either a ':' to declare a variable, or a '::' to declare a type\n",
                                .length = 112));
        } break;
    }

    return NULL;
}

struct Node *parse_parameter_list( struct Context *context ) {
    next_token(context);
    if (current_token(context)->token_type == TOKEN_IDENTIFIER) {
        struct Node *parameter = parse_parameter(context);
        if (current_token(context)->token_type == TOKEN_COMMA) {
            struct Node *parameter_list = get_empty_node();
            struct Node *rest_parameter = parse_parameter_list(context);
            
            parameter_list->contents.parameter_list = (struct Parameter_List) {
                .parameter = parameter,
                .next = rest_parameter
            };

            parameter_list->left = parameter->left;
            parameter_list->right = rest_parameter->right;
            parameter_list->line = parameter->line;


            parameter_list->node_type = NODE_PARAMETER_LIST;
            return parameter_list;
        }
        return parameter;
    }

    return NULL;
}

struct Node *parse_argument_list( struct Context *context ) {
    // expression
    // expression TOKEN_COMMA argument_list

    if (peek_token(context)->token_type == TOKEN_RPAREN) {
        return NULL; // TODO: Is this the correct place to put this. Maybe hoist it to the caller, to make this function more generic. 
    }

    struct Node *argument = parse_expression(context);
    if (peek_token(context)->token_type == TOKEN_COMMA) {
        next_token(context);
        // Current: TOKEN_COMMA

        struct Node *argument_list = get_empty_node();
        struct Node *argument_rest = parse_argument_list(context);

        argument_list->left = argument->left;
        argument_list->line = argument->line;
        argument_list->right = argument_rest->right;

        argument_list->contents.argument_list = (struct Argument_List) {
            .argument = argument,
            .next = argument_rest
        };

        argument_list->node_type = NODE_ARGUMENT_LIST;
        argument = argument_list;
    }

    return argument;
}

struct Node *parse_parameter( struct Context *context ) {
    // IDENTIFIER : IDENTIFIER 
    
    // Current: TOKEN_IDENTIFIER
    
    struct Token lhs = *current_token(context);

    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_COLON, .error_string = String(
                .str = "Unexpected Token trying to parse a Parameter. Expected a ':'\n",
                .length = 61 ));
    next_token(context); 

    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_IDENTIFIER, .error_string = String(
                .str = "Unexpected Token tyring to parse a Parameter. Expected a type\n",
                .length = 62 ));
    
    next_token(context);
    
    struct Token rhs = *current_token(context);

    next_token(context);

    struct Node *parameter = get_empty_node();
        
    parameter->contents.parameter = (struct Declaration_Variable) {
        .variable_name = lhs.data.str,
        .variable_type = rhs.data.str
    };

    parameter->left = lhs.left;
    parameter->right = current_token(context)->right;
    parameter->line = lhs.line;
    parameter->node_type = NODE_VARIABLE_DECLARATION;
    return parameter;
}


struct Node *parse_expression( struct Context *context ) {
    // We can have:
    // [1] comparison_expression
    // [2] comparison_expression && comparison_expression
    // [3] comparison_expression || comparison_expression
    struct Node *lhs = parse_comparison_expression(context);

    while (peek_token(context)->token_type == TOKEN_DOUBLE_AND || 
           peek_token(context)->token_type == TOKEN_DOUBLE_OR)  {
        
        next_token(context);

        enum TOKEN operator = current_token(context)->token_type;
        struct Node *binary_operation = get_empty_node();
        struct Node *rhs = parse_expression(context);

        binary_operation->left = lhs->left;
        binary_operation->right = rhs->right;
        binary_operation->line = lhs->line;
        binary_operation->node_type = NODE_BINARY_OPERATION;
        binary_operation->contents.binary_operation = (struct Binary_Operation) {
            .left = lhs,
            .right = rhs,
            .op = operator
        };
        lhs = binary_operation;
    }

    return lhs;
}

struct Node *parse_comparison_expression( struct Context *context ) {
    // We can have:
    // [1] parse_sub
    // [2] parse_sub == parse_sub
    // [3] parse_sub != parse_sub
    // [4] parse_sub <= parse_sub
    // [5] parse_sub >= parse_sub
    // [6] parse_sub <  parse_sub
    // [7] parse_sub >  parse_sub
    struct Node *lhs = parse_sum(context);

    while (peek_token(context)->token_type == TOKEN_DOUBLE_EQ || 
           peek_token(context)->token_type == TOKEN_NOT_EQ ||
           peek_token(context)->token_type == TOKEN_LESS_EQ ||
           peek_token(context)->token_type == TOKEN_GREATER_EQ ||
           peek_token(context)->token_type == TOKEN_LESS ||
           peek_token(context)->token_type == TOKEN_GREATER)  {
        
        next_token(context);

        enum TOKEN operator = current_token(context)->token_type;
        struct Node *binary_operation = get_empty_node();
        struct Node *rhs = parse_comparison_expression(context);

        binary_operation->left = lhs->left;
        binary_operation->right = rhs->right;
        binary_operation->line = lhs->line;
        binary_operation->node_type = NODE_BINARY_OPERATION;
        binary_operation->contents.binary_operation = (struct Binary_Operation) {
            .left = lhs,
            .right = rhs,
            .op = operator
        };
        lhs = binary_operation;
    }

    return lhs;

}

struct Node *parse_sum( struct Context *context ) {
    // We can have:
    // [1] parse_mult + parse_sub_expression
    // [2] parse_mult - parse_sub_expression
    // [3] parse_mult

    struct Node *lhs = parse_mult(context);

    while (peek_token(context)->token_type == TOKEN_PLUS || peek_token(context)->token_type == TOKEN_MINUS)  {
        next_token(context);
        enum TOKEN operator = current_token(context)->token_type;
        struct Node *binary_operation = get_empty_node();
        struct Node *rhs = parse_sum(context);

        binary_operation->left = lhs->left;
        binary_operation->right = rhs->right;
        binary_operation->line = lhs->line;
        binary_operation->node_type = NODE_BINARY_OPERATION;
        binary_operation->contents.binary_operation = (struct Binary_Operation) {
            .left = lhs,
            .right = rhs,
            .op = operator
        };
        lhs = binary_operation;
    }

    return lhs;
}

struct Node *parse_mult( struct Context *context ) {
    // We can have:
    // [1] parse_token * parse_mult
    // [2] parse_token / parse_mult
    // [3] parse_token

    struct Node *lhs = parse_token(context);

    while (peek_token(context)->token_type == TOKEN_TIMES || peek_token(context)->token_type == TOKEN_DIV)  {
        next_token(context);
        enum TOKEN operator = current_token(context)->token_type;
        struct Node *binary_operation = get_empty_node();
        struct Node *rhs = parse_mult(context);

        binary_operation->left = lhs->left;
        binary_operation->right = rhs->right;
        binary_operation->line = lhs->line;
        binary_operation->node_type = NODE_BINARY_OPERATION;
        binary_operation->contents.binary_operation = (struct Binary_Operation) {
            .left = lhs,
            .right = rhs,
            .op = operator
        };
        lhs = binary_operation;
    }

    return lhs;
}

struct Node *parse_token( struct Context *context ) {
    // We can have:
    // [1] TOKEN_LPAREN parse_expression TOKEN_RPAREN
    // [2] TOKEN_NUMBER_D
    // [3] TOKEN_NUMBER_F
    // [4] TOKEN_STRING
    // [5] parse_symbol ?( ?argument_list ?)
    // [6] TOKEN_AND parse_expression
    // [7] TOKEN_TIMES parse_expression
    // [8] TOKEN_FALSE
    // [9] TOKEN_TRUE
    switch (peek_token(context)->token_type) {
        case TOKEN_LPAREN: {
            // Case [1]
            next_token(context);
            struct Node *expr = parse_expression(context);

            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_RPAREN, .error_string = String(
                        .str = "Unexpected Token while parsing expression. Expected closing ')'\n",
                        .length = 64 ));
            next_token(context);
            return expr;
        } break;
        case TOKEN_NUMBER_D: {
            // Case [2]
            next_token(context);
            struct Node *num = get_empty_node();
            num->node_type = TOKEN_NUMBER_D;
            struct Token *current = current_token(context);
            num->contents.decimal_number.inum = current->data.inum;
            num->left = current->left;
            num->right = current->right;
            num->line = current->line;
            return num;
        } break;

        case TOKEN_NUMBER_F: {
            // Case [3]

            next_token(context);
            struct Node *num = get_empty_node();
            num->node_type = TOKEN_NUMBER_F;
            struct Token *current = current_token(context);
            num->contents.float_number.fnum = current->data.fnum;
            
            num->left = current->left;
            num->right = current->right;
            num->line = current->line;
            return num;
        } break;

        case TOKEN_STRING: {
            // Case [4]
            next_token(context);
            struct Token *current = current_token(context);

            struct Node *symbol = get_empty_node();
            symbol->node_type = TOKEN_STRING;
            symbol->contents.string.str = current->data.str;
            symbol->left = current->left;
            symbol->right = current->right;
            symbol->line = current->line;
            return symbol;
        } break;

        case TOKEN_IDENTIFIER: {
            // Case [5]
            next_token(context);
            struct Node *symbol = parse_symbol( context );
            if (peek_token(context)->token_type == TOKEN_LPAREN) {
                // function call
                struct Node *function_call = get_empty_node();
                next_token(context);

                struct Node *arguments = parse_argument_list(context);

                assert_token_type(context, .which = PEEK, .expected_token = TOKEN_RPAREN, .error_string = String(
                    .str = "Unexpected Token while trying to parse a function call. Expected ')'\n",
                    .length = 69 ));
                next_token(context);

                function_call->contents.function_call = (struct Function_Call) {
                    .lhs = symbol,
                    .arguments = arguments // NULL IF ZERO ARGUMENTS
                };

                function_call->left = symbol->left;
                function_call->line = symbol->line;
                function_call->right = current_token(context)->right;

                function_call->node_type = NODE_FN_CALL;
                symbol = function_call;
            }
            return symbol;
        } break;

        case TOKEN_AND: {
            // Case [6]
            next_token(context);
            struct Node *addressof = get_empty_node();
            
            addressof->left = current_token(context)->left;
            addressof->line = current_token(context)->line;
            
            struct Node *addressme = parse_expression(context);
            
            addressof->right = addressme->right;

            addressof->contents.address_of.expression = addressme;
            addressof->node_type = NODE_ADDRESS_OF;
            
            return addressof;
        } break;

        case TOKEN_TIMES: {
            // Case [7]
            next_token(context);
            struct Node *deref = get_empty_node();

            deref->left = current_token(context)->left;
            deref->line = current_token(context)->line;

            struct Node *derefme = parse_expression(context);

            deref->right = derefme->right;

            deref->contents.address_of.expression = derefme;
            deref->node_type = NODE_DEREF;
            return deref;
        } break;

        case TOKEN_FALSE: {
            // Case [8]
            next_token(context);
            struct Node *num = get_empty_node();
            num->node_type = TOKEN_NUMBER_D;
            num->contents.decimal_number.inum = 0;
            struct Token *current = current_token(context);
            num->left = current->left;
            num->right = current->right;
            num->line = current->line;
            return num;

        } break;

        case TOKEN_TRUE: {
            // Case [8]
            next_token(context);
            struct Node *num = get_empty_node();
            num->node_type = TOKEN_NUMBER_D;
            num->contents.decimal_number.inum = 0;
            struct Token *current = current_token(context);
            num->left = current->left;
            num->right = current->right;
            num->line = current->line;
            return num;
        } break;

        default: {
            emit_error(context, .token = peek_token(context), .error_string = String(
                        .str = "Unexpected Token in expression.\n",
                        .length = 32 ));
        }
    }

    return NULL;
}

struct Node *get_empty_node(void) {
    if (NODE_BUFFER_INDEX == NODE_BUFFER_SIZE) {
        // For now just realloc....

        NODE_BUFFER = realloc(NODE_BUFFER, NODE_BUFFER_SIZE * 2);
        if (NODE_BUFFER == NULL) {
            print_string(String( .str = "Out of memory\n", .length = 14));
            _Exit(2);
        }
        NODE_BUFFER_SIZE *= 2;
    }
    return &NODE_BUFFER[NODE_BUFFER_INDEX++];
}
