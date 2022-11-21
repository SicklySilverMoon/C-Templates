//For template users:
//Make sure to #define TEMPLATE_TYPE prior to inclusion of any template header.
//for types like 'long long' or 'unsigned long' you'll need to typedef something like
//`typedef long long long_long` and then `#define TEMPLATE_TYPE long_long`, else the space will break things.
//
//You will also need to include a template file per templated type, ex.
/*
    #define TEMPLATE_TYPE int
    #include "templates/list/list.h"
    //creates list_node$int$

    #define TEMPLATE_TYPE double
    #include "templates/list/list.h"
    //creates list_node$int$
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

//3rd level indirection to expand all macros and allow writing 'cleaner' code
#define TEMPLATE_INTERNAL_CAT(type) TEMPLATE_INTERNAL_CAT_(TEMPLATE_INTERNAL_NAME, type)
#define TEMPLATE_INTERNAL_CAT_(name, type) TEMPLATE_INTERNAL_CAT__(name, type)
#define TEMPLATE_INTERNAL_CAT__(name, type) name ## $ ## type ## $
