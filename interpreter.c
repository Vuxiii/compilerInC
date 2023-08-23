#include "interpreter.h"
#include "context.h"
#include "string.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void interpret( struct Runtime *runtime, struct Context *context ) {
    for (unsigned int i = 0; i < context->instruction_index; ++i) {
        struct ASM_Instruction *instruction = &context->ASM_INSTRUCTION_BUFFER[i];
        switch (instruction->instr) {
            case INSTR_MOVE: {
                print_string(String( .str = "Interpreter: MOVE\n", .length = 18));
                switch (instruction->from_mode) {
                    case IMMEDIATE: {
                        switch (instruction->to_mode) {
                            case IMMEDIATE:{
                                print_string( String( .str = "Error: (Interpreter) Tried to move immediate value into immediate value\n", .length = 72 ) );
                            } break;
                            case RELATIVE_OFFSET:
                            case DIRECT_OFFSET:
                            case REGISTER: MOVQ(instruction->data, REG64(runtime, instruction->to_reg)); break;
                        }
                    } break;
                    case RELATIVE_OFFSET:
                    case DIRECT_OFFSET:
                    case REGISTER: {
                        switch (instruction->to_mode) {

                            case IMMEDIATE: {
                                print_string( String( .str = "Error: (Interpreter) Tried to move register into immediate value\n", .length = 65 ) );
                            } break;
                            case RELATIVE_OFFSET:
                            case DIRECT_OFFSET:
                            case REGISTER: {
                                MOVQ( REG64(runtime, instruction->from_reg), REG64(runtime, instruction->to_reg) );
                            } break;
                        }
                    } break;
                }

            } break;
            case INSTR_ADD: {
                print_string(String( .str = "Interpreter: ADD\n", .length = 17));

            } break;
            case INSTR_SUB: {
                print_string(String( .str = "Interpreter: SUB\n", .length = 17));

            } break;
            case INSTR_IDIV: {
                print_string(String( .str = "Interpreter: IDIV\n", .length = 18));

            } break;
            case INSTR_IMUL: {
                print_string(String( .str = "Interpreter: IMUL\n", .length = 18));

            } break;
            case INSTR_LEA: {
                print_string(String( .str = "Interpreter: LEA\n", .length = 17));

            } break;
            case INSTR_ENTER: {
                print_string(String( .str = "Interpreter: ENTER\n", .length = 19));

            } break;
            case INSTR_LEAVE: {
                print_string(String( .str = "Interpreter: LEAVE\n", .length = 19));

            } break;
            case INSTR_RET: {
                print_string(String( .str = "Interpreter: RET\n", .length = 17));

            } break;
            case INSTR_CALL: {
                print_string(String( .str = "Interpreter: CALL\n", .length = 18));

            } break;
            case INSTR_PUSH: {
                print_string(String( .str = "Interpreter: PUSH\n", .length = 18));

                switch (instruction->from_mode) {
                    case IMMEDIATE: {
                        // switch (a->from_size) {

                        // case BYTES_8: PUSHQ(runtime, a->data); break;
                        // case BYTES_4: PUSHQ(runtime, a->data); break;
                        // case BYTES_2: PUSHQ(runtime, a->data); break;
                        // case BYTES_1: PUSHQ(runtime, a->data); break;
                        // }
                        PUSHQ(runtime, instruction->data);
                    } break;
                    case RELATIVE_OFFSET: {

                    } break;
                    case DIRECT_OFFSET: {
                        int total_offset = instruction->offset * instruction->offset_size;
                        PUSHQ(runtime, OFFSET(total_offset, REG64(runtime, instruction->from_reg), int64_t));
                    } break;
                    case REGISTER: {
                        PUSHQ(runtime, REG64(runtime, instruction->from_reg));
                    } break;
                }

            } break;
            case INSTR_POP: {
                print_string(String( .str = "Interpreter: POP\n", .length = 17));

            } break;
        }
    }
}

void print_stack( struct Runtime *runtime, int n ) {

    struct String *stk = String( .str = "Stack [", .length = 7 );
    struct String *cls = String( .str = "]\t", .length = 2 );
    struct String *nl = String( .str = "\n", .length = 1 );

    int64_t rsp = RSP(runtime);

    for ( int i = 0; i < n && i + rsp < runtime->stack_size; ++i ) {
        print_string(stk);
        print_int(RSP(runtime) + i);
        print_string(cls);
        print_int( runtime->stack[ RSP(runtime) + i] );
        print_string(nl);
    }
}

void print_registers( struct Runtime *runtime ) {

    struct String *rax = String( .str = "rax ", .length = 4 );
    struct String *rbx = String( .str = "rbx ", .length = 4 );
    struct String *rcx = String( .str = "rcx ", .length = 4 );
    struct String *rdx = String( .str = "rdx ", .length = 4 );
    struct String *rsi = String( .str = "rsi ", .length = 4 );
    struct String *rdi = String( .str = "rdi ", .length = 4 );
    struct String *rsp = String( .str = "rsp ", .length = 4 );
    struct String *rbp = String( .str = "rbp ", .length = 4 );

    struct String *tab = String( .str = "\t", .length = 1 );
    struct String *nl  = String( .str = "\n", .length = 1 );


    print_string(rax);
    print_string(tab);
    print_int(RAX(runtime));
    print_string(nl);

    print_string(rbx);
    print_string(tab);
    print_int(RBX(runtime));
    print_string(nl);

    print_string(rcx);
    print_string(tab);
    print_int(RCX(runtime));
    print_string(nl);

    print_string(rdx);
    print_string(tab);
    print_int(RDX(runtime));
    print_string(nl);


    print_string(rsi);
    print_string(tab);
    print_int(RSI(runtime));
    print_string(nl);


    print_string(rdi);
    print_string(tab);
    print_int(RDI(runtime));
    print_string(nl);


    print_string(rsp);
    print_string(tab);
    print_int(RSP(runtime));
    print_string(nl);


    print_string(rbp);
    print_string(tab);
    print_int(RBP(runtime));
    print_string(nl);


}
