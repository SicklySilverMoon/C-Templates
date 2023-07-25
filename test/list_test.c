//#define TEMPLATE_IS_IMPL //comment out this one and you also need to comment out `#define TEMPLATE_ISNT_STATIC 0` in list_test.h
#include "list_test.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

int int_compare(int* a, int* b, void* context) {
    if (*a > *b)
        return 1;
    else if (*a < *b)
        return -1;
    return 0;
}

void int_callback(int* val, void* context) {
    assert(*val >= *((int*) context));
    *((int*) context) = *val;
}

void list_test() {
    printf("List test\n");

    list$int$ int_list = create_list$int$();
    list$long_long$ long_long_list = create_list$long_long$();
    list$int_const$ int_const_list = create_list$int_const$();
    list___float___ float_list = create_list___float___();

    int_list.vtable->prepend(&int_list, 0);
    int_list.vtable->append(&int_list, 1);
    long_long_list.vtable->prepend(&long_long_list, 2LL);
    long_long_list.vtable->append(&long_long_list, 3LL);
    int_const_list.vtable->prepend(&int_const_list, 4);
    int_const_list.vtable->append(&int_const_list, 5);
    float_list.vtable->prepend(&float_list, 0.1f);
    float_list.vtable->append(&float_list, 1.0f);

    //some tests that append & prepend put it into a sane state
    assert(int_list.head == int_list.tail->prev);
    assert(int_list.tail == int_list.head->next);
    assert(int_list.head != int_list.tail);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);

    //value tests
    assert(int_list.head->value == 0);
    assert(int_list.tail->value == 1);
    assert(long_long_list.head->value == 2LL);
    assert(long_long_list.tail->value == 3LL);
    assert(int_const_list.head->value == 4);
    assert(int_const_list.tail->value == 5);
    assert(float_list.head->value == 0.1f);
    assert(float_list.tail->value == 1.0f);

    //append tests to check list middle consistency
    for (int i = 2; i < 5; i++)
        int_list.vtable->append(&int_list, i);

    assert(*int_list.vtable->get(&int_list, 3) == 3);
    assert(int_list.vtable->get_node(&int_list, 3) == int_list.head->next->next->next);
    assert(int_list.vtable->get_node(&int_list, 0) == int_list.tail->prev->prev->prev->prev);

    //Test adding in the middle
    int_list.vtable->add(&int_list, 3, -1);
