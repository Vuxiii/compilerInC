#include "hashtable.h"
#include "../error.h"
#include <stdint.h>
#include <stdlib.h>

uint32_t ht_hash(struct HashTable *table, struct String *key) {
    uint32_t hashval = 17;

    for ( uint32_t i = 0; i < key->length; ++i ) {
        hashval += key->str[i] * 31;
    }

    return hashval % table->size;
}

void insert(struct HashTable *table, struct String *key, struct String *value) {
    // Check if threshhold has been exceeded.
    if ( table->count / table->size > (uint32_t)HASHTABLE_THRESHHOLD ) {
        table->items = reallocarray(table->items, table->size*2, sizeof( struct String * ) );
        if ( table->items == NULL ) {
            emit_allocation_error( String(.str = "HashTable", .length = 9) );
        }
        table->size *= 2;
    }

    uint32_t index = ht_hash(table, key);

    while ( table->items[index] != NULL ) {
        // Linear probing
        index = (index + 1) % table->size;
    }

    table->items[index] = value;
    table->count++;
}

struct String *ht_get(struct HashTable *table, struct String *key) {
    uint32_t index = ht_hash(table, key);

    uint32_t start = index;
    while ( cmp_strings(key, table->items[index]) == 0 ) {
        index = (index + 1) % table->size;
        if ( index == start ) {
            return NULL;
        }
    }

    return table->items[index];
}

int ht_contains(struct HashTable *table, struct String *key) {
    return ht_get(table, key) != NULL;
}


struct HashTable ht_construct(void) {
    struct HashTable table = (struct HashTable) {
        .count = 0,
        .size  = HASHTABLE_SIZE,
        .items = malloc( sizeof( struct String *) * HASHTABLE_SIZE)
    };
    if (table.items == NULL) {
        emit_allocation_error( String(.str = "HashTable", .length = 9) );
    }
    return table;
}

