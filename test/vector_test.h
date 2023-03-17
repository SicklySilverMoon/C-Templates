#ifndef C_TEMPLATES_TEST_VECTOR_TEST_H
#define C_TEMPLATES_TEST_VECTOR_TEST_H

#include <stddef.h>

//#define TEMPLATE_ISNT_STATIC //comment out this one and you also need to comment out `#define TEMPLATE_IS_IMPL` in list_test.c

#define TEMPLATE_TYPE int
#include <templates/vector/vector.h>

typedef long long long_long;
#define TEMPLATE_TYPE long_long
#include <templates/vector/vector.h>

typedef int const int_const;
#define TEMPLATE_TYPE int_const
#include <templates/vector/vector.h>

void vector_test();

#endif //C_TEMPLATES_TEST_VECTOR_TEST_H
