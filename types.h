#ifndef C_TEMPLATES_TYPES_H
#define C_TEMPLATES_TYPES_H

#define TEMPLATE_TYPE int
#include "templates/list/list.h"

typedef long long long_long;
#define TEMPLATE_TYPE long_long
#include "templates/list/list.h"

#define TEMPLATE_TYPE double
#include "templates/list/list.h"

typedef int const int_const;
#define TEMPLATE_TYPE int_const
#include "templates/list/list.h"

//#undef TEMPLATE_SEP
//#define TEMPLATE_SEP ___
//#define TEMPLATE_TYPE float
//#include "templates/list/list.h"

#endif //C_TEMPLATES_TYPES_H
