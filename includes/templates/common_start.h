//For template users:
//Due to redefinition oddities (and general simplicity), you need to actually include any template files inside an INCLUDE GUARDED
//header file, and then include that elsewhere, ex. main.c includes types.h includes list.h (possibly multiple times)
//this prevents redefinition errors and also means you don't have to duplicate the full `#define TEMPLATE_TYPE type` each time

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

//Any macro/identifier starting with TEMPLATE_INTERNAL_ is reserved to any template library for any use
//Any macro/identifier starting with TEMPLATE_ is reserved to any template library for any user facing use

#ifndef TEMPLATE_TYPE
    #error TEMPLATE_TYPE is undefined!
#endif

#ifndef TEMPLATE_INTERNAL_NAME
    #error TEMPLATE_INTERNAL_NAME undefined! This is an error from the library creator!
#endif

//todo: write up an explanation for this in the future docs
//Long story short if you don't define TEMPLATE_ISNT_STATIC then all funcs and vars (such as the vtable) are marked static.
//This is easier but wastes and duplicates memory (which doesn't matter all that much in the long run on modernish systems).
//However if TEMPLATE_ISNT_STATIC is defined (which it should be in the above mentioned include guarded file),
//then only the prototypes for funcs are provided, and vars are marked extern.
//Then there needs to be some single implementing code file that defines TEMPLATE_IS_IMPL before including the header that
//generates the types
#ifndef TEMPLATE_ISNT_STATIC //This is NOT undef'd so that it only needs to be defined once and then works properly for all template includes
    #define TEMPLATE_INTERNAL_staticish static
    #define TEMPLATE_INTERNAL_externish static
#else
    #define TEMPLATE_INTERNAL_staticish
    #ifndef TEMPLATE_IS_IMPL //ditto
        #define TEMPLATE_INTERNAL_externish extern
    #else
        #define TEMPLATE_INTERNAL_externish /*intentionality blank*/
    #endif
#endif

#ifndef TEMPLATE_SEP //We don't actually undef this one as we don't want to force the user to write this again and again
    #define TEMPLATE_SEP $
#endif

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

//3rd level indirection to expand all macros and allow writing 'cleaner' code
#define TEMPLATE_INTERNAL_CAT(prefix, name, type, suffix) TEMPLATE_INTERNAL_CAT_(prefix, name, type, suffix, TEMPLATE_SEP) //expands all but SEP
#define TEMPLATE_INTERNAL_CAT_(prefix, name, type, suffix, sep) TEMPLATE_INTERNAL_CAT__(prefix, name, type, suffix, sep) //forwards + expands SEP
#define TEMPLATE_INTERNAL_CAT__(prefix, name, type, suffix, sep) prefix ## name ## sep ## type ## sep ## suffix //Glues all tokens together

//Expands to actual proper type name (ex. `list$double$`)
#define TEMPLATE_INTERNAL_FullName TEMPLATE_INTERNAL_CAT(, TEMPLATE_INTERNAL_NAME, TEMPLATE_TYPE, )

//Used to generate a prefix to the full type (ex. `create_list$int$`)
#define TEMPLATE_INTERNAL_PREFIX_CAT(prefix) TEMPLATE_INTERNAL_CAT(prefix, TEMPLATE_INTERNAL_NAME, TEMPLATE_TYPE, )

//Can be used to generate delegate types (ex. `list_node$long$`)
#define TEMPLATE_INTERNAL_SHORT_CAT(name) TEMPLATE_INTERNAL_CAT(, name, TEMPLATE_TYPE, )

//Give it a deliberately weird name so to indicate it's not for general use
//Expands to an internal use vtable name
#define TEMPLATE_INTERNAL_vTable TEMPLATE_INTERNAL_CAT(TEMPLATE_INTERNAL_, TEMPLATE_INTERNAL_NAME, TEMPLATE_TYPE, ____vtable____)

#define TEMPLATE_INTERNAL_func_name(func_name) TEMPLATE_INTERNAL_CAT(TEMPLATE_INTERNAL_, TEMPLATE_INTERNAL_NAME, TEMPLATE_TYPE, func_name)

#define TEMPLATE_INTERNAL_TYPE_NAME(type_name) TEMPLATE_INTERNAL_CAT(TEMPLATE_INTERNAL_TYPE, TEMPLATE_INTERNAL_NAME, TEMPLATE_TYPE, type_name)
