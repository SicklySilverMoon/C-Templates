//See common_start.h for more info

#define TEMPLATE_INTERNAL_NAME list
#include "../common_start.h"

//After including this header you can access the newly created list type via: `list$TEMPLATE_TYPE$`
//And you create an instance of one `create_list$TEMPLATE_TYPE$`
//ex. with int: `list$int$` & `create_list$int$`.

//todo: oh my god this thing requires docs BADLY, you can't tell what's going on in here
//code side this doesn't matter too much its not THAT bad once you understand it, user side, yeah this needs docs

//Declarations
struct TEMPLATE_INTERNAL_SHORT_CAT(list_node);
struct TEMPLATE_INTERNAL_FULL_NAME;

//Prototypes
//todo: sort, etc.
// a function that deletes the list and takes in a single argument function that the val is passed to
// (so lists holding pointers can have their pointers freed as the actual list is being freed)
// see if you can't pull more macro trickery like `#define TEMPLATE_COMPARE` as some function and use that for sorting if present
// falling back to the standard comparison ops if not
struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(append)(struct TEMPLATE_INTERNAL_FULL_NAME* list, TEMPLATE_TYPE value);
struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(prepend)(struct TEMPLATE_INTERNAL_FULL_NAME* list, TEMPLATE_TYPE value);
TEMPLATE_TYPE* TEMPLATE_INTERNAL_FUNC_NAME(get)(struct TEMPLATE_INTERNAL_FULL_NAME* list, size_t target_idx);
struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(get_node)(struct TEMPLATE_INTERNAL_FULL_NAME* list, size_t target_idx);
TEMPLATE_TYPE* TEMPLATE_INTERNAL_FUNC_NAME(add)(struct TEMPLATE_INTERNAL_FULL_NAME* list, size_t target_idx, TEMPLATE_TYPE value);
TEMPLATE_TYPE* TEMPLATE_INTERNAL_FUNC_NAME(add_node)(struct TEMPLATE_INTERNAL_FULL_NAME* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node, TEMPLATE_TYPE value);
TEMPLATE_TYPE TEMPLATE_INTERNAL_FUNC_NAME(remove)(struct TEMPLATE_INTERNAL_FULL_NAME* list, size_t target_idx);
TEMPLATE_TYPE TEMPLATE_INTERNAL_FUNC_NAME(remove_node)(struct TEMPLATE_INTERNAL_FULL_NAME* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node);
void TEMPLATE_INTERNAL_FUNC_NAME(destroy)(struct TEMPLATE_INTERNAL_FULL_NAME* list);
void TEMPLATE_INTERNAL_FUNC_NAME(destroy_callback)(struct TEMPLATE_INTERNAL_FULL_NAME* list, void (callback)(TEMPLATE_TYPE*));
void TEMPLATE_INTERNAL_FUNC_NAME(sort)(struct TEMPLATE_INTERNAL_FULL_NAME* list, int (*comp)(TEMPLATE_TYPE*, TEMPLATE_TYPE*));

//vtable
struct {
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(append))* const append;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(prepend))* const prepend;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(get))* const get;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(get_node))* const get_node;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(add))* const add;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(add_node))* const add_node;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(remove))* const remove;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(remove_node))* const remove_node;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(destroy))* const destroy;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(destroy_callback))* const destroy_callback;
//    typeof(TEMPLATE_INTERNAL_FUNC_NAME(sort))* const sort;
} const TEMPLATE_INTERNAL_VTABLE = {TEMPLATE_INTERNAL_FUNC_NAME(append), TEMPLATE_INTERNAL_FUNC_NAME(prepend),
                                    TEMPLATE_INTERNAL_FUNC_NAME(get), TEMPLATE_INTERNAL_FUNC_NAME(get_node),
                                    TEMPLATE_INTERNAL_FUNC_NAME(add), TEMPLATE_INTERNAL_FUNC_NAME(add_node),
                                    TEMPLATE_INTERNAL_FUNC_NAME(remove), TEMPLATE_INTERNAL_FUNC_NAME(remove_node),
                                    TEMPLATE_INTERNAL_FUNC_NAME(destroy), TEMPLATE_INTERNAL_FUNC_NAME(destroy_callback),
                                    };
//                                    TEMPLATE_INTERNAL_FUNC_NAME(sort),};

//Actual list_node type
typedef struct TEMPLATE_INTERNAL_SHORT_CAT(list_node) {
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* const prev;
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* const next;
    TEMPLATE_TYPE value;
} TEMPLATE_INTERNAL_SHORT_CAT(list_node);

//Actual list type
typedef struct TEMPLATE_INTERNAL_FULL_NAME {
    size_t const size;
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* const head;
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* const tail;
    typeof(TEMPLATE_INTERNAL_VTABLE) const* const vtable; //typeof is standard in C2X and supported widely before
} TEMPLATE_INTERNAL_FULL_NAME;

TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(make_node)(TEMPLATE_TYPE value) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = calloc(1, sizeof(TEMPLATE_INTERNAL_SHORT_CAT(list_node)));
    if (!node)
        return node;

    //Have to memcpy the value in cause the user might set the template type to a const type
    memcpy(((char*) node) + offsetof(TEMPLATE_INTERNAL_SHORT_CAT(list_node), value), &value, sizeof(value));

    return node;
}

