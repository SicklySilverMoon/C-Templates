#include "vector_test.h"

#include <stdio.h>

#define loop_check(vec, end) \
    for (size_t i = 0; i < end; i++) { \
        int* valP = vec.vtable->get(&vec, i); \
        assert(valP != NULL); \
        assert(*valP == i); \
        assert(vec.arr[i] == i); \
    }

size_t callback_counter = 0;

static void callback_test(int* val) {
    assert(*val == callback_counter);
    callback_counter++;
}

void vector_test() {
    printf("Vector test\n");

    vector$int$ vectorInt = create_vector$int$();
    assert(vectorInt.size == 0);
    assert(vectorInt.arr == NULL);
    assert(vectorInt.capacity == 0);

    vectorInt.vtable->append(&vectorInt, 1);
    assert(vectorInt.size == 1);
    assert(vectorInt.capacity >= 1);
    assert(vectorInt.arr[0] == 1);
    vectorInt.vtable->prepend(&vectorInt, 0);
    assert(vectorInt.size == 2);
    assert(vectorInt.capacity >= 2);
    assert(vectorInt.arr[0] == 0);
    assert(vectorInt.arr[1] == 1);
    vectorInt.vtable->append(&vectorInt, 3);
    assert(vectorInt.size == 3);
    assert(vectorInt.capacity >= 3);
    assert(vectorInt.arr[0] == 0);
    assert(vectorInt.arr[1] == 1);
    assert(vectorInt.arr[2] == 3);

    assert(*vectorInt.vtable->get(&vectorInt, 0) == 0);
    assert(*vectorInt.vtable->get(&vectorInt, 1) == 1);

    vectorInt.vtable->add(&vectorInt, 2, 2);
    assert(vectorInt.size == 4);
    assert(vectorInt.capacity >= 4);
    loop_check(vectorInt, 4);

    vectorInt.vtable->add(&vectorInt, 4, 4); //test add -> append
    assert(vectorInt.size == 5);
    assert(vectorInt.capacity >= 5);
    loop_check(vectorInt, 5);

    for (int i = 0; i < 5; i++) {
        vectorInt.vtable->append(&vectorInt, i + 5);
    }
    loop_check(vectorInt, 10);

    for (ptrdiff_t i = vectorInt.size - 1; i >= 0; i--) {
        vectorInt.vtable->remove(&vectorInt, i);
        assert(vectorInt.size == i);
    }
    assert(vectorInt.size == 0);

    vectorInt.vtable->append(&vectorInt, 0);
    assert(vectorInt.size == 1);
    assert(vectorInt.capacity > 1);

    vectorInt.vtable->shrink_to_fit(&vectorInt);
    assert(vectorInt.size == 1);
    assert(vectorInt.capacity == 1);

    vectorInt.vtable->reserve(&vectorInt, 10);
    assert(vectorInt.size == 1);
    assert(vectorInt.capacity == 10);

    vectorInt.vtable->append(&vectorInt, 1);
    assert(vectorInt.size == 2);
    assert(vectorInt.capacity == 10);
    loop_check(vectorInt, 2);

    vectorInt.vtable->swap(&vectorInt, 0, 1);
    assert(vectorInt.size == 2);
    assert(vectorInt.capacity == 10);
    assert(vectorInt.arr[0] == 1);
    assert(vectorInt.arr[1] == 0);
    vectorInt.vtable->swap(&vectorInt, 1, 0);
    assert(vectorInt.size == 2);
    assert(vectorInt.capacity == 10);
    loop_check(vectorInt, 2);

    vectorInt.vtable->destroy(&vectorInt);
    assert(vectorInt.arr == NULL);
    assert(vectorInt.size == 0);
    assert(vectorInt.capacity == 0);
    assert(vectorInt.vtable != NULL);

    for (int i = 0; i < 10; i++) {
        vectorInt.vtable->append(&vectorInt, i);
    }
    loop_check(vectorInt, 10);
    vectorInt.vtable->destroy_callback(&vectorInt, callback_test);
    assert(vectorInt.arr == NULL);
    assert(vectorInt.size == 0);
    assert(vectorInt.capacity == 0);
    assert(vectorInt.vtable != NULL);
}