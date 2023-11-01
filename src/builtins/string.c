#include "../index.h"

void _string_print(xvm_t * vm) {
    char *s = (char *) xvm_value_stack_pop(vm);
    printf("%s", s);
    free(s);
}

void _string_dup(xvm_t * vm) {
    char *s = (char *) xvm_value_stack_pop(vm);
    xvm_value_stack_push(vm, (value_t) s);
    xvm_value_stack_push(vm, (value_t) string_dup(s));
}

void _string_length(xvm_t * vm) {
    char *s = (char *) xvm_value_stack_pop(vm);
    xvm_value_stack_push(vm, strlen(s));
    free(s);
}

void _string_append(xvm_t * vm) {
    char *first = (char *) xvm_value_stack_pop(vm);
    char *second = (char *) xvm_value_stack_pop(vm);
    size_t first_length = strlen(first);
    size_t second_length = strlen(second);
    char *result = malloc(first_length + second_length + 1);
    result[0] = '\0';
    strcat(result, second);
    strcat(result, first);
    free(first);
    free(second);
    xvm_value_stack_push(vm, (value_t) result);
}
