
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <svm/string.h>
#include <svm/assert.h>

#define N 1000000

int main(void)
{

    svm_string_pool_t pool;
    svm_string_pool_init(&pool);

    for (int i = 0; i < N; i++) {
        static char buf[2048];
        int len = snprintf(buf, sizeof buf, "String #%08d", i);
        svm_string_t *s = svm_string_new(&pool, buf, len);
        assert(memcmp(s->data, buf, len) == 0);
    }

    svm_string_pool_free(&pool);
    return 0;
}
