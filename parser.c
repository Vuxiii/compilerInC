#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "token.h"
#include <stdlib.h>
#include <unistd.h>


extern struct Node *NODE_BUFFER;
static unsigned int NODE_BUFFER_INDEX = 0;
static unsigned int NODE_BUFFER_SIZE = NODE_BUFFER_INITIAL_SIZE;
struct Node *parse(struct Context *context) {
    next_token(context);
    while (current_token(context)->token_type != TOKEN_EOP) {
        return parse_toplevel_statement(context);
    }
    return NULL;
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
                            .str = "Unexpected Token.\n",
                            .length = 19),
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
                                 .str = "Unexpected Token. Expected '('\n",
                                 .length = 31));
    
    // Insert parameter list here

    next_token(context);
    // Current: TOKEN_RPAREN
    assert_token_type(context, .expected_token = TOKEN_RPAREN, .which = CURRENT,
                             .error_string = String( 
                                 .str = "Unexpected Token. Expected ')'\n",
                                 .length = 31));
    
    next_token(context);
    // Current: TOKEN_LCURLY
    assert_token_type(context, .expected_token = TOKEN_LCURLY, .which = CURRENT,
                             .error_string = String( 
                                 .str = "Unexpected Token. Expected '{'\n",
                                 .length = 31));

    // We want the parent node first. So we get a linear progression in the array.
    // Otherwise, we would have the body before the function declaration in memory.
    struct Node *out = get_empty_node();

    struct Node *body = parse_statement(context);

    // Current: TOKEN_RCURLY
    assert_token_type(context, .expected_token = TOKEN_RCURLY, .which = CURRENT,
                             .error_string = String( 
                                 .str = "Unexpected Token. Expected '}'\n",
                                 .length = 31));


    out->contents.function_declaration = (struct Declaration_Function){
        .function_name = func_name, 
        .body = body
    };
    out->node_type = NODE_FN_DECLARATION;
    return out;
}

struct Node *parse_statement( struct Context *context ) {
    next_token(context);
    struct Node *some_statement = NULL;
    switch (current_token(context)->token_type) {
        case TOKEN_LET: {
            some_statement = parse_declaration(context);
        } break;
        default: {
            return NULL;
        }
    }
    struct Node *rhs_statement = parse_statement(context);
    if (!rhs_statement) {
        return some_statement;
    }

    // We have to make a compound statement
    struct Node *compound_statement = get_empty_node();
    compound_statement->node_type = NODE_COMPOUND_STATEMENT;
    compound_statement->left  = some_statement->left;
    compound_statement->right = rhs_statement->right;
    compound_statement->line  = some_statement->line;
    compound_statement->contents.compound_statement.left = some_statement;
    compound_statement->contents.compound_statement.right = rhs_statement;
    return compound_statement;
}

struct Node *parse_symbol( struct Context *context ) {
    // [1] IDENTIFIER
    // [2] IDENTIFIER . parse_symbol
    // [3] IDENTIFIER [ EXPRESSION ]
    // [4] IDENTIFIER [ EXPRESSION ] . parse_symbol

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
                .str = "Unexpected Token in declaration. Expected one of [ '.' , '[' ]\n",
                .length = 63));

    // We never reach here.
    return NULL;
}

struct Node *parse_declaration( struct Context *context ) {
    // [1] LET IDENTIFIER : IDENTIFIER ;
    // [2] LET IDENTIFIER : IDENTIFIER = expression ;
    // [3] LET IDENTIFIER : [ NUMBER ] IDENTIFIER ;
    // [4] LET IDENTIFIER :: IDENTIFIER ;
    // [5] LET IDENTIFIER :: STRUCT { parameter_list } ;
    
    // Current: LET
    struct Token *let_token = current_token(context);
    
    next_token(context);

    assert_token_type(context, .which = CURRENT, .expected_token = TOKEN_IDENTIFIER,
                             .error_string = String( 
                                 .str = "Unexpected Token. Expected an Identifier\n",
                                 .length = 41));
    // Current: TOKEN_IDENTIFIER
    
    struct Token *lhs_identifier = current_token(context);
    next_token(context);

