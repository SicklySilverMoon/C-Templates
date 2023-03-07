#ifndef C_TEMPLATES_LIST_TEST_H
#define C_TEMPLATES_LIST_TEST_H

#include <stddef.h>

#define TEMPLATE_TYPE int
#include "templates/list/list.h"

typedef long long long_long;
#define TEMPLATE_TYPE long_long
#include "templates/list/list.h"

typedef int const int_const;
#define TEMPLATE_TYPE int_const
#include "templates/list/list.h"

#undef TEMPLATE_SEP //tests that setting a sep value actually works
#define TEMPLATE_SEP ___
#define TEMPLATE_TYPE float
#include "templates/list/list.h"
#undef TEMPLATE_SEP //unset it again, we don't want to deal with ___ on everything

int list_test();

#endif //C_TEMPLATES_LIST_TEST_H