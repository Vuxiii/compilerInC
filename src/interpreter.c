#include "interpreter.h"
#include "context.h"
#include "include/library.h"

void interpret( struct Runtime *runtime, struct Context *context ) {
    for (unsigned int i = 0; i < context->instruction_index; ++i) {
        struct ASM_Instruction *instruction = &context->ASM_INSTRUCTION_BUFFER[i];
        switch (instruction->instr) {
            case INSTR_MOVE: {
                print( str_from_cstr("Interpreter: MOVE\n"));
                switch (instruction->from_mode) {
                    case IMMEDIATE: {
                        switch (instruction->to_mode) {
                            case IMMEDIATE:{
                                print( str_from_cstr("Error: (Interpreter) Tried to move immediate value into immediate value\n"));
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
                                print(str_from_cstr("Error: (Interpreter) Tried to move register into immediate value\n"));
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
                print( str_from_cstr("Interpreter: ADD\n"));

            } break;
            case INSTR_SUB: {
                print( str_from_cstr("Interpreter: SUB\n"));

            } break;
            case INSTR_IDIV: {
                print( str_from_cstr("Interpreter: IDIV\n"));

            } break;
            case INSTR_IMUL: {
                print( str_from_cstr("Interpreter: IMUL\n"));

            } break;
            case INSTR_LEA: {
                print( str_from_cstr("Interpreter: LEA\n"));

            } break;
            case INSTR_ENTER: {
                print( str_from_cstr("Interpreter: ENTER\n"));

            } break;
            case INSTR_LEAVE: {
                print( str_from_cstr("Interpreter: LEAVE\n"));

            } break;
            case INSTR_RET: {
                print( str_from_cstr("Interpreter: RET\n"));

            } break;
            case INSTR_CALL: {
                print( str_from_cstr("Interpreter: CALL\n"));

            } break;
            case INSTR_PUSH: {
                print( str_from_cstr("Interpreter: PUSH\n"));

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
                print( str_from_cstr("Interpreter: POP\n"));

            } break;
        }
    }
}

