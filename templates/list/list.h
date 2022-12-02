//See common_start.h for more info

#define TEMPLATE_INTERNAL_NAME list
#include "../common_start.h"

//After including this header you can access the newly created list type via: `list$TEMPLATE_TYPE$`
//And you create an instance of one `create_list$TEMPLATE_TYPE$`
//ex. with int: `list$int$` & `create_list$int$`.

//todo: oh my god this thing requires docs BADLY, you can tell what's going on in here

//Declarations
struct TEMPLATE_INTERNAL_SHORT_CAT(list_node);
struct TEMPLATE_INTERNAL_FULL_NAME;

//Prototypes
//todo: get, pop_head, pop_tail (return the value and delete node, pick a better name), sort, remove at index, add at index, etc.
// a function that deletes the list and takes in a single argument function that the val is passed to
// (so lists holding pointers can have their pointers freed as the actual list is being freed)
// see if you can't pull more macro trickery like `#define TEMPLATE_COMPARE` as some function and use that for sorting if present
// falling back to the standard comparison ops if not
struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(append)(struct TEMPLATE_INTERNAL_FULL_NAME* list, TEMPLATE_TYPE value);
struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(prepend)(struct TEMPLATE_INTERNAL_FULL_NAME* list, TEMPLATE_TYPE value);

//vtable
struct {
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(append))* const append;
    typeof(TEMPLATE_INTERNAL_FUNC_NAME(append))* const prepend;
} const TEMPLATE_INTERNAL_VTABLE = {TEMPLATE_INTERNAL_FUNC_NAME(append), TEMPLATE_INTERNAL_FUNC_NAME(prepend)};

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

//Function implementations
//Yup, in a header
struct TEMPLATE_INTERNAL_FULL_NAME TEMPLATE_INTERNAL_PREFIX_CAT(create_)(void) {
    TEMPLATE_INTERNAL_FULL_NAME list = {.size = 1, .vtable = &TEMPLATE_INTERNAL_VTABLE};

    return list;
}

//memcpy into an allocated struct like this is legal as the const modification rule only applies to objects *defined* as const,
//and modifying the mem of the struct, which is NOT const defined, is legal C17[6.7.3/6] (and sets effective type C17[6.5/6])
struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(append)(struct TEMPLATE_INTERNAL_FULL_NAME* list, TEMPLATE_TYPE value) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = calloc(1, sizeof(TEMPLATE_INTERNAL_SHORT_CAT(list_node)));
    TEMPLATE_INTERNAL_SHORT_CAT(list_node) temp_node = (TEMPLATE_INTERNAL_SHORT_CAT(list_node)){.value = value, .prev = list->tail};

    if (!node)
        return node;
    memcpy(node, &temp_node, sizeof(temp_node));
    if (list->tail) {
        memcpy(((char*) list->tail) + offsetof(struct TEMPLATE_INTERNAL_SHORT_CAT(list_node), next), &node, sizeof(node));
    } else { //Empty list, want to make both head and tail the same
        memcpy(((char*) list) + offsetof(TEMPLATE_INTERNAL_FULL_NAME, head), &node, sizeof(node));
    }
    memcpy(((char*) list) + offsetof(TEMPLATE_INTERNAL_FULL_NAME, tail), &node, sizeof(node));

    size_t new_size = list->size + 1;
    memcpy(((char*) list) + offsetof(TEMPLATE_INTERNAL_FULL_NAME, size), &new_size, sizeof(new_size));

    return node;
}

struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_FUNC_NAME(prepend)(struct TEMPLATE_INTERNAL_FULL_NAME* list, TEMPLATE_TYPE value) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = calloc(1, sizeof(TEMPLATE_INTERNAL_SHORT_CAT(list_node)));
    TEMPLATE_INTERNAL_SHORT_CAT(list_node) temp_node = (TEMPLATE_INTERNAL_SHORT_CAT(list_node)){.value = value, .next = list->head};

    if (!node)
        return node;
    memcpy(node, &temp_node, sizeof(temp_node));
    if (list->head) {
        memcpy(((char*) list->head) + offsetof(struct TEMPLATE_INTERNAL_SHORT_CAT(list_node), prev), &node, sizeof(node));
    } else { //Empty list, want to make both head and tail the same
        memcpy(((char*) list) + offsetof(TEMPLATE_INTERNAL_FULL_NAME, tail), &node, sizeof(node));
    }
    memcpy(((char*) list) + offsetof(TEMPLATE_INTERNAL_FULL_NAME, head), &node, sizeof(node));

    size_t new_size = list->size + 1;
    memcpy(((char*) list) + offsetof(TEMPLATE_INTERNAL_FULL_NAME, size), &new_size, sizeof(new_size));

    return node;
}

#include "../common_end.h"
