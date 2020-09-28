
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <svm/vmstate.h>

static svm_vmstate_t vm = {0};

static void bar(void) {
    puts("bar");
    svm_throw(&vm, 23);
    puts("bar2");
}

static void foo(void) {
    puts("foo");
    SVM_CATCH(&vm, {
        bar();
    });
    svm_throw(&vm, 1);
}

int main(void)
{
    int result = SVM_CATCH(&vm, {
        foo();
    });
    printf("Result: %d\n", result);
    return EXIT_SUCCESS;
}


