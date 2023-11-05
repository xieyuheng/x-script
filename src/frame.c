#include "index.h"

struct _frame_t {
    size_t index;
    program_t *program;
};

frame_t *
frame_create(program_t *program) {
    frame_t *self = allocate(sizeof(frame_t));
    self->index = 0;
    self->program = program;
    return self;
}

void
frame_destroy(frame_t **self_ptr) {
    assert(self_ptr);
    if (*self_ptr) {
        frame_t *self = *self_ptr;
        free(self);
        *self_ptr = NULL;
    }
}

bool
frame_end_p(frame_t *self) {
    return self->index >= program_byte_size(self->program);
}

byte_t
frame_fetch_byte(frame_t *self) {
    byte_t byte = program_fetch_byte(self->program, self->index);
    self->index += sizeof(byte_t);
    return byte;
}

opcode_t
frame_fetch_opcode(frame_t *self) {
    return (opcode_t) frame_fetch_byte(self);
}

value_t
frame_fetch_value(frame_t *self) {
    value_t value = program_fetch_value(self->program, self->index);
    self->index += sizeof(value_t);
    return value;
}

word_t *
frame_fetch_word(frame_t *self) {
    word_t *word = program_fetch_word(self->program, self->index);
    self->index += sizeof(word_t *);
    return word;
}
