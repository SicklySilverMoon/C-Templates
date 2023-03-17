#include <stdio.h>

//#include "types.h"
#include "list_test.h"

//list$int$ const int_list = {.size = 0, .vtable = &template_internal_list$int$____vtable____};

void print_int(int* int_ptr) {
    printf("%d, ", *int_ptr);
}

//Just an example for the provided template(s)
int main() {
    list_test();

//    list$int$ int_list = create_list$int$();
//
//    int_list.vtable->append(&int_list, 9);
//    printf("%p: %d, %p: %d\n", int_list.head, int_list.head->value, int_list.tail, int_list.tail->value);
//
//    int_list.vtable->append(&int_list, 10);
//    printf("%p: %d, %p: %d\n", int_list.head, int_list.head->value, int_list.tail, int_list.tail->value);
//
//    int_list.vtable->append(&int_list, 11);
//    printf("%p: %d, %p: %d %p: %d\n", int_list.head, int_list.head->value, int_list.head->next, int_list.head->next->value, int_list.tail, int_list.tail->value);
//    printf("int list size: %zu\n", int_list.size);
//
//    int_list.vtable->destroy(&int_list);
//
//    printf("\n");
//    list$int$ int_list2 = create_list$int$();
//
//    int_list2.vtable->prepend(&int_list2, 9);
//    printf("%p: %d, %p: %d\n", int_list2.tail, int_list2.tail->value, int_list2.head, int_list2.head->value);
//
//    int_list2.vtable->prepend(&int_list2, 10);
//    printf("%p: %d, %p: %d\n", int_list2.tail, int_list2.tail->value, int_list2.head, int_list2.head->value);
//
//    int_list2.vtable->prepend(&int_list2, 11);
//    printf("%p: %d, %p: %d %p: %d\n", int_list2.tail, int_list2.tail->value, int_list2.tail->prev, int_list2.tail->prev->value, int_list2.head, int_list2.head->value);
//    printf("int list 2 size: %zu\n", int_list2.size);
//
//    printf("Contents of list being destroyed: ");
//    int_list2.vtable->destroy_callback(&int_list2, print_int);
//    printf("\n");
//
//    list$double$ double_list = create_list$double$();
//    for (size_t i = 0; i < 100; i++) {
//        double_list.vtable->append(&double_list, i / 10.0);
//    }
//    printf("\n\n");
////    list_node$double$* node = double_list.head;
////    while (node) {
////        printf("%p: %f\n", node, node->value);
////        node = node->next;
////    }
//    printf("get tests:\n");
//    printf("idx 4: %f\n", *double_list.vtable->get(&double_list, 4));
//    printf("idx 95: %f\n", *double_list.vtable->get(&double_list, 95));
//
//    double_list.vtable->remove(&double_list, 0);
//    printf("\nremoval tests:\n");
//    printf("idx 0: %f\n", double_list.head->value);
//    printf("idx 98: %f\n", *double_list.vtable->get(&double_list, 98));
//
//    printf("\nAdd tests:\n");
//    printf("prev idx 0: %f\n", double_list.head->value);
//    double_list.vtable->add(&double_list, 0, -1);
//    printf("new  idx 0: %f\n\n", double_list.head->value);
//    list_node$double$* double_node = double_list.vtable->get_node(&double_list, 17);
//    printf("prev idx 17: %f\n", double_node->value);
//    double_list.vtable->add_node(&double_list, double_node, -2);
//    printf("new  idx 17: %f\n", *double_list.vtable->get(&double_list, 17));
//    if ((double_list.vtable->get_node(&double_list, 17) != double_node->prev) || (double_list.vtable->get_node(&double_list, 17)->next != double_node)) {
//        printf("ERROR: removal pointer consistency failure!");
//    }
}
