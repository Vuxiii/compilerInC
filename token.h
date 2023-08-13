#ifndef TOKEN_H
#define TOKEN_H
#include "string.h"
enum TOKEN {
    TOKEN_EOP        = -1,
    TOKEN_LET        =  0,
    TOKEN_FN         =  1,
    TOKEN_LPAREN     =  2,
    TOKEN_RPAREN     =  3,
    TOKEN_LCURLY     =  4,
    TOKEN_RCURLY     =  5,
    TOKEN_LBRACKET   =  6,
    TOKEN_RBRACKET   =  7,
    TOKEN_COLON      =  8,
    TOKEN_DOUBLE_COLON = 9,
    TOKEN_SEMICOLON  =  10,
    TOKEN_COMMA      = 11,
    TOKEN_DOT        = 12,
    TOKEN_NUMBER_F   = 13,
    TOKEN_NUMBER_D   = 14,
    TOKEN_STRING     = 15,
    TOKEN_IDENTIFIER = 16,
    TOKEN_PLUS       = 17,
    TOKEN_MINUS      = 18,
    TOKEN_DIV        = 19,
    TOKEN_TIMES      = 20,
    TOKEN_MODULO     = 21,
    TOKEN_SINGLE_AND = 22,
    TOKEN_SINGLE_OR  = 23,
    TOKEN_DOUBLE_AND = 24,
    TOKEN_DOUBLE_OR  = 25,
    TOKEN_BANG       = 26,
    TOKEN_LESS       = 27,
    TOKEN_GREATER    = 28,
    TOKEN_LESS_EQ    = 29,
    TOKEN_GREATER_EQ = 30,
    TOKEN_DOUBLE_EQ  = 31,
    TOKEN_NOT_EQ     = 32,
    TOKEN_EQ         = 33,
    TOKEN_FALSE      = 34,
    TOKEN_TRUE       = 35,
    TOKEN_STRUCT     = 36, // Compounded type. Just packing.
    TOKEN_TYPE       = 37, // Enable the user to make their own types. Custom behaviour
    TOKEN_WHILE      = 38,
    TOKEN_FOR        = 39,

    NODE_COMPOUND_STATEMENT,
    NODE_FN_DECLARATION,
    NODE_FN_CALL,
    NODE_SYMBOL,
    NODE_FIELD_ACCESS,
    NODE_ARRAY_ACCESS,
    NODE_VARIABLE_DECLARATION,
    NODE_ARRAY_DECLARATION,
    NODE_TYPE_DECLARATION,
    NODE_STRUCT_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_ADDRESS_OF,
    NODE_DEREF,
    NODE_BINARY_OPERATION,
    NODE_PARAMETER_LIST,
    NODE_ARGUMENT_LIST,
    NODE_FOR,
    NODE_SCOPE,
};

enum PRIMITIVE_TYPE {
    i8  = 0,
    i16 = 1,
    i32 = 2,
    i64 = 3,

    u8  = 4,
    u16 = 5,
    u32 = 6,
    u64 = 7,

    f32 = 8,
    f64 = 9,
    string = 10,
};

struct Token {
    enum TOKEN token_type;

    union {
        long long     inum; // 64 bit
        double        fnum; // 64 bit
        struct String*str;  // 64 bit
        struct Node  *node; // 64 bit
    } data;

    unsigned int line;
    unsigned int left;
    unsigned int right;
};

struct Declaration_Function {
    struct String *function_name;
    struct Node *parameters; // NULL if no parameters
    struct Node *body;
};

struct Declaration_Variable {
    // What physical type does the variable contain
    // i8, u8, i16, u16, f8, f16 ...
    enum PRIMITIVE_TYPE literal_type;
    struct String *variable_name;
    struct String *variable_type;
};

struct Declaration_Array {
    struct String *array_name;
    struct String *array_type;
    long long length;
};

struct Declaration_Type {

};

struct Declaration_Struct {
    struct String *struct_name;
    struct Node *fields;
    long long count; // If not set: -1
};

struct For_Loop {
    struct Node *init;      // NULLABLE
    struct Node *guard;
    struct Node *advance;   // NULLABLE
    struct Node *body;
};

struct Function_Call {
    struct Node *lhs;
    struct Node *arguments; // NULL if no parameters
};

struct Parameter_List {
    struct Node *parameter;
    struct Node *next;
};

struct Argument_List {
    struct Node *argument;
    struct Node *next;
};


struct Assignment {
    struct Node *lhs;
    struct Node *rhs;
};

struct Number_D {
    long long inum;
};

struct Number_F {
    double fnum;
};

struct Symbol {
    struct String *str;
};

struct Expression {
    struct Node *expression;
};

struct Array_Access {
    struct String *lhs;
    struct Node *index;
};

struct Field_Access {
    struct Node *lhs;
    struct Node *rhs;
};

struct Compound_Statement {
    struct Node *left;
    struct Node *right;
};

struct Binary_Operation {
    struct Node *left;
    struct Node *right;
    enum TOKEN op;
};

struct Node {
    enum TOKEN node_type;
    union {
        struct Function_Call            function_call;
        struct Declaration_Function     function_declaration;
        struct Declaration_Variable     variable_declaration;
        struct Declaration_Array        array_declaration;
        struct Declaration_Struct       struct_declaration;
        struct Declaration_Type         type_declaration;
        struct Parameter_List           parameter_list; 
        struct Argument_List            argument_list;
        struct Declaration_Variable     parameter;
        struct Assignment               assignment;
        struct Compound_Statement       compound_statement;
        struct Symbol                   symbol;
        struct Field_Access             field_access;
        struct Array_Access             array_access;
        struct Number_D                 decimal_number;
        struct Number_F                 float_number;
        struct Symbol                   string;
        struct Expression               address_of;
        struct Expression               deref;
        struct Binary_Operation         binary_operation;
        struct For_Loop                 for_loop;
        struct Expression               scope;
    } contents;
    
    unsigned int line;
    unsigned int left;
    unsigned int right;

};

#endif
