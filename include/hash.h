#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef H_HASH
#define H_HASH
typedef struct hash_table hash;
typedef struct hash_elem_s hash_elem_t;

enum key_type {
    INT_PTR,
    UINT_PTR
} key_type;

struct hash_elem_s {
    uint8_t *key;
    void *value;
    size_t value_len;
    hash_elem_t *next;
};

struct hash_table {
    enum key_type type;
    hash_elem_t **elements;
    size_t elements_length;
    size_t hash_len;
    size_t capacity;
};

hash *hash_init (size_t, enum key_type);
void hash_destroy (hash **hash);
void hash_put (hash *table, void *key, void *data, size_t length);
hash_elem_t *hash_get (hash *table, void *key);
void hash_del (hash *table, void *key);
int match (enum key_type, void *key1, void *key2, size_t key1_size);
#endif
