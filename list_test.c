//#define TEMPLATE_IS_IMPL //comment out this one and you also need to comment out `#define TEMPLATE_ISNT_STATIC 0` in list_test.h
#include "list_test.h"

#include <assert.h>
#include <stdio.h>

int list_test() {
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
    node = int_list.vtable->get_node(&int_list, 3);
    //todo: check that the path is consistent

    //todo: test swap


    //todo: test destroy and destroy_callback

    //todo: test sort
    return 0;
}
