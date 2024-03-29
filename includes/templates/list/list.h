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
struct TEMPLATE_INTERNAL_FullName;

//Prototypes for "free" func
TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_FullName TEMPLATE_INTERNAL_PREFIX_CAT(create_)(void);

//Prototypes for vtable funcs
//todo: see if you can't pull more macro trickery like `#define TEMPLATE_COMPARE` as some function and use that for sorting if present
// falling back to the standard comparison ops if not
TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_func_name(append)(struct TEMPLATE_INTERNAL_FullName* list, TEMPLATE_TYPE value);
TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_func_name(prepend)(struct TEMPLATE_INTERNAL_FullName* list, TEMPLATE_TYPE value);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE*                                 TEMPLATE_INTERNAL_func_name(get)(struct TEMPLATE_INTERNAL_FullName* list, size_t target_idx);
TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_func_name(get_node)(struct TEMPLATE_INTERNAL_FullName* list, size_t target_idx);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE*                                 TEMPLATE_INTERNAL_func_name(add)(struct TEMPLATE_INTERNAL_FullName* list, size_t target_idx, TEMPLATE_TYPE value);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE*                                 TEMPLATE_INTERNAL_func_name(add_node)(struct TEMPLATE_INTERNAL_FullName* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node, TEMPLATE_TYPE value);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE                                  TEMPLATE_INTERNAL_func_name(remove)(struct TEMPLATE_INTERNAL_FullName* list, size_t target_idx);
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE                                  TEMPLATE_INTERNAL_func_name(remove_node)(struct TEMPLATE_INTERNAL_FullName* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node);
TEMPLATE_INTERNAL_staticish void                                           TEMPLATE_INTERNAL_func_name(swap)(struct TEMPLATE_INTERNAL_FullName* list, size_t target1, size_t target2);
TEMPLATE_INTERNAL_staticish void                                           TEMPLATE_INTERNAL_func_name(swap_node)(struct TEMPLATE_INTERNAL_FullName* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* n1, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* n2);
TEMPLATE_INTERNAL_staticish void                                           TEMPLATE_INTERNAL_func_name(destroy)(struct TEMPLATE_INTERNAL_FullName* list);
TEMPLATE_INTERNAL_staticish void                                           TEMPLATE_INTERNAL_func_name(destroy_callback)(struct TEMPLATE_INTERNAL_FullName* list, void (callback)(TEMPLATE_TYPE*, void*), void* callContext);
TEMPLATE_INTERNAL_staticish void                                           TEMPLATE_INTERNAL_func_name(sort)(struct TEMPLATE_INTERNAL_FullName* list, int (*comp)(TEMPLATE_TYPE*, TEMPLATE_TYPE*));

//vtable
TEMPLATE_INTERNAL_externish struct {
    typeof(TEMPLATE_INTERNAL_func_name(append))* const append;
    typeof(TEMPLATE_INTERNAL_func_name(prepend))* const prepend;
    typeof(TEMPLATE_INTERNAL_func_name(get))* const get;
    typeof(TEMPLATE_INTERNAL_func_name(get_node))* const get_node;
    typeof(TEMPLATE_INTERNAL_func_name(add))* const add;
    typeof(TEMPLATE_INTERNAL_func_name(add_node))* const add_node;
    typeof(TEMPLATE_INTERNAL_func_name(remove))* const remove;
    typeof(TEMPLATE_INTERNAL_func_name(remove_node))* const remove_node;
    typeof(TEMPLATE_INTERNAL_func_name(swap))* const swap;
    typeof(TEMPLATE_INTERNAL_func_name(swap_node))* const swap_node;
    typeof(TEMPLATE_INTERNAL_func_name(destroy))* const destroy;
    typeof(TEMPLATE_INTERNAL_func_name(destroy_callback))* const destroy_callback;
    typeof(TEMPLATE_INTERNAL_func_name(sort))* const sort;
} const TEMPLATE_INTERNAL_vTable
#if defined(TEMPLATE_IS_IMPL) || !defined(TEMPLATE_ISNT_STATIC)
     = {TEMPLATE_INTERNAL_func_name(append), TEMPLATE_INTERNAL_func_name(prepend),
                TEMPLATE_INTERNAL_func_name(get), TEMPLATE_INTERNAL_func_name(get_node),
                TEMPLATE_INTERNAL_func_name(add), TEMPLATE_INTERNAL_func_name(add_node),
                TEMPLATE_INTERNAL_func_name(remove), TEMPLATE_INTERNAL_func_name(remove_node),
                TEMPLATE_INTERNAL_func_name(swap), TEMPLATE_INTERNAL_func_name(swap_node),
                TEMPLATE_INTERNAL_func_name(destroy), TEMPLATE_INTERNAL_func_name(destroy_callback),
                TEMPLATE_INTERNAL_func_name(sort),
                    };
#else
;
#endif

