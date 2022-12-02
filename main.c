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


    list$int$ int_list2 = create_list$int$();

    int_list2.vtable->prepend(&int_list2, 9);
    printf("%p: %d, %p: %d\n", int_list2.head, int_list2.head->value, int_list2.tail, int_list2.tail->value);

    int_list2.vtable->prepend(&int_list2, 10);
    printf("%p: %d, %p: %d\n", int_list2.head, int_list2.head->value, int_list2.tail, int_list2.tail->value);

    int_list2.vtable->prepend(&int_list2, 11);
    printf("%p: %d, %p: %d %p: %d\n", int_list2.head, int_list2.head->value, int_list2.head->next, int_list2.head->next->value, int_list2.tail, int_list2.tail->value);

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
