/* vim: set ft=c: */
#ifndef UTILS_ASSERT_H
#define UTILS_ASSERT_H

#include <assert.h>
#include <stdnoreturn.h>

/** @brief Enable all assertions */
#define SVM_ASSERT_LEVEL_PARANOID 3
/** @brief Enable release and normal */
#define SVM_ASSERT_LEVEL_DEBUG    2
/** @brief Enable release assertions */
#define SVM_ASSERT_LEVEL_RELEASE  1
/** @brief Disable all assertions */
#define SVM_ASSERT_LEVEL_NONE     0

/** @def SVM_ASSERT_LEVEL
 * @brief The level that assertions should follow
 */
#ifndef SVM_ASSERT_LEVEL
#  define SVM_ASSERT_LEVEL SVM_ASSERT_LEVEL_DEBUG
#endif

/** @def svm_assert_paranoid
 * @param expr Expression to check
 * @brief Asserts the expression evaluates to non-zero
 * @note This macro removes its argument when not activated
 */
#if SVM_ASSERT_LEVEL >= 3
#  define svm_assert_paranoid(expr) \
    ((expr) ? (void)0 : svm_assert_fail(#expr, __FILE__, __LINE__, __func__))
#else
#  define svm_assert_paranoid(expr) ((void)0)
#endif

/** @def svm_assert
 * @param expr Expression to check
 * @brief Asserts the expression evaluates to non-zero
 * @note This macro removes its argument when not activated
 */
#if SVM_ASSERT_LEVEL >= 2
#  define svm_assert(expr) \
    ((expr) ? (void)0 : svm_assert_fail(#expr, __FILE__, __LINE__, __func__))
#else
#  define svm_assert(expr) ((void)0)
#endif

/** @def svm_assert_release
 * @param expr Expression to check
 * @brief Asserts the expression evaluates to non-zero
 * @note This macro removes its argument when not activated
 */
#if SVM_ASSERT_LEVEL >= 1
#  define svm_assert_release(expr) \
    ((expr) ? (void)0 : svm_assert_fail(#expr, __FILE__, __LINE__, __func__))
#else
#  define svm_assert_release(expr) ((void)0)
#endif

extern noreturn
void svm_assert_fail(const char *assertion, const char *file, unsigned line,
        const char *function);

#endif /* ifndef UTILS_ASSERT_H */
