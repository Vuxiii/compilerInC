#pragma once

#include "string.h"

struct SSA_Statement {
    struct String *var;
    
};

struct Predecessor {
    unsigned int count;
    unsigned int *predecessor_block;
};

struct Phi {
    struct SSA_Variable **operands;
    struct SSA_Variable *users;
    unsigned int op_count;
    unsigned int users_count;
    unsigned int block;
};

struct SSA_Variable {
    union {
        struct Phi phi;
        
    } contents;
    unsigned int isPhi;
};

struct SSA_Variable *make_phi( unsigned int block );

void write_variable( struct String *variable, unsigned int block, void *value );

struct SSA_Variable *read_variable( void *variable, unsigned int block );

struct SSA_Variable *read_variable_recursive( struct String *variable, unsigned int block );

struct SSA_Variable *add_phi_operands( struct String *variable, struct SSA_Variable *phi );

struct SSA_Variable *try_remove_trivial_phi( struct SSA_Variable *varphi );

void seal_block( unsigned int block );

void remove_redundant_phis( void *phi_functions );

void process_scc( void *scc );

void append_operand( struct SSA_Variable *phi, struct SSA_Variable *variable );

void replace_phi_with( struct SSA_Variable *phi, struct SSA_Variable *variable );
