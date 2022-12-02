//For template users:
//Make sure to #define TEMPLATE_TYPE prior to inclusion of any template header.
//for types like 'long long' or 'unsigned long' you'll need to typedef something like
//`typedef long long long_long` and then `#define TEMPLATE_TYPE long_long`, else the space will break things.
//
//You will also need to include a template file per templated type, ex.
/*
    #define TEMPLATE_TYPE int
    #include "templates/list/list.h"
    //creates list$int$

    #define TEMPLATE_TYPE double
    #include "templates/list/list.h"
    //creates list$int$
 */

//For template creators:
//Make sure to #define TEMPLATE_INTERNAL_NAME before including *this* header
//(and do it BEFORE writing any other code).

#ifndef TEMPLATE_TYPE
    #error TEMPLATE_TYPE is undefined!
#endif

#ifndef TEMPLATE_INTERNAL_NAME
    #error TEMPLATE_INTERNAL_NAME undefined! This is an error from the library creator!
#endif

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

//2nd level indirection to expand all macros and allow writing 'cleaner' code
#define TEMPLATE_INTERNAL_CAT(prefix, name, type, suffix) TEMPLATE_INTERNAL_CAT_(prefix, name, type, suffix)
#define TEMPLATE_INTERNAL_CAT_(prefix, name, type, suffix) prefix ## name ## $ ## type ## $ ## suffix

//Expands to actual proper type name (ex. `list$double$`)
#define TEMPLATE_INTERNAL_FULL_NAME TEMPLATE_INTERNAL_CAT(, TEMPLATE_INTERNAL_NAME, TEMPLATE_TYPE, )

//Used to generate a prefix to the full type (ex. `create_list$int$`)
#define TEMPLATE_INTERNAL_PREFIX_CAT(prefix) TEMPLATE_INTERNAL_CAT(prefix, TEMPLATE_INTERNAL_NAME, TEMPLATE_TYPE, )

//Can be used to generate delegate types (ex. `list_node$long$`)
#define TEMPLATE_INTERNAL_SHORT_CAT(name) TEMPLATE_INTERNAL_CAT(, name, TEMPLATE_TYPE, )

//Give it a deliberately weird name so to indicate it's not for general use
//Expands to an internal use vtable name
#define TEMPLATE_INTERNAL_VTABLE TEMPLATE_INTERNAL_CAT(template_internal_, TEMPLATE_INTERNAL_NAME, TEMPLATE_TYPE, ____vtable____)

#define TEMPLATE_INTERNAL_FUNC_NAME(func_name) TEMPLATE_INTERNAL_CAT(template_internal_, TEMPLATE_INTERNAL_NAME, TEMPLATE_TYPE, func_name)
