#include "ssa.h"
#include "string.h"
#include <stddef.h>
#include <stdlib.h>

/**
static void ***current_def;
static char *sealed_blocks;
static struct SSA_Variable ***incomplete_phis;
static struct Predecessor *pred;
void write_variable(struct String *variable, unsigned int block, void *value) {

    current_def[hash(variable)][block] = value
    
}

struct SSA_Variable *read_variable(struct String *variable, unsigned int block) {

    if (current_def[hash(variable)][block] != NULL) {
        return current_def[hash(variable)][block];
    }
    return read_variable_recursive( variable, block)
}

struct SSA_Variable *read_variable_recursive(struct String *variable, unsigned int block) {
    struct SSA_Variable *val;
    if (sealed_blocks[block] == 1) {
        val = make_phi(block);
        incomplete_phis[block][hash(variable)] = val;
    } else if (pred[block].count == 1) {
        val = read_variable(variable, pred[block].predecessor_block[0]); 
    } else {
        val = make_phi(block);
        write_variable( variable, block, val );
        val = add_phi_operands( variable, val );
    }
    write_variable( variable, block, val);
    return val;
}

struct SSA_Variable *add_phi_operands(struct String *variable, struct SSA_Variable *phii) {
    struct Phi *phi = &phii->contents.phi;
    for ( int i = 0; i < pred[phi->block].count; ++i ) {
        append_operand( phii, read_variable(variable, pred[phi->block].predecessor_block[i]));
    }
    return try_remove_trivial_phi( phii );
}

struct SSA_Variable *try_remove_trivial_phi( struct SSA_Variable *varphi ) {
    struct SSA_Variable *same = NULL;
    struct Phi *phi = &varphi->contents.phi;
    for (int i = 0; i < phi->op_count; ++i) {
        if (phi->operands[i] == same || phi->operands[i] == varphi)
            continue;

        if (same != NULL)
            return varphi;
        same = phi->operands[i];
    }
    if (same == NULL) 
        same = undef();

    unsigned int users_count = phi->users_count - 1;

    struct SSA_Variable *users = malloc( sizeof(struct Phi) * users_count);
    for (int j, i = j = 0; i < phi->users_count - 1; ++i) {
        if (*phi->users[i] != *varphi)
            users[j++] = phi->users[i];
    }

    replace_phi_with(varphi, same);

    for (int i = 0; i < users_count; ++i) {
        if (users[i].isPhi == 1) {
            try_remove_trivial_phi(&users[i]);
        }
    }

    return same;
}
*/