//Actual list_node type
typedef struct TEMPLATE_INTERNAL_SHORT_CAT(list_node) {
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* const prev;
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* const next;
    TEMPLATE_TYPE value;
} TEMPLATE_INTERNAL_SHORT_CAT(list_node);

//Actual list type
typedef struct TEMPLATE_INTERNAL_FullName {
    size_t const size;
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* const head;
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* const tail;
    typeof(TEMPLATE_INTERNAL_vTable) const* const vtable; //typeof is standard in C2X and supported widely before
} TEMPLATE_INTERNAL_FullName;

//Function implementations
//Yup, in a header
#if defined(TEMPLATE_IS_IMPL) || !defined(TEMPLATE_ISNT_STATIC)
TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_FullName TEMPLATE_INTERNAL_PREFIX_CAT(create_)(void) { //this is NOT in the vtable for obvious reasons
    TEMPLATE_INTERNAL_FullName list = {.size = 0, .vtable = &TEMPLATE_INTERNAL_vTable};

    return list;
}

//memcpy and pointer cast into an allocated struct like this is legal as the const modification rule only applies to objects *defined* as const,
//and modifying the mem of the struct, which is NOT const defined, is legal C17[6.7.3/6] (and sets effective type C17[6.5/6]).
TEMPLATE_INTERNAL_staticish TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_func_name(make_node)(TEMPLATE_TYPE value) { //NOT a user visible func (ideally), internal use only really (users can usually see it though)
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = calloc(1, sizeof(TEMPLATE_INTERNAL_SHORT_CAT(list_node)));
    if (!node)
        return node;

    //Have to memcpy the value in cause the user might set the template type to a const type
    memcpy(((char*) node) + offsetof(TEMPLATE_INTERNAL_SHORT_CAT(list_node), value), &value, sizeof(value));

    return node;
}

TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_func_name(append)(struct TEMPLATE_INTERNAL_FullName* list, TEMPLATE_TYPE value) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = TEMPLATE_INTERNAL_func_name(make_node)(value);
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

TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_func_name(prepend)(struct TEMPLATE_INTERNAL_FullName* list, TEMPLATE_TYPE value) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = TEMPLATE_INTERNAL_func_name(make_node)(value);
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

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(get)(struct TEMPLATE_INTERNAL_FullName* list, size_t target_idx) {
    return &TEMPLATE_INTERNAL_func_name(get_node)(list, target_idx)->value;
}

TEMPLATE_INTERNAL_staticish struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_func_name(get_node)(struct TEMPLATE_INTERNAL_FullName* list, size_t target_idx) {
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

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(add)(struct TEMPLATE_INTERNAL_FullName* list, size_t target_idx, TEMPLATE_TYPE val) {
    return TEMPLATE_INTERNAL_func_name(add_node)(list, TEMPLATE_INTERNAL_func_name(get_node)(list, target_idx), val);
}

//adds BEFORE the current node
TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE* TEMPLATE_INTERNAL_func_name(add_node)(struct TEMPLATE_INTERNAL_FullName* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node, TEMPLATE_TYPE value) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* new_node = TEMPLATE_INTERNAL_func_name(make_node)(value);
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

    *((size_t*) &list->size) = list->size + 1;

    return &new_node->value;
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE TEMPLATE_INTERNAL_func_name(remove)(struct TEMPLATE_INTERNAL_FullName* list, size_t target_idx) {
    return TEMPLATE_INTERNAL_func_name(remove_node)(list, TEMPLATE_INTERNAL_func_name(get_node)(list, target_idx));
}

TEMPLATE_INTERNAL_staticish TEMPLATE_TYPE TEMPLATE_INTERNAL_func_name(remove_node)(struct TEMPLATE_INTERNAL_FullName* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node) {
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

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(swap)(struct TEMPLATE_INTERNAL_FullName* list, size_t target1, size_t target2) {
    if (target1 == target2)
        return;
    TEMPLATE_INTERNAL_func_name(swap_node)(list, TEMPLATE_INTERNAL_func_name(get_node)(list, target1), TEMPLATE_INTERNAL_func_name(get_node)(list, target2));
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(swap_node)(struct TEMPLATE_INTERNAL_FullName* list, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* n1, struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* n2) {
    if (n1 == NULL || n2 == NULL || n1 == n2)
        return;

    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* n1_prev;
    if (n1->prev != n2)
        n1_prev = n1->prev;
    else
        n1_prev = n1;
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* n1_next;
    if (n1->next != n2)
        n1_next = n1->next;
    else
        n1_next = n1;
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* n2_prev;
    if (n2->prev != n1)
        n2_prev = n2->prev;
    else
        n2_prev = n2;
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* n2_next;
    if (n2->next != n1)
        n2_next = n2->next;
    else
        n2_next = n2;


    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &n1->prev) = n2_prev;
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &n1->next) = n2_next;
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &n2->prev) = n1_prev;
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &n2->next) = n1_next;

    if (n1->prev != NULL) { //n2 was NOT head
        *((struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &n1->prev->next) = n1;
    } else {
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->head) = n1;
    }
    if (n1->next != NULL) { //n2 was NOT tail
        *((struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &n1->next->prev) = n1;
    } else {
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->tail) = n1;
    }

    if (n2->prev != NULL) { //n1 was NOT head
        *((struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &n2->prev->next) = n2;
    } else {
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->head) = n2;
    }
    if (n2->next != NULL) { //n1 was NOT tail
        *((struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &n2->next->prev) = n2;
    } else {
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->tail) = n2;
    }
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(destroy)(struct TEMPLATE_INTERNAL_FullName* list) {
    TEMPLATE_INTERNAL_func_name(destroy_callback)(list, NULL, NULL);
}

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(destroy_callback)(struct TEMPLATE_INTERNAL_FullName* list, void (callback)(TEMPLATE_TYPE*, void*), void* callContext) {
    struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* node = list->head;
    while (node) {
        struct TEMPLATE_INTERNAL_SHORT_CAT(list_node)* next = node->next;
        if (callback)
            callback(&node->value, callContext);
        free(node);
        node = next;
    }
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->head) = NULL;
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->tail) = NULL;
    *((size_t*) &list->size) = 0;
}

