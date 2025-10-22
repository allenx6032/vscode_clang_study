#ifdef CONFIG_H
#include CONFIG_H
#endif

#ifdef STRING_C
#pragma once
#define STRING2_C
#define UTILITIES_C

#define FUZZY_C
#define INI_C
#define QUARK_C
#define REGEX_C
#define SSO_C
#define UNICODE_C
#endif

#include "string2.c.h"
#include "string_utilities.c.h"

#include "string_fuzzy.c.h"
#include "string_ini.c.h"
#include "string_quark.c.h"
#include "string_regex.c.h"
#include "string_sso.c.h"
#include "string_unicode.c.h"
