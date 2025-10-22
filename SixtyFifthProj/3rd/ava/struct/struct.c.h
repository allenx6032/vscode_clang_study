#ifdef CONFIG_H
#include CONFIG_H
#endif

#ifdef STRUCT_C
#pragma once
#define ARRAY_C
#define CMP_C
#define HASH_C
#define HASHMAP_C
#define MAP_C
#endif

#ifndef API
#define API
#endif

#include "struct_array.c.h"
#include "struct_hash.c.h"
#include "struct_hashmap.c.h"
#include "struct_cmp.c.h"
#include "struct_map.c.h"
