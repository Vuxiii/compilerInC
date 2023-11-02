#include "hashtable.h"
#include "../error.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t ht_hash(struct HashTable *table, struct String *key) {
    uint32_t hashval = 17;

    for ( uint32_t i = 0; i < key->length; ++i ) {
        hashval += key->str[i] * 31;
    }

    return hashval % table->size;
}

void ht_insert(struct HashTable *table, struct String *key, void *value) {
    // Check if threshold has been exceeded.
    if ( table->count / table->size > (uint32_t)HASHTABLE_THRESHHOLD ) {

        table->items = realloc(table->items, table->size * 2 * sizeof( struct HT_Entry ) );
        if ( table->items == NULL ) {
            emit_allocation_error( String(.str = "HashTable", .length = 9) );
        }
        table->size *= 2;
    }

    uint32_t index = ht_hash(table, key);

    while ( table->items[index].key != NULL ) {
        // Linear probing
        index = (index + 1) % table->size;
    }

    table->items[index] = (struct HT_Entry) { .key = key, .value = value };
    table->count++;
}

void *ht_get(struct HashTable *table, struct String *key) {
    uint32_t index = ht_hash(table, key);

    uint32_t start = index;

    if ( table->items[index].key == NULL ) return NULL;

    while ( table->items[index].key != NULL && cmp_strings(key, table->items[index].key) == 0 ) {
        index = (index + 1) % table->size;
        if ( index == start || table->items[index].key == NULL ) {
            return NULL;
        }
    }

    return table->items[index].value;
}

int ht_contains(struct HashTable *table, struct String *key) {
    uint32_t index = ht_hash(table, key);

    uint32_t start = index;

    if ( table->items[index].key == NULL ) return 0;

    while ( table->items[index].key != NULL && cmp_strings(key, table->items[index].key) == 0 ) {
        index = (index + 1) % table->size;
        if ( index == start || table->items[index].key == NULL ) {
            return 0;
        }
    }

    return 1;
}


struct HashTable ht_construct(void) {
    struct HashTable table = (struct HashTable) {
        .count = 0,
        .size  = HASHTABLE_SIZE,
        .items = calloc(HASHTABLE_SIZE, sizeof( struct HT_Entry ))
    };
    if (table.items == NULL) {
        emit_allocation_error( String(.str = "HashTable", .length = 9) );
    }
    return table;
}

