#include <stdio.h>

#include "types.h"

//Just an example for the provided template(s)
int main() {
    list$int$ int_list = create_list$int$();

    int_list.vtable->append(&int_list, 9);
    printf("%p: %d, %p: %d\n", int_list.head, int_list.head->value, int_list.tail, int_list.tail->value);

    int_list.vtable->append(&int_list, 10);
    printf("%p: %d, %p: %d\n", int_list.head, int_list.head->value, int_list.tail, int_list.tail->value);

    int_list.vtable->append(&int_list, 11);
    printf("%p: %d, %p: %d %p: %d\n", int_list.head, int_list.head->value, int_list.head->next, int_list.head->next->value, int_list.tail, int_list.tail->value);
    printf("int list size: %zu\n", int_list.size);

    printf("\n");
    list$int$ int_list2 = create_list$int$();

    int_list2.vtable->prepend(&int_list2, 9);
    printf("%p: %d, %p: %d\n", int_list2.tail, int_list2.tail->value, int_list2.head, int_list2.head->value);

    int_list2.vtable->prepend(&int_list2, 10);
    printf("%p: %d, %p: %d\n", int_list2.tail, int_list2.tail->value, int_list2.head, int_list2.head->value);

    int_list2.vtable->prepend(&int_list2, 11);
    printf("%p: %d, %p: %d %p: %d\n", int_list2.tail, int_list2.tail->value, int_list2.tail->prev, int_list2.tail->prev->value, int_list2.head, int_list2.head->value);
    printf("int list 2 size: %zu\n", int_list2.size);

    list$double$ double_list = create_list$double$();
    for (size_t i = 0; i < 100; i++) {
        double_list.vtable->append(&double_list, i / 10.0);
    }
    printf("\n\n");
//    list_node$double$* node = double_list.head;
//    while (node) {
//        printf("%p: %f\n", node, node->value);
//        node = node->next;
//    }
    printf("get tests:\n");
    printf("idx 4: %f\n", *double_list.vtable->get(&double_list, 4));
    printf("idx 95: %f\n", *double_list.vtable->get(&double_list, 95));

    double_list.vtable->remove(&double_list, 0);
    printf("\nremoval tests:\n");
    printf("idx 0: %f\n", double_list.head->value);
    printf("idx 98: %f\n", *double_list.vtable->get(&double_list, 98));

    printf("\nAdd tests:\n");
    printf("prev idx 0: %f\n", double_list.head->value);
    double_list.vtable->add(&double_list, 0, -1);
    printf("new  idx 0: %f\n\n", double_list.head->value);
    list_node$double$* double_node = double_list.vtable->get_node(&double_list, 17);
    printf("prev idx 17: %f\n", double_node->value);
    double_list.vtable->add_node(&double_list, double_node, -2);
    printf("new  idx 17: %f\n", *double_list.vtable->get(&double_list, 17));
    if ((double_list.vtable->get_node(&double_list, 17) != double_node->prev) || (double_list.vtable->get_node(&double_list, 17)->next != double_node)) {
        printf("ERROR: removal pointer consistency failure!");
    }

//    list_node$int$ int_node = {4, NULL};
//    printf("%d, %p\n", int_node.data, int_node.next);
//
//    list_node$long_long$ ll_node = {27LL, NULL};
//    printf("%lld, %p\n", ll_node.data, ll_node.next);
//
//    list_node$int_const$ int_const_node_2 = {2, NULL};
//    list_node$int_const$ int_const_node_1 = {1, &int_const_node_2};
////    int_const_node_1.data = 5; //Uncommenting will cause a compile error
//
//    list_node$double$ double_node_2 = {8.99, NULL};
//    list_node$double$ double_node_1 = {3.14, &double_node_2};
//    printf("%f, %p\n", double_node_1.data, double_node_1.next);
//    printf("%f, %p\n", double_node_2.data, double_node_2.next);
}
