
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <stdarg.h>
#include <svm/assert.h>

extern noreturn
void svm_assert_fail(const char *assertion, const char *file, unsigned line,
        const char *function)
{
    extern const char *__progname;
    fprintf(stderr, "%s%s%s:%u: %s%sAssertion `%s' failed.\n",
        __progname,
        __progname[0] ? ": " : "",
        file,
        line,
        function ? function : "",
        function ? ": " : "",
        assertion);
    fflush(stderr);
    abort();
}

