#include "index.h"

void
execute(vm_t *vm, frame_t *frame) {
    if (frame_is_end(frame)) return;

    instruction_t instruction = frame_fetch_instruction(frame);
    if (instruction == CALL) {
        execute_call(vm, frame);
        return;
    } else if (
        instruction == LITERAL_INT ||
        instruction == LITERAL_STRING
        ) {
        execute_literal_value(vm, frame);
        return;
    } else {
        assert(false);
    }
}

void
execute_call(vm_t *vm, frame_t *frame) {
    word_t *word = frame_fetch_word(frame);
    vm_return_stack_push(vm, frame);

    primitive_t *primitive = word_primitive(word);
    if (primitive) {
        (*primitive)(vm);
        return;
    }

    program_t *program = word_program(word);
    if (program) {
        frame_t *new_frame = frame_create(program);
        vm_return_stack_push(vm, new_frame);
        return;
    }

    printf("[execute_call] word name: %s\n", word_name(word));
    assert(false);
}

void
execute_literal_value(vm_t *vm, frame_t *frame) {
    value_t value = frame_fetch_value(frame);
    vm_return_stack_push(vm, frame);
    vm_value_stack_push(vm, value);
}