//https://en.wikipedia.org/wiki/Merge_sort#Bottom-up_implementation
//Thanks wikipedia
//todo: also add a macro like TEMPLATE_COMPARE with values like 0 meaning it uses <, 1 >, 2 <=, 3 >=, etc. and if not defined then require passing of a comp function
TEMPLATE_INTERNAL_staticish TEMPLATE_INTERNAL_SHORT_CAT(list_node)* TEMPLATE_INTERNAL_func_name(merge)(TEMPLATE_INTERNAL_SHORT_CAT(list_node)* left, TEMPLATE_INTERNAL_SHORT_CAT(list_node)* right, int (*comp)(TEMPLATE_TYPE*, TEMPLATE_TYPE*)) {
    TEMPLATE_INTERNAL_SHORT_CAT(list_node) dummy = {0};
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* tail = &dummy;

    while (left != NULL && right != NULL) {
        if (comp(&left->value, &right->value) <= 0) {
            *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &tail->next) = left;
            *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &left->prev) = tail;
            left = left->next;
        } else {
            *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &tail->next) = right;
            *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &right->prev) = tail;
            right = right->next;
        }
        tail = tail->next;
    }

    if (left != NULL) {
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &tail->next) = left;
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &left->prev) = tail;
    } else {
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &tail->next) = right;
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &right->prev) = tail;
    }

    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &dummy.next->prev) = NULL;
//    size_t jumps = 0;
//    while (tail->next != NULL) {
//        tail = tail->next;
//        jumps++;
//    }

//    struct TEMPLATE_INTERNAL_TYPE_NAME(sub_list) sub = {dummy.next, tail};
    return dummy.next;
}

//define it as either the bit width of size_t (new to C23) or bits in a byte * sizeof(size_t), most systems will have these equivalent anyway
#ifdef SIZE_WIDTH
    #define BOT_UP_ARR_SIZE (SIZE_WIDTH)
#else
    #define BOT_UP_ARR_SIZE (sizeof(size_t) * CHAR_BIT)
#endif

TEMPLATE_INTERNAL_staticish void TEMPLATE_INTERNAL_func_name(sort)(struct TEMPLATE_INTERNAL_FullName* list, int (*comp)(TEMPLATE_TYPE*, TEMPLATE_TYPE*)) {
    if (list->size <= 1) {
        return;
    }

    //"BOT_UP_ARR_SIZE constant assumes that your list has at most 2**BOT_UP_ARR_SIZE-1 nodes. (Given its based on size_t it's not actually possible to even hit this)
    //It splits the array up so that split[i] is always either empty or contains a sorted list of size 2**i."
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* split[BOT_UP_ARR_SIZE] = {NULL};
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* current;
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* head = list->head;

    while (head) {
        current = head;
        head = head->next;
        *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &current->next) = NULL;

        for (size_t i = 0; i < (sizeof(split) / sizeof(split[0])); i++) {
            if (split[i] == NULL) {
                split[i] = current;
                break;
            }
            current = TEMPLATE_INTERNAL_func_name(merge)(current, split[i], comp);
            split[i] = NULL;
        }
    }

    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* carry = NULL;
    for (size_t i = 0; i < (sizeof(split) / sizeof(split[0])); i++) {
        if (split[i] != NULL) {
            carry = TEMPLATE_INTERNAL_func_name(merge)(carry, split[i], comp);
        } else {
//            printf("split[%zu] is NULL\n", i);
        }
    }
    TEMPLATE_INTERNAL_SHORT_CAT(list_node)* tail = carry;
//    size_t jumps = 0;
    while (tail->next) {
        tail = tail->next;
//        jumps++;
    }

    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->head) = carry;
    *((TEMPLATE_INTERNAL_SHORT_CAT(list_node)**) &list->tail) = tail;
}
#endif

#include "../common_end.h"
