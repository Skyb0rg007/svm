/* vim: set ft=c: */
#ifndef SVM_VALUE_H
#define SVM_VALUE_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <svm/assert.h>
#include <svm/config.h>

/** @brief Union of all types */
typedef union svm_value_t svm_value_t;
/** @brief Common header for all Garbage-collected values */
typedef struct svm_gcheader_t svm_gcheader_t;
/** @section GC Values */
/** @brief Strings */
typedef struct svm_string_t svm_string_t;
/** @brief Functions */
typedef struct svm_function_t svm_function_t;
/** @brief Closures */
typedef struct svm_closure_t svm_closure_t;
/** @brief Tables */
typedef struct svm_table_t svm_table_t;
/** @brief Sequences */
typedef struct svm_sequence_t svm_sequence_t;
/** @brief Blocks */
typedef struct svm_block_t svm_block_t;
/** @brief C functions */
typedef struct svm_cfunc_t svm_cfunc_t;
/** @brief C data */
typedef struct svm_cdata_t svm_cdata_t;

#define SVM_VALUE_TAG_NIL      (UINT32_C(~0))
#define SVM_VALUE_TAG_FALSE    (UINT32_C(~1))
/* All following tags are considered truthy */
#define SVM_VALUE_TAG_TRUE     (UINT32_C(~2))
/* Tags from here to SVM_VALUE_TAG_NUM are garbage-collected (must have a GC header) */
#define SVM_VALUE_TAG_STRING   (UINT32_C(~3))
#define SVM_VALUE_TAG_FUNCTION (UINT32_C(~4))
#define SVM_VALUE_TAG_CLOSURE  (UINT32_C(~5))
#define SVM_VALUE_TAG_TABLE    (UINT32_C(~6))
#define SVM_VALUE_TAG_SEQUENCE (UINT32_C(~7))
#define SVM_VALUE_TAG_BLOCK    (UINT32_C(~8))
#define SVM_VALUE_TAG_CFUNC    (UINT32_C(~9))
#define SVM_VALUE_TAG_CDATA    (UINT32_C(~10))
/* XXX: more types, from ~11 - ~12 */
/* Integers have type == SVM_VALUE_TAG_NUM, doubles have type < SVM_VALUE_TAG_NUM */
#define SVM_VALUE_TAG_NUM      (UINT32_C(~13))

/** @brief Get the tag of a value
 * @note Values of type double will return a value < SVM_VALUE_TAG_NUM
 */
static inline uint32_t svm_value_tag(const svm_value_t *x) __attribute__((__nonnull__(1)));