//Function implementations
//Yup, in a header
struct TEMPLATE_INTERNAL_FULL_NAME TEMPLATE_INTERNAL_PREFIX_CAT(create_)(void) {
    TEMPLATE_INTERNAL_FULL_NAME list = {.size = 0, .vtable = &TEMPLATE_INTERNAL_VTABLE};

    return list;
}

//memcpy and pointer cast into an allocated struct like this is legal as the const modification rule only applies to objects *defined* as const,
//and modifying the mem of the struct, which is NOT const defined, is legal C17[6.7.3/6] (and sets effective type C17[6.5/6]).
struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(append)(struct TEMPLATE_INTERNAL_FULL_NAME* list, TEMPLATE_TYPE value) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = TEMPLATE_INTERNAL_FUNC_NAME(make_node)(value);
    if (!node)
        return node;

    *((struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &node->prev) = list->tail;

    if (list->tail) {
        *((struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->tail->next) = node;
    } else { //Empty list, want to make both head and tail the same
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->head) = node;
    }
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->tail) = node;

    *((size_t*) &list->size) = list->size + 1;

    return node;
}

struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(prepend)(struct TEMPLATE_INTERNAL_FULL_NAME* list, TEMPLATE_TYPE value) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = TEMPLATE_INTERNAL_FUNC_NAME(make_node)(value);
    if (!node)
        return node;

    *((struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &node->next) = list->head;

    if (list->head) {
        *((struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->head->prev) = node;
    } else { //Empty list, want to make both head and tail the same
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->tail) = node;
    }
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->head) = node;

    *((size_t*) &list->size) = list->size + 1;

    return node;
}

TEMPLATE_TYPE* TEMPLATE_INTERNAL_FUNC_NAME(get)(struct TEMPLATE_INTERNAL_FULL_NAME* list, size_t target_idx) {
    return &TEMPLATE_INTERNAL_FUNC_NAME(get_node)(list, target_idx)->value;
}

struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(get_node)(struct TEMPLATE_INTERNAL_FULL_NAME* list, size_t target_idx) {
    if (target_idx >= list->size)
        return NULL;

    size_t idx;
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node;
    if (list->size / 2 >= target_idx) {
        idx = 0;
        node = list->head;
        while (idx != target_idx) {
            idx++;
            node = node->next;
        }
        return node;
    } else {
        idx = list->size - 1;
        node = list->tail;
        while (idx != target_idx) {
            idx--;
            node = node->prev;
        }
        return node;
    }
}

TEMPLATE_TYPE* TEMPLATE_INTERNAL_FUNC_NAME(add)(struct TEMPLATE_INTERNAL_FULL_NAME* list, size_t target_idx, TEMPLATE_TYPE val) {
    return TEMPLATE_INTERNAL_FUNC_NAME(add_node)(list, TEMPLATE_INTERNAL_FUNC_NAME(get_node)(list, target_idx), val);
}

TEMPLATE_TYPE* TEMPLATE_INTERNAL_FUNC_NAME(add_node)(struct TEMPLATE_INTERNAL_FULL_NAME* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node, TEMPLATE_TYPE value) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* new_node = TEMPLATE_INTERNAL_FUNC_NAME(make_node)(value);
    if (!new_node)
        return NULL;

    if (node->prev) {
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &node->prev->next) = new_node;
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &new_node->prev) = node->prev;
    }
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &node->prev) = new_node;
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &new_node->next) = node;

    if (list->head == node) {
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->head) = new_node;
    }

    return &new_node->value;
}

TEMPLATE_TYPE TEMPLATE_INTERNAL_FUNC_NAME(remove)(struct TEMPLATE_INTERNAL_FULL_NAME* list, size_t target_idx) {
    return TEMPLATE_INTERNAL_FUNC_NAME(remove_node)(list, TEMPLATE_INTERNAL_FUNC_NAME(get_node)(list, target_idx));
}

TEMPLATE_TYPE TEMPLATE_INTERNAL_FUNC_NAME(remove_node)(struct TEMPLATE_INTERNAL_FULL_NAME* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node) {
    TEMPLATE_TYPE value = node->value;

    if (node->prev)
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &node->prev->next) = node->next;
    if (node->next)
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &node->next->prev) = node->prev;

    if (list->head == node)
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->head) = node->next;
    if (list->tail == node)
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->tail) = node->prev;
    *((size_t*) &list->size) = list->size - 1;

    free(node);
    return value;
}

void TEMPLATE_INTERNAL_FUNC_NAME(destroy)(struct TEMPLATE_INTERNAL_FULL_NAME* list) {
    TEMPLATE_INTERNAL_FUNC_NAME(destroy_callback)(list, NULL);
}

void TEMPLATE_INTERNAL_FUNC_NAME(destroy_callback)(struct TEMPLATE_INTERNAL_FULL_NAME* list, void (callback)(TEMPLATE_TYPE*)) {
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = list->head;
    while (node) {
        struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* next = node->next;
        if (callback)
            callback(&node->value);
        free(node);
        node = next;
    }
}

void TEMPLATE_INTERNAL_FUNC_NAME(sort)(struct TEMPLATE_INTERNAL_FULL_NAME* list, int (*comp)(TEMPLATE_TYPE*, TEMPLATE_TYPE*)) {
    //todo
}

#include "../common_end.h"