//    for (size_t i = 0; i < int_list.size; i++)
//        printf("%zu : %d\n", i, *int_list.vtable->get(&int_list, i));
    list_node$int$* node = int_list.vtable->get_node(&int_list, 3);
    int_list.vtable->add_node(&int_list, node, -2);
    assert(node->value == -1);
    assert(*int_list.vtable->get(&int_list, 4) == -1);
    assert(node->prev->value == -2);
    assert(*int_list.vtable->get(&int_list, 3) == -2);
    assert(node->next->value == 3);
    assert(node->next->prev == node);
    assert(node->prev->next == node);
    assert(node->next->next->prev->prev == node); //Not even sure if these are needed or actually check anything
    assert(node->prev->prev->next->next == node);

    //Test removing in the middle
    int_list.vtable->remove(&int_list, 3);
    int_list.vtable->remove_node(&int_list, node);
    node = int_list.head;
    for (size_t i = 0; node != NULL; i++) {
        assert(node->value == i);
        node = node->next;
    }
    node = int_list.tail;
    for (size_t i = int_list.size - 1; node != NULL; i--) {
        assert(node->value == i);
        node = node->prev;
    }

    //Swap tests
    int_list.vtable->swap(&int_list, 0, int_list.size - 1);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    int_list.vtable->swap(&int_list, int_list.size - 1, 0);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);

    int_list.vtable->swap(&int_list, 3, 4);
    assert(*int_list.vtable->get(&int_list, 3) == 4);
    assert(*int_list.vtable->get(&int_list, 4) == 3);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    assert(int_list.tail->value == 3);

    int_list.vtable->swap(&int_list, 3, 4);
    assert(*int_list.vtable->get(&int_list, 3) == 3);
    assert(*int_list.vtable->get(&int_list, 4) == 4);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    assert(int_list.tail->value == 4);

    int_list.vtable->swap(&int_list, 4, 3);
    assert(*int_list.vtable->get(&int_list, 3) == 4);
    assert(*int_list.vtable->get(&int_list, 4) == 3);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    assert(int_list.tail->value == 3);

    int_list.vtable->swap(&int_list, 4, 3);
    assert(*int_list.vtable->get(&int_list, 3) == 3);
    assert(*int_list.vtable->get(&int_list, 4) == 4);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    assert(int_list.tail->value == 4);

    int_list.vtable->swap(&int_list, 0, 1);
    assert(*int_list.vtable->get(&int_list, 0) == 1);
    assert(*int_list.vtable->get(&int_list, 1) == 0);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    assert(int_list.head->value == 1);

    int_list.vtable->swap(&int_list, 0, 1);
    assert(*int_list.vtable->get(&int_list, 0) == 0);
    assert(*int_list.vtable->get(&int_list, 1) == 1);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    assert(int_list.head->value == 0);

    int_list.vtable->swap(&int_list, 1, 0);
    assert(*int_list.vtable->get(&int_list, 0) == 1);
    assert(*int_list.vtable->get(&int_list, 1) == 0);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    assert(int_list.head->value == 1);

    int_list.vtable->swap(&int_list, 1, 0);
    assert(*int_list.vtable->get(&int_list, 0) == 0);
    assert(*int_list.vtable->get(&int_list, 1) == 1);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    assert(int_list.head->value == 0);

    //Test swap_node
    int_list.vtable->swap_node(&int_list, int_list.head, int_list.tail);
    assert(int_list.head->value == 4);
    assert(int_list.tail->value == 0);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);

    int_list.vtable->swap_node(&int_list, int_list.tail, int_list.head);
    assert(int_list.head->value == 0);
    assert(int_list.tail->value == 4);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);

    node = int_list.vtable->get_node(&int_list, 2);
    list_node$int$* node2 = int_list.vtable->get_node(&int_list, 3);
    int_list.vtable->swap_node(&int_list, node, node2);
    assert(*int_list.vtable->get(&int_list, 2) == 3);
    assert(*int_list.vtable->get(&int_list, 3) == 2);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);

    node = int_list.vtable->get_node(&int_list, 2);
    node2 = int_list.vtable->get_node(&int_list, 3);
    int_list.vtable->swap_node(&int_list, node, node2);
    assert(*int_list.vtable->get(&int_list, 2) == 2);
    assert(*int_list.vtable->get(&int_list, 3) == 3);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);

    //Test destroy and destroy_callback
    assert(int_list.size > 0);
    int_list.vtable->destroy(&int_list);
    assert(int_list.size == 0);

    for (size_t i = 0; i < 5000; i++) {
        int_list.vtable->append(&int_list, i);
    }
    assert(int_list.size == 5000);
    int_list.vtable->destroy(&int_list);
    assert(int_list.size == 0);

    for (size_t i = 0; i < 5000; i++) {
        int_list.vtable->append(&int_list, i);
    }
    assert(int_list.size == 5000);
    int prev = INT_MIN;
    int_list.vtable->destroy_callback(&int_list, int_callback, &prev);
    assert(int_list.size == 0);

    //test sort
    int_list.vtable->append(&int_list, 3);
    int_list.vtable->append(&int_list, 5);
    int_list.vtable->append(&int_list, 1);
    int_list.vtable->append(&int_list, 0);
    int_list.vtable->append(&int_list, 4);
    int_list.vtable->append(&int_list, 2);

    int_list.vtable->sort(&int_list, int_compare, NULL);
    assert(int_list.head->prev == NULL);
    assert(int_list.tail->next == NULL);
    for (size_t i = 0; i < int_list.size; i++) {
        assert(*int_list.vtable->get(&int_list, i) == i);
    }
    prev = INT_MIN;
    int_list.vtable->destroy_callback(&int_list, int_callback, &prev);
    assert(int_list.size == 0);

    assert(int_list.head == NULL);
    assert(int_list.tail == NULL);
    int_list.vtable->sort(&int_list, int_compare, NULL); //just ensure sorting an empty list doesn't crash
    assert(int_list.size == 0);
    assert(int_list.head == NULL);
    assert(int_list.tail == NULL);

    for (size_t i = 0; i < 10; i++) {
        int_list.vtable->append(&int_list, 9 - i);
//        printf("%d, ", int_list.tail->value);
    }
    int_list.vtable->sort(&int_list, int_compare, NULL);
    prev = INT_MIN;
    int_list.vtable->destroy_callback(&int_list, int_callback, &prev);
    assert(int_list.size == 0);

    unsigned seed = time(NULL);
//    unsigned seed = 1679713952;
//    printf("seed: %d\n", seed);
    srand(seed);
    for (size_t i = 0; i < 500; i++) {
        int_list.vtable->append(&int_list, rand() % 1000);
//        printf("%d, ", int_list.tail->value);
    }
    int_list.vtable->sort(&int_list, int_compare, NULL);
    prev = INT_MIN;
    int_list.vtable->destroy_callback(&int_list, int_callback, &prev);
    assert(int_list.size == 0);

    for (size_t i = 0; i < 500; i++) {
        for (size_t j = 0; j < 10; j++) {
            int_list.vtable->append(&int_list, rand() % 500);
        }
    }
    int_list.vtable->sort(&int_list, int_compare, NULL);
    prev = INT_MIN;
    int_list.vtable->destroy_callback(&int_list, int_callback, &prev);
    assert(int_list.size == 0);
}
