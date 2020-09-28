
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <svm/assert.h>
#include <svm/value.h>

int main(void)
{
    svm_value_t x;
    svm_value_set_nan(&x);
    assert(svm_value_is_nan(&x));

    {
        double f = 1.14 * (double)rand();
        svm_value_set_double(&x, f);
        assert(svm_value_is_double(&x));
        assert(svm_value_get_double(&x) == f);
    }

    {
        int32_t n = 0xaaaaaaaa;
        svm_value_set_int(&x, n);
        assert(svm_value_is_int(&x));
        assert(svm_value_get_int(&x) == n);
    }

    {
        void *p = malloc(12);
        /* Should be true on Linux */
        assert((uintptr_t)p >> 47 == 0);
        svm_value_set_ptr(&x, p, SVM_TYPE_CLOSURE);
        assert(svm_value_is_closure(&x));
        assert(svm_value_get_ptr(&x) == p);
        free(p);
    }

    {
        void *p = NULL;
        svm_value_set_ptr(&x, p, SVM_TYPE_TABLE);
        assert(svm_value_is_table(&x));
        assert(svm_value_get_ptr(&x) == p);
    }

    return EXIT_SUCCESS;
}

