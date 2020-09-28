#ifndef SVM_CONFIG_H
#define SVM_CONFIG_H

/** @def SVM_BIG_ENDIAN
 * @brief 1 if arch is big-endian, 0 otherwise
 */
#ifndef SVM_BIG_ENDIAN
/* Use glibc <endian.h> */
#  include <endian.h>
#  if __BYTE_ORDER == __BIG_ENDIAN
#    define SVM_BIG_ENDIAN 1
#  elif __BYTE_ORDER == __LITTLE_ENDIAN
#    define SVM_BIG_ENDIAN 0
#  else
#    error "Byte order neither big nor little endian (no support for PDP endian)"
#  endif
#endif /* ifndef SVM_ENDIAN */

/** @def SVM_ENDIAN_LOHI
 * @brief Orders the arguments so the first argument corresponds to the low bytes
 */
#if SVM_BIG_ENDIAN
#  define SVM_ENDIAN_LOHI(lo, hi) lo hi
#else
#  define SVM_ENDIAN_LOHI(lo, hi) hi lo
#endif

/** @def SVM_64
 * @brief 1 if pointers are 64-bit, 0 otherwise
 */
#ifndef SVM_64
#  if __SIZEOF_POINTER__ == 8
#    define SVM_64 1
#  elif __SIZEOF_POINTER__ == 4
#    define SVM_64 0
#  else
#    error "Architecture neither 64 nor 32 bit"
#  endif
#endif /* ifndef SVM_64 */

/* Sanity checks */
_Static_assert(sizeof(void *) == SVM_64 ? 8 : 4, "SVM_64 is incorrect");

#endif /* ifndef SVM_CONFIG_H */
