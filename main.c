#include <stdio.h>

//Just an example for the provided template(s)

#define TEMPLATE_TYPE int
#include "templates/list/list.h"

typedef long long long_long;
#define TEMPLATE_TYPE long_long
#include "templates/list/list.h"

#define TEMPLATE_TYPE double
#include "templates/list/list.h"

int main() {
    list_node$int$ x = {4, NULL};
    printf("%d, %p\n", x.data, x.next);

    list_node$long_long$ w = {27LL, NULL};
    printf("%lld, %p\n", w.data, w.next);

    list_node$double$ y = {3.14, NULL};
    list_node$double$ z = {8.99, &y};
    printf("%f, %p\n", y.data, y.next);
    printf("%f, %p\n", z.data, z.next);
}
