//See common_start.h for more info

#define TEMPLATE_INTERNAL_NAME vector
#include "../common_start.h"

struct TEMPLATE_INTERNAL_FullName;

//Prototypes for "free" func
TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_FullName TEMPLATE_INTERNAL_PREFIX_CAT(create_)(void);

//Prototypes for vtable funcs
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(reserve)(struct TEMPLATE_INTERNAL_FullName* vec, size_t new_size);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(shrink_to_fit)(struct TEMPLATE_INTERNAL_FullName* vec);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(append)(struct TEMPLATE_INTERNAL_FullName* vec, TEMPLATE_TYPE value);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(prepend)(struct TEMPLATE_INTERNAL_FullName* vec, TEMPLATE_TYPE value);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(get)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(add)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx, TEMPLATE_TYPE value);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE  TEMPLATE_INTERNAL_func_name(remove)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx);
TEMPLATE_INTERNAL_staticish void           TEMPLATE_INTERNAL_func_name(swap)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx1, size_t idx2);
TEMPLATE_INTERNAL_staticish void           TEMPLATE_INTERNAL_func_name(destroy)(struct TEMPLATE_INTERNAL_FullName* vec);
TEMPLATE_INTERNAL_staticish void           TEMPLATE_INTERNAL_func_name(destroy_callback)(struct TEMPLATE_INTERNAL_FullName* vec, void (callback)(TEMPLATE_TYPE*, void*), void* callContext);
TEMPLATE_INTERNAL_staticish void           TEMPLATE_INTERNAL_func_name(sort)(struct TEMPLATE_INTERNAL_FullName* vec, int (*comp)(void const*, void const*));

//vtable
TEMPLATE_INTERNAL_externish struct {
    typeof(TEMPLATE_INTERNAL_func_name(reserve))* const reserve;
    typeof(TEMPLATE_INTERNAL_func_name(shrink_to_fit))* const shrink_to_fit;
    typeof(TEMPLATE_INTERNAL_func_name(append))* const append;
    typeof(TEMPLATE_INTERNAL_func_name(prepend))* const prepend;
    typeof(TEMPLATE_INTERNAL_func_name(get))* const get;
    typeof(TEMPLATE_INTERNAL_func_name(add))* const add;
    typeof(TEMPLATE_INTERNAL_func_name(remove))* const remove;
    typeof(TEMPLATE_INTERNAL_func_name(swap))* const swap;
    typeof(TEMPLATE_INTERNAL_func_name(destroy))* const destroy;
    typeof(TEMPLATE_INTERNAL_func_name(destroy_callback))* const destroy_callback;
    typeof(TEMPLATE_INTERNAL_func_name(sort))* const sort;
} const TEMPLATE_INTERNAL_vTable
#if defined(TEMPLATE_IS_IMPL) || !defined(TEMPLATE_ISNT_STATIC)
    = {TEMPLATE_INTERNAL_func_name(reserve), TEMPLATE_INTERNAL_func_name(shrink_to_fit),
                TEMPLATE_INTERNAL_func_name(append), TEMPLATE_INTERNAL_func_name(prepend),
                TEMPLATE_INTERNAL_func_name(get), TEMPLATE_INTERNAL_func_name(add),
                TEMPLATE_INTERNAL_func_name(remove), TEMPLATE_INTERNAL_func_name(swap),
                TEMPLATE_INTERNAL_func_name(destroy), TEMPLATE_INTERNAL_func_name(destroy_callback),
                TEMPLATE_INTERNAL_func_name(sort),
                    };
#else
;
#endif

//Actual list type
typedef struct TEMPLATE_INTERNAL_FullName {
    size_t const size;
    size_t const capacity;
    TEMPLATE_TYPE* const arr;
    typeof(TEMPLATE_INTERNAL_vTable) const* const vtable; //typeof is standard in C2X and supported widely before
} TEMPLATE_INTERNAL_FullName;

