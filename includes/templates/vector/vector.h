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
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(add)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE TEMPLATE_INTERNAL_func_name(remove)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx);
TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(swap)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx1, size_t idx2);
TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(destroy)(struct TEMPLATE_INTERNAL_FullName* vec);
TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(destroy_callback)(struct TEMPLATE_INTERNAL_FullName* vec, void (callback)(TEMPLATE_TYPE*));
TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(sort)(struct TEMPLATE_INTERNAL_FullName* vec, int (*comp)(TEMPLATE_TYPE*, TEMPLATE_TYPE*));

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
    if (vec->capacity >= new_size)
        return vec->arr;
    if (vec->capacity == 0) {
        *((TEMPLATE_TYPE**) &vec->arr) = malloc(2 * sizeof(TEMPLATE_TYPE));
        if (vec->arr == NULL)
            return NULL;
        *((size_t*) &vec->capacity) = 2;
    }

    TEMPLATE_TYPE* new_arr = realloc(vec->arr, new_size * sizeof(TEMPLATE_TYPE));
    if (new_arr != NULL)
        *((TEMPLATE_TYPE**) &vec->arr) = new_arr;
    return new_arr;
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(shrink_to_fit)(struct TEMPLATE_INTERNAL_FullName* vec) {
    if (vec->arr == NULL)
        return NULL;
    size_t new_size = vec->size;
    if (new_size == 0)
        new_size = 1; //Don't realloc to 0, UB in C23, stupid before

    TEMPLATE_TYPE* new_arr = realloc(vec->arr, new_size * sizeof(TEMPLATE_TYPE));
    if (new_arr != NULL)
        *((TEMPLATE_TYPE**) &vec->arr) = new_arr;
    return new_arr;
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(append)(struct TEMPLATE_INTERNAL_FullName* vec, TEMPLATE_TYPE value) {
    if (vec->arr == NULL)
        return NULL;
    //todo
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(prepend)(struct TEMPLATE_INTERNAL_FullName* vec, TEMPLATE_TYPE value) {
    if (vec->arr == NULL)
        return NULL;
    //todo
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(get)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx) {
    if (vec->arr == NULL || idx >= vec->size)
        return NULL;
    return &vec->arr[idx];
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(add)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx) {
    if (vec->arr == NULL || idx >= vec->size)
        return NULL;
    //todo:
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE TEMPLATE_INTERNAL_func_name(remove)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx) {
    //todo
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(swap)(struct TEMPLATE_INTERNAL_FullName* vec, size_t idx1, size_t idx2) {
    //todo
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(destroy)(struct TEMPLATE_INTERNAL_FullName* vec) {
    //todo
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(destroy_callback)(struct TEMPLATE_INTERNAL_FullName* vec, void (callback)(TEMPLATE_TYPE*)) {
    //todo
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(sort)(struct TEMPLATE_INTERNAL_FullName* vec, int (*comp)(TEMPLATE_TYPE*, TEMPLATE_TYPE*)) {
    //todo, just call qsort lmao
}


#endif

#include "../common_end.h"