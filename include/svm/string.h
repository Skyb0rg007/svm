/* vim: set ft=c: */
#ifndef SVM_STRING_H
#define SVM_STRING_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint64_t length;
    uint64_t hash;
    uint8_t data[];
} svm_string_t;

typedef struct {
    svm_string_t **tab;
    size_t cap_mask; /* Capacity - 1 */
    size_t size;     /* Number of strings */
} svm_string_pool_t;

void svm_string_pool_init(svm_string_pool_t *pool);
void svm_string_pool_free(svm_string_pool_t *pool);
svm_string_t *svm_string_new(svm_string_pool_t *pool, const char *str, size_t len);

#endif /* ifndef SVM_STRING_H */
