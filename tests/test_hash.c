#include <stdlib.h>
#include <string.h>
#include "thc.h"
#include "hash.h"

void test_hash_init_destroy (void)
{
    hash *table;
    table = hash_init (256, UINT_PTR);

    ENSURE(table != NULL);
    ENSURE(table->elements_length == 0);
    ENSURE(table->hash_len == 0);
    ENSURE(table->capacity == 256);

    hash_destroy (&table);

    ENSURE(table == NULL);

    hash_destroy (&table);

    ENSURE(table == NULL);
}

void test_hash_put_get (void)
{
    hash *table;
    hash_elem_t *element;
    table = hash_init (256, UINT_PTR);

    char *d1 = strdup ("Test");
    uint8_t key[] = "Key";

    hash_put (table, key, d1, strlen (d1));

    /* should not crash */
    hash_put (NULL, key, d1, strlen (d1));
    hash_put (table, NULL, d1, strlen (d1));
    hash_put (table, key, NULL, strlen (d1));
    hash_put (table, key, d1, 0);

    element = hash_get (table, key);
    ENSURE(match(table->type, element->value, d1, element->value_len));

    ENSURE(NULL == hash_get (table, (uint8_t*)"k"));
    ENSURE(NULL == hash_get (NULL, (uint8_t*)"k"));
    ENSURE(NULL == hash_get (table, NULL));

    hash_destroy (&table);
}

void test_hash_put_get_int_key (void)
{
    hash *table;
    hash_elem_t *element;
    table = hash_init (256, INT_PTR);

    char *d1 = strdup ("Test");
    int key = 10;
    int dummy_key = 11;

    hash_put (table, &key, d1, strlen (d1));

    /* should not crash */
    hash_put (NULL, &key, d1, strlen (d1));
    hash_put (table, NULL, d1, strlen (d1));
    hash_put (table, &key, NULL, strlen (d1));
    hash_put (table, &key, d1, 0);

    element = hash_get (table, &key);
    ENSURE(match(table->type, element->value, d1, element->value_len));

    ENSURE(NULL == hash_get (table, &dummy_key));
    ENSURE(NULL == hash_get (NULL, &dummy_key));
    ENSURE(NULL == hash_get (table, NULL));

    hash_destroy (&table);
}

void test_hash_put_collision (void)
{
    hash *table;
    hash_elem_t *element;
    table = hash_init (1, UINT_PTR);

    char *d1 = strdup ("Test");
    char *d2 = strdup ("Test 2");
    uint8_t key[] = "Key";

    hash_put (table, key, d1, strlen (d1));
    hash_put (table, key, d2, strlen (d2));

    element = hash_get (table, key);
    ENSURE(match(table->type, element->value, d2, element->value_len));

    char *d3 = strdup ("Test 3");
    uint8_t key2[] = "Key2";

    hash_put (table, key2, d3, strlen (d3));
    element = hash_get (table, key2);
    ENSURE(match(table->type, element->value, d3, element->value_len));

    hash_destroy (&table);
}

void test_hash_put_collision_int_key (void)
{
    hash *table;
    hash_elem_t *element;
    table = hash_init (1, UINT_PTR);

    char *d1 = strdup ("Test");
    char *d2 = strdup ("Test 2");
    int key = 10;

    hash_put (table, &key, d1, strlen (d1));
    hash_put (table, &key, d2, strlen (d2));

    element = hash_get (table, &key);
    ENSURE(match(table->type, element->value, d2, element->value_len));

    char *d3 = strdup ("Test 3");
    int key2 = 100;

    hash_put (table, &key2, d3, strlen (d3));
    element = hash_get (table, &key2);
    ENSURE(match(table->type, element->value, d3, element->value_len));

    hash_destroy (&table);
}

void test_hash_del (void)
{
    hash *table;
    hash_elem_t *element;
    table = hash_init (1, UINT_PTR);

    char *d1 = strdup ("Test");
    uint8_t key[] = "Key";

    hash_put (table, key, d1, strlen (d1));
    hash_del (table, key);

    ENSURE (NULL == hash_get (table, key));

    char *d2 = strdup ("Test 2");

    hash_put (table, key, d2, strlen (d2));

    ENSURE (NULL != hash_get (table, key));

    hash_del (table, key);

    ENSURE (NULL == hash_get (table, key));

    uint8_t key2[] = "k2";
    char *d3 = strdup ("T3");

    hash_put (table, key2, d3, strlen (d3));

    ENSURE (NULL != hash_get (table, key2));

    element = hash_get (table, key2);
    ENSURE(match(table->type, element->value, "T3", element->value_len));

    hash_del (table, key2);

    ENSURE (NULL == hash_get (table, key2));

    hash_destroy (&table);
}
void test_hash_del_int_key (void)
{
    hash *table;
    hash_elem_t *element;
    table = hash_init (1, UINT_PTR);

    char *d1 = strdup ("Test");
    int key = 30;

    hash_put (table, &key, d1, strlen (d1));
    hash_del (table, &key);

    ENSURE (NULL == hash_get (table, &key));

    char *d2 = strdup ("Test 2");

    hash_put (table, &key, d2, strlen (d2));

    ENSURE (NULL != hash_get (table, &key));

    hash_del (table, &key);

    ENSURE (NULL == hash_get (table, &key));

    int key2 = 900;
    char *d3 = strdup ("T3");

    hash_put (table, &key2, d3, strlen (d3));

    ENSURE (NULL != hash_get (table, &key2));

    element = hash_get (table, &key2);
    ENSURE(match(table->type, element->value, "T3", element->value_len));

    hash_del (table, &key2);

    ENSURE (NULL == hash_get (table, &key2));

    hash_destroy (&table);
}
