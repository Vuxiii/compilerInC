#pragma once
#include "../include/library.h"
#include "../defines.h"

#define HASHTABLE_SIZE 1000
#define HASHTABLE_THRESHOLD 0.8
struct HashTable {
    ARRAY(struct HT_Entry) items;
    u32 size;
    u32 count;
};

struct HT_Entry {
    Str key;
    void *value;
};

uint32_t ht_hash(struct HashTable *table, Str key);

void ht_insert(struct HashTable *table, Str key, void *value);

void *ht_get(struct HashTable *table, Str key);

int ht_contains(struct HashTable *table, Str key);

struct HashTable ht_construct(void);