/** @section Value predicates */
/** @brief Determine if a value is nil */
static inline bool svm_value_is_nil(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is true */
static inline bool svm_value_is_true(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is false */
static inline bool svm_value_is_false(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is a boolean */
static inline bool svm_value_is_bool(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is a string */
static inline bool svm_value_is_string(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is a function */
static inline bool svm_value_is_function(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is a closure */
static inline bool svm_value_is_closure(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is a table */
static inline bool svm_value_is_table(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is a sequence */
static inline bool svm_value_is_sequence(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is a block */
static inline bool svm_value_is_block(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is an integer */
static inline bool svm_value_is_int(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is a double */
static inline bool svm_value_is_double(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is an integer or double */
static inline bool svm_value_is_number(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is truthy */
static inline bool svm_value_is_truthy(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is NaN */
static inline bool svm_value_is_nan(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is zero */
static inline bool svm_value_is_zero(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Determine if a value is garbage-collected */
static inline bool svm_value_is_gc(const svm_value_t *x) __attribute__((__nonnull__(1)));

/** @section Value setters */
/** @brief Set the value's tag */
static inline void svm_value_set_tag(svm_value_t *x, uint32_t tag) __attribute__((__nonnull__(1)));
/** @brief Set the value's tag to SVM_VALUE_TAG_NIL */
static inline void svm_value_set_nil(svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Set the value to the boolean */
static inline void svm_value_set_bool(svm_value_t *x, bool b) __attribute__((__nonnull__(1)));
/** @brief Set the value to the double */
static inline void svm_value_set_double(svm_value_t *x, double n) __attribute__((__nonnull__(1)));
/** @brief Set the value to the integer */
static inline void svm_value_set_int(svm_value_t *x, int32_t n) __attribute__((__nonnull__(1)));
/** @brief Set the value to NaN */
static inline void svm_value_set_nan(svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Set the value to the string */
static inline void svm_value_set_string(svm_value_t *x, svm_string_t *str) __attribute__((__nonnull__(1)));
/** @brief Set the value to the function */
static inline void svm_value_set_function(svm_value_t *x, svm_function_t *str) __attribute__((__nonnull__(1)));
/** @brief Set the value to the closure */
static inline void svm_value_set_closure(svm_value_t *x, svm_closure_t *str) __attribute__((__nonnull__(1)));
/** @brief Set the value to the table */
static inline void svm_value_set_table(svm_value_t *x, svm_table_t *str) __attribute__((__nonnull__(1)));
/** @brief Set the value to the sequence */
static inline void svm_value_set_sequence(svm_value_t *x, svm_sequence_t *str) __attribute__((__nonnull__(1)));
/** @brief Set the value to the block */
static inline void svm_value_set_block(svm_value_t *x, svm_block_t *str) __attribute__((__nonnull__(1)));

/** @section Value getters */
/** @brief Get the value of a boolean */
static inline bool svm_value_get_bool(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Get the value of a double */
static inline double svm_value_get_double(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Get the value of an integer */
static inline int32_t svm_value_get_int(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Get the value of a string */
static inline svm_string_t *svm_value_get_string(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Get the value of a function */
static inline svm_function_t *svm_value_get_function(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Get the value of a closure */
static inline svm_closure_t *svm_value_get_closure(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Get the value of a table */
static inline svm_table_t *svm_value_get_table(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Get the value of a sequence */
static inline svm_sequence_t *svm_value_get_sequence(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Get the value of a block */
static inline svm_block_t *svm_value_get_block(const svm_value_t *x) __attribute__((__nonnull__(1)));
/** @brief Get the header of a gc value */
static inline svm_gcheader_t *svm_value_get_gc(const svm_value_t *x) __attribute__((__nonnull__(1)));

/** @section GC Header */
/** @brief Get the next GC object in the chain */
static inline svm_gcheader_t *svm_gcheader_next(const svm_gcheader_t *gch) __attribute__((__nonnull__(1)));
/** @brief Set the next GC object in the chain */
static inline void svm_gcheader_set_next(svm_gcheader_t *gch, svm_gcheader_t *next) __attribute__((__nonnull__(1)));
/** @brief Determine is the GC object is marked */
static inline bool svm_gcheader_marked(const svm_gcheader_t *gch) __attribute__((__nonnull__(1)));
/** @brief Mark the GC object */
static inline void svm_gcheader_mark(svm_gcheader_t *gch) __attribute__((__nonnull__(1)));
/** @brief Unmark the GC object */
static inline void svm_gcheader_unmark(svm_gcheader_t *gch) __attribute__((__nonnull__(1)));

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

union svm_value_t {
    int64_t  _asInt64;
    uint64_t _asUInt64;
    double   _asDouble;
    struct {
        SVM_ENDIAN_LOHI(int32_t _lo;, uint32_t _hi;)
    } _asUInt32;
};

/* We use the same NaN encoding as LuaJIT:
 *   Prims   { 1..1 itype 1..1
 *   Integer { 1..1 itype 0..0 int
 *   Table   { 1..1 itype pointer
 *   qNaN    { 1..1 0..0
 *   Double  { ****:****:****:****
 *
 */

static inline uint32_t svm_value_tag(const svm_value_t *x) {
    return x->_asInt64 >> 47;
}
static inline bool svm_value_is_nil(const svm_value_t *x) {
    return x->_asInt64 == -1;
}
static inline bool svm_value_is_true(const svm_value_t *x) {
    return svm_value_tag(x) == SVM_VALUE_TAG_TRUE;
}
static inline bool svm_value_is_false(const svm_value_t *x) {
    return svm_value_tag(x) == SVM_VALUE_TAG_FALSE;
}
static inline bool svm_value_is_bool(const svm_value_t *x) {
    return svm_value_is_true(x) || svm_value_is_false(x);
}
static inline bool svm_value_is_string(const svm_value_t *x) {
    return svm_value_tag(x) == SVM_VALUE_TAG_STRING;
}
static inline bool svm_value_is_function(const svm_value_t *x) {
    return svm_value_tag(x) == SVM_VALUE_TAG_FUNCTION;
}
static inline bool svm_value_is_closure(const svm_value_t *x) {
    return svm_value_tag(x) == SVM_VALUE_TAG_CLOSURE;
}
static inline bool svm_value_is_table(const svm_value_t *x) {
    return svm_value_tag(x) == SVM_VALUE_TAG_TABLE;
}
static inline bool svm_value_is_sequence(const svm_value_t *x) {
    return svm_value_tag(x) == SVM_VALUE_TAG_SEQUENCE;
}
static inline bool svm_value_is_block(const svm_value_t *x) {
    return svm_value_tag(x) == SVM_VALUE_TAG_BLOCK;
}
static inline bool svm_value_is_int(const svm_value_t *x) {
    return svm_value_tag(x) == SVM_VALUE_TAG_NUM;
}
static inline bool svm_value_is_double(const svm_value_t *x) {
    return svm_value_tag(x) < SVM_VALUE_TAG_NUM;
}
static inline bool svm_value_is_number(const svm_value_t *x) {
    return svm_value_tag(x) <= SVM_VALUE_TAG_NUM;
}
static inline bool svm_value_is_truthy(const svm_value_t *x) {
    return svm_value_tag(x) < SVM_VALUE_TAG_FALSE;
}
static inline bool svm_value_is_nan(const svm_value_t *x) {
    return x->_asDouble != x->_asDouble;
}
static inline bool svm_value_is_zero(const svm_value_t *x) {
    return (x->_asUInt64 << 1) == 0;
}
static inline bool svm_value_is_gc(const svm_value_t *x) {
    uint32_t gcv = SVM_VALUE_TAG_STRING + 1;
    return (svm_value_tag(x) - gcv) > (SVM_VALUE_TAG_NUM - gcv);
}

static inline void svm_value_set_tag(svm_value_t *x, uint32_t tag) {
    x->_asUInt32._hi = tag << 15;
}
static inline void svm_value_set_nil(svm_value_t *x) {
    x->_asInt64 = -1;
}
static inline void svm_value_set_bool(svm_value_t *x, bool b) {
    x->_asInt64 = (int64_t)~((uint64_t)((int)b + 1) << 47);
}
static inline void svm_value_set_double(svm_value_t *x, double n) {
    x->_asDouble = n;
}
static inline void svm_value_set_int(svm_value_t *x, int32_t n) {
    x->_asUInt32._lo = n;
    svm_value_set_tag(x, SVM_VALUE_TAG_NUM);
}
static inline void svm_value_set_nan(svm_value_t *x) {
    x->_asDouble = nan("0");
}
#if SVM_64
#  define svm__set_ptr(x, ptr, tag) \
    ((x)->_asUInt64 = (uint64_t)(ptr) | ((uint64_t)(tag) << 47))
#else
#  define svm__set_ptr(x, ptr, tag) \
    ((x)->_asUInt32._lo = (uint32_t)(ptr), svm_value_set_tag(x, tag))
#endif
static inline void svm_value_set_string(svm_value_t *x, svm_string_t *str) {
    svm__set_ptr(x, str, SVM_VALUE_TAG_STRING);
}
static inline void svm_value_set_function(svm_value_t *x, svm_function_t *str) {
    svm__set_ptr(x, str, SVM_VALUE_TAG_FUNCTION);
}
static inline void svm_value_set_closure(svm_value_t *x, svm_closure_t *str) {
    svm__set_ptr(x, str, SVM_VALUE_TAG_CLOSURE);
}
static inline void svm_value_set_table(svm_value_t *x, svm_table_t *str) {
    svm__set_ptr(x, str, SVM_VALUE_TAG_TABLE);
}
static inline void svm_value_set_sequence(svm_value_t *x, svm_sequence_t *str) {
    svm__set_ptr(x, str, SVM_VALUE_TAG_SEQUENCE);
}
static inline void svm_value_set_block(svm_value_t *x, svm_block_t *str) {
    svm__set_ptr(x, str, SVM_VALUE_TAG_BLOCK);
}
#undef svvm__set_ptr

static inline bool svm_value_get_bool(const svm_value_t *x) {
    svm_assert(svm_value_is_bool(x));
    return SVM_VALUE_TAG_FALSE - svm_value_tag(x);
}
static inline double svm_value_get_double(const svm_value_t *x) {
    svm_assert(svm_value_is_double(x));
    return x->_asDouble;
}
static inline int32_t svm_value_get_int(const svm_value_t *x) {
    svm_assert(svm_value_is_int(x));
    return x->_asUInt32._lo;
}
#if SVM_64
#  define svm__ptr_mask ((UINT64_C(1) << 47) - 1)
#  define svm__get_ptr(x) ((void *)((x)->_asUInt64 & svm__ptr_mask))
#else
#  define svm__get_ptr(x) ((void *)(uintptr_t)(x)->_asUInt32._lo)
#endif
static inline svm_string_t *svm_value_get_string(const svm_value_t *x) {
    svm_assert(svm_value_is_string(x));
    return svm__get_ptr(x);
}
static inline svm_function_t *svm_value_get_function(const svm_value_t *x) {
    svm_assert(svm_value_is_function(x));
    return svm__get_ptr(x);
}
static inline svm_closure_t *svm_value_get_closure(const svm_value_t *x) {
    svm_assert(svm_value_is_closure(x));
    return svm__get_ptr(x);
}
static inline svm_table_t *svm_value_get_table(const svm_value_t *x) {
    svm_assert(svm_value_is_table(x));
    return svm__get_ptr(x);
}
static inline svm_sequence_t *svm_value_get_sequence(const svm_value_t *x) {
    svm_assert(svm_value_is_sequence(x));
    return svm__get_ptr(x);
}
static inline svm_block_t *svm_value_get_block(const svm_value_t *x) {
    svm_assert(svm_value_is_block(x));
    return svm__get_ptr(x);
}
static inline svm_gcheader_t *svm_value_get_gc(const svm_value_t *x) {
    svm_assert(svm_value_is_gc(x));
    return svm__get_ptr(x);
}
#undef svm__ptr_mask
#undef svm__get_ptr

struct svm_gcheader_t { uintptr_t _next; };
static inline svm_gcheader_t *svm_gcheader_next(const svm_gcheader_t *gch) {
    return (void *)(gch->_next & ~1);
}
static inline void svm_gcheader_set_next(svm_gcheader_t *gch, svm_gcheader_t *next) {
    svm_assert(((uintptr_t)next & 1) == 0);
    gch->_next = (uintptr_t)next | (gch->_next & 1);
}
static inline bool svm_gcheader_marked(const svm_gcheader_t *gch) {
    return gch->_next & 1;
}
static inline void svm_gcheader_mark(svm_gcheader_t *gch) {
    gch->_next |= 1;
}
static inline void svm_gcheader_unmark(svm_gcheader_t *gch) {
    gch->_next &= ~1;
}

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

/** @section String */
struct svm_string_t {
    svm_gcheader_t gch;
    uint64_t length;
    uint64_t hash;
    uint8_t data[];
};

/** @section Function */
struct svm_function_t {
    svm_gcheader_t gch;
    uint16_t arity;
    uint16_t nregs;
    uint32_t instructions[];
};

/** @section Closure */
struct svm_closure_t {
    svm_gcheader_t gch;
    svm_function_t *f;
    uint16_t nslots;
    svm_value_t captured[];
};

/** @section Block */
struct svm_block_t {
    svm_gcheader_t gch;
    uintptr_t nslots;
    svm_value_t slots[];
};

/** @section Sequence */
struct svm_sequence_t {
    svm_gcheader_t gch;
    /* TODO */
};

/** @section Tables */
struct svm_table_t {
    svm_gcheader_t gch;
    /* TODO */
};

/** @section CFunc */
struct svm_cfunc_t {
    svm_gcheader_t gch;
    /* TODO */
};

/** @section CData */
struct svm_cdata_t {
    svm_gcheader_t gch;
    /* TODO */
};

#endif /* ifndef SVM_VALUE_H */