    switch (current_token(context)->token_type) {
        case TOKEN_COLON: {
            // Current: TOKEN_COLON
            next_token(context);
            switch (current_token(context)->token_type) {
                case TOKEN_IDENTIFIER: {
                    // Current: TOKEN_IDENTIFIER
                    struct String *type = current_token(context)->data.str;

                    next_token(context);
                    switch (current_token(context)->token_type) {
                        case TOKEN_SEMICOLON: {
                            // [1] LET IDENTIFIER : IDENTIFIER ;
                            struct Node *decl = get_empty_node();
                            decl->contents.variable_declaration = (struct Declaration_Variable){
                                .variable_name = lhs_identifier->data.str,
                                .variable_type = type
                            };
                            decl->line = let_token->line;
                            decl->left = let_token->left;
                            decl->right = current_token(context)->right;
                            decl->node_type = NODE_VARIABLE_DECLARATION;
                            return decl;
                        } break;
                        case TOKEN_EQ: {
                            // [2] LET IDENTIFIER : IDENTIFIER = expression ;

                            // Current: TOKEN_EQ
                            struct Node *compound = get_empty_node();
                            struct Node *lhs = get_empty_node();
                            struct Node *decl = get_empty_node();
                            struct Node *assignment = get_empty_node();
                            struct Node *rhs = parse_expression( context );
    
                            assert_token_type(context, .which = PEEK, .expected_token = TOKEN_SEMICOLON, .error_string = String(
                                        .str = "Unexpected Token. Expected a ';'\n",
                                        .length = 33));
                            next_token(context);

                            // Fill decl
                            decl->contents.variable_declaration = (struct Declaration_Variable){
                                .variable_name = lhs_identifier->data.str,
                                .variable_type = type
                            };
                            decl->line = let_token->line;
                            decl->left = let_token->left;
                            decl->right = rhs->right;
                            decl->node_type = NODE_VARIABLE_DECLARATION;
                            lhs->contents.symbol.str = lhs_identifier->data.str;
                            assignment->contents.assignment = (struct Assignment){
                                .lhs = lhs,
                                .rhs = rhs
                            };
                            assignment->line = let_token->line;
                            assignment->left = let_token->left;
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
                            emit_error(context, .token = current_token(context), .error_string = String(
                                        .str = "Unexpected Token. Expected one of [ ';' , '=' ]\n",
                                        .length = 48));
                        } break;
                    }

                } break;
                case TOKEN_LBRACKET: {
                    // [3] LET IDENTIFIER : [ NUMBER ] IDENTIFIER ;
                    // Current: TOKEN_LBRACKET
                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_NUMBER_D, .error_string = String( 
                                .str = "Unexpected Token. The length of the array MUST be literal number.\n", 
                                .length = 66 ));
                    next_token(context);
                    // Current: TOKEN_NUMBER_B

                    struct Token *length = current_token(context);
                    
                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_RBRACKET, .error_string = String(
                                .str = "Unexpected Token. Expected a ']'\n",
                                .length = 33));
                    next_token(context);
                    // Current: TOKEN_RBRACKET

                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_IDENTIFIER, .error_string = String(
                                .str = "Unexpected Token. Expected a Type for the array declaration\n",
                                .length = 60 ));
                    next_token(context);
                    // Current: TOKEN_IDENTIFIER

                    struct Token *type = current_token(context);

                    assert_token_type(context, .which = PEEK, .expected_token = TOKEN_SEMICOLON, .error_string = String(
                                .str = "Unexpected Token. Expected a ';'\n",
                                .length = 33 ));
                    next_token(context);

                    struct Node *array_decl = get_empty_node();
                    array_decl->contents.array_declaration = (struct Declaration_Array){
                        .array_name = lhs_identifier->data.str,
                        .array_type = type->data.str,
                        .length = length->data.inum
                    };
                    array_decl->left = lhs_identifier->left;
                    array_decl->right = length->right;
                    array_decl->line = lhs_identifier->line;
                    array_decl->node_type = NODE_ARRAY_DECLARATION;
                    return array_decl;
                } break;
                default: {
                    emit_error(context, .token = current_token(context), .error_string = String(
                                .str = "Unexpected Token. Expected one of [ Identifier , '[' ]\n",
                                .length = 55) );
                } break;
            }
        } break;
        case TOKEN_DOUBLE_COLON: {

        } break;
        default: {
            emit_error(context, .token = current_token(context),
                            .error_string = String(
                                .str = "Unexpected Token. Expected one of [ ':' , '::' ]\n",
                                .length = 49));
        } break;
    }

    return NULL;
}

struct Node *parse_assignment( struct Context *context ) {
    
    return NULL;
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
    // [5] parse_symbol
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
                        .str = "Unexpected Token. Expected ')'\n",
                        .length = 31 ));
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
            return parse_symbol( context );
        } break;

        case TOKEN_SINGLE_AND: {
            // Case [6]
            next_token(context);
            struct Node *addressof = get_empty_node();
            struct Node *addressme = parse_expression(context);
            addressof->contents.address_of.expression = addressme;
            addressof->node_type = NODE_ADDRESS_OF;
            return addressof;
        } break;

        case TOKEN_TIMES: {
            // Case [7]
            next_token(context);
            struct Node *deref = get_empty_node();
            struct Node *derefme = parse_expression(context);
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

struct Node *get_empty_node() {
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
