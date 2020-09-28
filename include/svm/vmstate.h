#ifndef SVM_VMSTATE_H
#define SVM_VMSTATE_H

#include <stddef.h>
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <svm/assert.h>

#define SVM_NUM_REGISTERS 256

typedef struct {
    /* svm_string_pool_t string_pool; */
    /* svm_value_t registers[SVM_NUM_REGISTERS]; */
    /* svm_table_t globals; */
    /* svm_value_t *literals; */
    size_t num_literals;
    struct svm_jmpbuf *errorjmp;
} svm_vmstate_t;

struct svm_jmpbuf {
    struct svm_jmpbuf *prev;
    jmp_buf buf;
    volatile int status;
};

/** @brief SVM equivalent of C++'s try { } catch { }
 * @param vm A `svm_vmstate_t *` containing the error handle stack
 * @param ... Statements to execute in the context of the error handler
 * @return 0 if successful, or nonzero with the error code thrown
 */
#define SVM_CATCH(vm, ...) __extension__ ({             \
    struct svm_jmpbuf __svm_catch_jmpbuf;               \
    svm_vmstate_t *__svm_catch_vm = (vm);               \
    __svm_catch_jmpbuf.prev = __svm_catch_vm->errorjmp; \
    __svm_catch_jmpbuf.status = 0;                      \
    __svm_catch_vm->errorjmp = &__svm_catch_jmpbuf;     \
    if (setjmp(__svm_catch_jmpbuf.buf) == 0) {          \
        __VA_ARGS__                                     \
    }                                                   \
    __svm_catch_vm->errorjmp = __svm_catch_jmpbuf.prev; \
    __svm_catch_jmpbuf.status;                          \
})

/** @brief SVM equivalent of C++'s throw
 * @param vm A `svm_vmstate_t *` containing the error handle stack
 * @param code The error code to throw
 * @note The error code should be nonzero if the error should be detected
 */
static inline noreturn void svm_throw(svm_vmstate_t *vm, int code) {
    if (vm->errorjmp) {
        vm->errorjmp->status = code;
        longjmp((vm)->errorjmp->buf, 1);
    } else {
        fprintf(stderr, "No panic set - aborting with errorcode %d!\n", code);
        fflush(stderr);
        abort();
    }
}

#endif /* ifndef SVM_VMSTATE_H */