//Function implementations
//Yup, in a header
#if defined(TEMPLATE_IS_IMPL) || !defined(TEMPLATE_ISNT_STATIC)
TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_FullName TEMPLATE_INTERNAL_PREFIX_CAT(create_)(void) {
    TEMPLATE_INTERNAL_FullName vec = {.size = 0, .capacity = 0, .arr = NULL, .vtable = &TEMPLATE_INTERNAL_vTable};
    return vec;
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(reserve)(struct TEMPLATE_INTERNAL_FullName* vec, size_t new_size) {
    if (new_size == 0)
        new_size = 2;
    if (vec->capacity >= new_size)
        return NULL;

    TEMPLATE_TYPE* new_arr;
    if (vec->capacity == 0) {
        new_arr = malloc(new_size * sizeof(TEMPLATE_TYPE));
    } else {
        new_arr = realloc(vec->arr, new_size * sizeof(TEMPLATE_TYPE));
    }
    if (new_arr != NULL)
        *((TEMPLATE_TYPE**) &vec->arr) = new_arr;
    *((size_t*) &vec->capacity) = new_size;
    return new_arr;
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(shrink_to_fit)(struct TEMPLATE_INTERNAL_FullName* vec) {
    if (vec->arr == NULL)
        return NULL;
    size_t new_size = vec->size;
    if (new_size == 0)
        new_size = 1; //Don't realloc to 0, UB in C23, stupid before

    TEMPLATE_TYPE* new_arr = realloc(vec->arr, new_size * sizeof(TEMPLATE_TYPE));
    if (new_arr != NULL) {
        *((TEMPLATE_TYPE**) &vec->arr) = new_arr;
        *((size_t*) &vec->capacity) = new_size;
    }
    return new_arr;
}

//todo: this (and other) funcs freak out if the type is const qualified (for obvious reasons)
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(append)(struct TEMPLATE_INTERNAL_FullName* vec, TEMPLATE_TYPE value) {
    if (vec->arr == NULL || vec->size + 1 > vec->capacity) {
        if (TEMPLATE_INTERNAL_func_name(reserve)(vec, vec->capacity * 2) == NULL)
            return NULL;
    }
    *((size_t*) &vec->size) = vec->size + 1;
    vec->arr[vec->size - 1] = value;
    return &vec->arr[vec->size - 1];
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(prepend)(struct TEMPLATE_INTERNAL_FullName* vec, TEMPLATE_TYPE value) {
    if (vec->arr == NULL || vec->size + 1 > vec->capacity) {
        if (TEMPLATE_INTERNAL_func_name(reserve)(vec, vec->capacity * 2) == NULL)
            return NULL;
    }
    memmove(vec->arr + 1, vec->arr, vec->size * sizeof(TEMPLATE_TYPE));
    *((size_t*) &vec->size) = vec->size + 1;
    vec->arr[0] = value;
    return &vec->arr[0];
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(get)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx) {
    if (vec->arr == NULL || idx >= vec->size)
        return NULL;
    return &vec->arr[idx];
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(add)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx, TEMPLATE_TYPE value) {
    if (idx == vec->size) //Special case to transform add past the last to append
        return TEMPLATE_INTERNAL_func_name(append)(vec, value);
    if (vec->arr == NULL || idx >= vec->size)
        return NULL;
    if (vec->size + 1 > vec->capacity) {
        if (TEMPLATE_INTERNAL_func_name(reserve)(vec, vec->capacity * 2) == NULL)
            return NULL;
    }
    memmove(vec->arr + idx + 1, vec->arr + idx, (vec->size - idx) * sizeof(TEMPLATE_TYPE));
    *((size_t*) &vec->size) = vec->size + 1;
    vec->arr[idx] = value;
    return &vec->arr[idx];
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE TEMPLATE_INTERNAL_func_name(remove)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx) {
//    if (vec->arr == NULL || idx >= vec->size) //todo: the inability to signal failure here is an issue, figure out what to return (or just make it UB to call w/ invalid params)
//        return NULL;
    TEMPLATE_TYPE val = vec->arr[idx];
    memmove(vec->arr + idx, vec->arr + idx + 1, (vec->size - idx - 1) * sizeof(TEMPLATE_TYPE));
    *((size_t*) &vec->size) = vec->size - 1;
    return val;
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(swap)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx1, size_t idx2) {
    if (vec->arr == NULL || idx1 >= vec->size || idx2 >= vec->size)
        return;
    TEMPLATE_TYPE temp = vec->arr[idx1];
    vec->arr[idx1] = vec->arr[idx2];
    vec->arr[idx2] = temp;
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(destroy)(struct TEMPLATE_INTERNAL_FullName* vec) {
    free(vec->arr);
    *((TEMPLATE_TYPE**) &vec->arr) = NULL;
    *((size_t*) &vec->size) = 0;
    *((size_t*) &vec->capacity) = 0;
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(destroy_callback)(struct TEMPLATE_INTERNAL_FullName* vec, void (callback)(TEMPLATE_TYPE*, void*), void* callContext) {
    for (size_t i = 0; i < vec->size; i++)
        callback(vec->arr + i, callContext);
    TEMPLATE_INTERNAL_func_name(destroy)(vec);
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(sort)(struct TEMPLATE_INTERNAL_FullName* vec, int (*comp)(void const*, void const*)) { //todo: also change list's comp to void pointers for consistency, and implement the same thing about a TEMPLATE_COMPARE macro
    qsort(vec->arr, vec->size, sizeof(TEMPLATE_TYPE), comp);
}


#endif

#include "../common_end.h"