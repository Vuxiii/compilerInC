#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "token.h"

struct Runtime {
    void *heap;
    long  heap_size;
    void *heap_ptr;

    void *stack;
    long  stack_size;
    
    
    /*
        [0] = rax
        [1] = rbx
        [2] = rcx
        [3] = rdx
        [4] = rsi
        [5] = rdi
        [6] = rbp
        [7] = rsp
        [8] = r8
        [9] = r9
        [a] = r10
        [b] = r11
        [c] = r12
        [d] = r13
        [e] = r14
        [f] = r15
    */
    long registers[16];
};

// MACROS FOR ACCESSING REGISTERS
#define RAX(runtime)                   (runtime->registers)[0]
#define EAX(runtime) (*     (int   *)&((runtime->registers)[0]))
#define AX(runtime)  (*     (short *)&((runtime->registers)[0]))
#define AH(runtime)  (*(1 + (char  *)&((runtime->registers)[0])))
#define AL(runtime)  (*     (char  *)&((runtime->registers)[0]))

#define RBX(runtime)                   (runtime->registers)[1]
#define EBX(runtime) (*     (int   *)&((runtime->registers)[1]))
#define BX(runtime)  (*     (short *)&((runtime->registers)[1]))
#define BH(runtime)  (*(1 + (char  *)&((runtime->registers)[1])))
#define BL(runtime)  (*     (char  *)&((runtime->registers)[1]))

#define RCX(runtime)                   (runtime->registers)[2]
#define ECX(runtime) (*     (int   *)&((runtime->registers)[2]))
#define CX(runtime)  (*     (short *)&((runtime->registers)[2]))
#define CH(runtime)  (*(1 + (char  *)&((runtime->registers)[2])))
#define CL(runtime)  (*     (char  *)&((runtime->registers)[2]))

#define RDX(runtime)                   (runtime->registers)[3]
#define EDX(runtime) (*     (int   *)&((runtime->registers)[3]))
#define DX(runtime)  (*     (short *)&((runtime->registers)[3]))
#define DH(runtime)  (*(1 + (char  *)&((runtime->registers)[3])))
#define DL(runtime)  (*     (char  *)&((runtime->registers)[3]))

#define RSI(runtime)                   (runtime->registers)[4]
#define ESI(runtime) (*     (int   *)&((runtime->registers)[4]))
#define SI(runtime)  (*     (short *)&((runtime->registers)[4]))
#define SIL(runtime)  (*    (char  *)&((runtime->registers)[4]))

#define RDI(runtime)                   (runtime->registers)[5]
#define EDI(runtime) (*     (int   *)&((runtime->registers)[5]))
#define DI(runtime)  (*     (short *)&((runtime->registers)[5]))
#define DIL(runtime)  (*    (char  *)&((runtime->registers)[5]))

#define RBP(runtime)                  (runtime->registers)[6]
#define EBP(runtime) (*    (int   *)&((runtime->registers)[6]))
#define BP(runtime)  (*    (short *)&((runtime->registers)[6]))
#define BPL(runtime) (*    (char  *)&((runtime->registers)[6]))

#define RSP(runtime)                  (runtime->registers)[7]
#define ESP(runtime) (*    (int   *)&((runtime->registers)[7]))
#define SP(runtime)  (*    (short *)&((runtime->registers)[7]))
#define SPL(runtime) (*    (char  *)&((runtime->registers)[7]))

#define R8(runtime)                   (runtime->registers)[8]
#define R8D(runtime) (*    (int   *)&((runtime->registers)[8]))
#define R8W(runtime) (*    (short *)&((runtime->registers)[8]))
#define R8B(runtime) (*    (char  *)&((runtime->registers)[8]))

#define R9(runtime)                   (runtime->registers)[9]
#define R9D(runtime) (*    (int   *)&((runtime->registers)[9]))
#define R9W(runtime) (*    (short *)&((runtime->registers)[9]))
#define R9B(runtime) (*    (char  *)&((runtime->registers)[9]))

#define R10(runtime)                  (runtime->registers)[10]
#define R10D(runtime) (*   (int   *)&((runtime->registers)[10]))
#define R10W(runtime) (*   (short *)&((runtime->registers)[10]))
#define R10B(runtime) (*   (char  *)&((runtime->registers)[10]))

#define R11(runtime)                  (runtime->registers)[11]
#define R11D(runtime) (*   (int   *)&((runtime->registers)[11]))
#define R11W(runtime) (*   (short *)&((runtime->registers)[11]))
#define R11B(runtime) (    (char  *)&((runtime->registers)[11]))

#define R12(runtime)                  (runtime->registers)[12]
#define R12D(runtime) (*   (int   *)&((runtime->registers)[12]))
#define R12W(runtime) (*   (short *)&((runtime->registers)[12]))
#define R12B(runtime) (*   (char  *)&((runtime->registers)[12]))

#define R13(runtime)                  (runtime->registers)[13]
#define R13D(runtime) (*   (int   *)&((runtime->registers)[13]))
#define R13W(runtime) (*   (short *)&((runtime->registers)[13]))
#define R13B(runtime) (*   (char  *)&((runtime->registers)[13]))

#define R14(runtime)                  (runtime->registers)[14]
#define R14D(runtime) (*    (int   *)&((runtime->registers)[14]))
#define R14W(runtime) (*   (short *)&((runtime->registers)[14]))
#define R14B(runtime) (*   (char  *)&((runtime->registers)[14]))

#define R15(runtime)                  (runtime->registers)[15]
#define R15D(runtime) (*   (int   *)&((runtime->registers)[15]))
#define R15W(runtime) (*   (short *)&((runtime->registers)[15]))
#define R15B(runtime) (*   (char  *)&((runtime->registers)[15]))

#define PUSHQ(runtime, value) *(long *)((runtime)->stack + (++RSP(runtime))) = value;
#define POPQ(runtime, register) (register) = *(long *)((runtime)->stack + (RSP((runtime))))
#define ENTER(runtime, offset) PUSHQ((runtime), RBP(runtime));\
                               ADD(offset, RSP(runtime));\
                               MOVE(RSP(runtime), RBP(runtime))
#define LEAVE(runtime) MOVE(RBP(runtime), RSP(runtime))
// #define RET(runtime) 
// #define CALL(runtime, function)
#define MOVE(from, to) (to) = (from)
#define ADD(from, to) (to) = (to) + (from)
#define SUB(from, to) (to) = (to) - (from)
#define MUL(runtime, reg) RAX(runtime) = RAX(runtime) * (reg);\
                          RDX(runtime) = RAX(runtime) % (reg)
#define XOR(from, to) (to) = (to) ^ (from)
#define OR(from, to) (to) = (to) | (from)
#define AND(from, to) (to) = (to) & (from)
 
#define LEA(from, to) (to) = &(from)
#define OFFSET(value, reg, type) *(type *)(((char *)&(reg)) + value)

void interpret( struct Runtime *runtime, struct Node *node );

void interpret_statement( struct Runtime *runtime, struct Node *some_statement );

#endif
