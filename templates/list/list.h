//See common_start.h for more info

#define TEMPLATE_INTERNAL_NAME list_node
#include "../common_start.h"

//After including this header you can access the newly created list node via: `list_node$TEMPLATE_TYPE$`
//ex. with int: `list_node$int$`.

typedef struct TEMPLATE_INTERNAL_CAT(TEMPLATE_TYPE) {
    TEMPLATE_TYPE data;
    struct TEMPLATE_INTERNAL_CAT(TEMPLATE_TYPE)* next;
} TEMPLATE_INTERNAL_CAT(TEMPLATE_TYPE);

#include "../common_end.h"
