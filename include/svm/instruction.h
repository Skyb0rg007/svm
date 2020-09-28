/* vim: set ft=c: */
#ifndef SVM_INSTRUCTION_H
#define SVM_INSTRUCTION_H

#include <stdint.h>
#include <svm/assert.h>
#include <svm/value.h>
#include <svm/opcode.h>

static inline svm_opcode_t svm_instruction_opcode(uint32_t);
static inline uint8_t  svm_instruction_uX(uint32_t);
static inline uint8_t  svm_instruction_uY(uint32_t);
static inline uint8_t  svm_instruction_uZ(uint32_t);
static inline uint16_t svm_instruction_uXY(uint32_t);
static inline int32_t  svm_instruction_iXYZ(uint32_t);

static inline uint32_t svm_instruction_r0(svm_opcode_t);
static inline uint32_t svm_instruction_r1(svm_opcode_t, uint8_t);
static inline uint32_t svm_instruction_r2(svm_opcode_t, uint8_t, uint8_t);
static inline uint32_t svm_instruction_r3(svm_opcode_t, uint8_t, uint8_t, uint8_t);
static inline uint32_t svm_instruction_r1u16(svm_opcode_t, uint8_t, uint16_t);
static inline uint32_t svm_instruction_r0i24(svm_opcode_t, int32_t);

/*****************************************************************************/

static inline svm_opcode_t svm_instruction_opcode(uint32_t i) {
    return i >> 24;
}
static inline uint8_t svm_instruction_uX(uint32_t i) {
    return (i >> 16) & 0xff;
}
static inline uint8_t svm_instruction_uY(uint32_t i) {
    return (i >> 8) & 0xff;
}
static inline uint8_t svm_instruction_uZ(uint32_t i) {
    return i & 0xff;
}
static inline uint16_t svm_instruction_uXY(uint32_t i) {
    return i & 0xffff;
}
static inline int32_t svm_instruction_iXYZ(uint32_t i) {
    return (int32_t)i & 0xffffff;
}

static inline uint32_t svm_instruction_r0(svm_opcode_t op) {
    return svm_instruction_r3(op, 0, 0, 0);
}
static inline uint32_t svm_instruction_r1(svm_opcode_t op, uint8_t x) {
    return svm_instruction_r3(op, x, 0, 0);
}
static inline uint32_t svm_instruction_r2(svm_opcode_t op, uint8_t x, uint8_t y) {
    return svm_instruction_r3(op, x, y, 0);
}
static inline uint32_t svm_instruction_r3(svm_opcode_t op, uint8_t x, uint8_t y, uint8_t z) {
    svm_assert(op >= 0 && op < SVM_NUM_OPCODES);
    return ((uint32_t)op << 24) | ((uint32_t)x << 16) | ((uint32_t)y << 8) | (uint32_t)z;
}
static inline uint32_t svm_instruction_r1u16(svm_opcode_t op, uint8_t x, uint16_t yz) {
    svm_assert(op >= 0 && op < SVM_NUM_OPCODES);
    return ((uint32_t)op << 24) | ((uint32_t)x << 16) | (uint32_t)yz;
}
static inline uint32_t svm_instruction_r0i24(svm_opcode_t op, int32_t xyz) {
    svm_assert(op >= 0 && op < SVM_NUM_OPCODES);
    svm_assert((xyz & 0xff000000) == 0);
    return ((uint32_t)op << 24) | (uint32_t)xyz;
}

#endif /* ifndef SVM_INSTRUCTION_H */
