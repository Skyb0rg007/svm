/* vim: set ft=c: */
#ifndef SVM_OPCODE_H
#define SVM_OPCODE_H

typedef enum {
    SVM_OPCODE_HALT,        // R0    -- return;
    SVM_OPCODE_PRINT,       // R1    -- print(R(X))
    SVM_OPCODE_CHECK,       // R1LIT -- check(R(X), L(YZ))
    SVM_OPCODE_EXPECT,      // R1LIT -- expect(R(X), L(YZ))
    SVM_OPCODE_ADD,         // R3    -- R(X) := R(Y) + R(Z)
    SVM_OPCODE_LOADLITERAL, // R1LIT -- R(X) := L(YZ)
    SVM_OPCODE_GOTO,        // R0I24 -- ip += XYZ
    SVM_OPCODE_IF,          // R1    -- if (truthy(R(X))) { ip++; }
    SVM_OPCODE_GETGLOBAL,   // R1LIT -- R(X) := _G[LIT]
    SVM_OPCODE_SETGLOBAL,   // R1LIT -- _G[LIT] := R(X)
    SVM_OPCODE_DIVIDE,      // R3    -- R(X) := R(Y) / R(Z)
    SVM_OPCODE_SUBTRACT,    // R3    -- R(X) := R(Y) - R(Z)
    SVM_OPCODE_MULTIPLY,    // R3    -- R(X) := R(Y) * R(Z)
    SVM_OPCODE_ABS,         // R2    -- R(X) := |R(Y)|
    SVM_OPCODE_HASH,        // R2    -- R(X) := hash(R(Y))
    SVM_NUM_OPCODES,        // Number of opcodes
} svm_opcode_t;

#endif /* ifndef SVM_OPCODE_H */
