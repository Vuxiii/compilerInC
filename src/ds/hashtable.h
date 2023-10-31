#pragma once
#include <stdint.h>
#include "../string.h"
#include "../defines.h"

#define HASHTABLE_SIZE 1000
#define HASHTABLE_THRESHHOLD 0.8
struct HashTable {
    ARRAY(struct HT_Entry) items;
    uint32_t size;
    uint32_t count;
};

struct HT_Entry {
    struct String *key;
    void *value;
};

uint32_t ht_hash(struct HashTable *table, struct String *key);

void ht_insert(struct HashTable *table, struct String *key, void *value);

void *ht_get(struct HashTable *table, struct String *key);

int ht_contains(struct HashTable *table, struct String *key);

struct HashTable ht_construct(void);
