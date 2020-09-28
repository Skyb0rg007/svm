
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <svm/string.h>
#include <svm/assert.h>

static size_t MIN_TABSIZE = 256;

static uint64_t fnv1a(const uint8_t *str, size_t len)
{
    static const uint64_t FNV_OFFSET_BASIS = UINT64_C(14695981039346656037);
    static const uint64_t FNV_PRIME = UINT64_C(1099511628211);

    uint64_t h = FNV_OFFSET_BASIS;
    for (size_t i = 0; i < len; i++) {
        h ^= str[i];
        h *= FNV_PRIME;
    }
    return h;
}

static void pool_resize(svm_string_pool_t *pool, size_t new_mask)
{
    svm_string_t **newtab = malloc(sizeof *newtab * (new_mask + 1));
    svm_assert_release(newtab != NULL);
    memset(newtab, 0x0, sizeof *newtab * (new_mask + 1));

    for (size_t i = 0; i < pool->cap_mask + 1; i++) {
        svm_string_t *str = pool->tab[i];
        if (str == NULL) {
            continue;
        }
        uint64_t hash = str->hash;
        size_t new_pos = hash & new_mask;
        for (size_t j = new_pos; j < new_mask + 1; j++) {
            if (newtab[j] == NULL) {
                newtab[j] = str;
                goto next_elem;
            }
        }

        for (size_t j = 0; j < new_pos; j++) {
            if (newtab[i] == NULL) {
                newtab[j] = str;
                goto next_elem;
            }
        }

        fprintf(stderr, "Aborting!!!\n");
        abort(); /* Something went wrong */
next_elem:
        ;
    }

    free(pool->tab);
    pool->tab = newtab;
    pool->cap_mask = new_mask;
}

static svm_string_t *alloc_string(const char *_str, size_t len, size_t hash) {
    const uint8_t *str = (const uint8_t *)_str;
    svm_string_t *string = malloc(sizeof *string + len + 1);
    svm_assert_release(string != NULL);

    string->length = len;
    string->hash = hash;
    memcpy(string->data, str, len);
    string->data[len] = '\0';
    return string;
}

void svm_string_pool_init(svm_string_pool_t *pool) {
    svm_assert(pool != NULL);
    pool->tab = malloc(sizeof *pool->tab * MIN_TABSIZE);
    svm_assert_release(pool->tab != NULL);
    memset(pool->tab, 0x0, sizeof *pool->tab * MIN_TABSIZE);
    pool->cap_mask = MIN_TABSIZE - 1;
    pool->size = 0;
}

void svm_string_pool_free(svm_string_pool_t *pool) {
    if (pool) {
        for (size_t i = 0; i < pool->cap_mask + 1; i++) {
            free(pool->tab[i]);
        }
        free(pool->tab);
        pool->tab = NULL;
        pool->cap_mask = -1;
        pool->size = 0;
    }
}

svm_string_t *svm_string_new(svm_string_pool_t *pool, const char *str, size_t len) {
    svm_assert(pool != NULL);
    svm_assert(str != NULL);
    svm_assert(len != 0);

    pool->size++;

    /* Load factor of 7/8 */
    if (pool->size * 8 >= pool->cap_mask * 7) {
        /* Next power of 2 */
        pool_resize(pool, (pool->cap_mask << 1) + 1);
    }

    uint64_t hash = fnv1a((const uint8_t *)str, len);
    size_t bucket = hash & pool->cap_mask;
    for (size_t i = bucket; i < pool->cap_mask + 1; i++) {
        if (pool->tab[i] == NULL) {
            bucket = i;
            goto allocate;
        }
        if (pool->tab[i]->hash == hash &&
                pool->tab[i]->length == len &&
                memcmp(pool->tab[i]->data, str, len) == 0) {
            return pool->tab[i];
        }
    }
    for (size_t i = 0; i < bucket; i++) {
        if (pool->tab[i] == NULL) {
            bucket = i;
            goto allocate;
        }
        if (pool->tab[i]->hash == hash &&
                pool->tab[i]->length == len &&
                memcmp(pool->tab[i]->data, str, len) == 0) {
            return pool->tab[i];
        }
    }
    /* There must have been a problem! */
    svm_assert_release(0);

    /* */
allocate:
    {
        svm_string_t *string = alloc_string(str, len, hash);
        svm_assert_release(pool->tab[bucket] == NULL);
        pool->tab[bucket] = string;
        return string;
    }
}



