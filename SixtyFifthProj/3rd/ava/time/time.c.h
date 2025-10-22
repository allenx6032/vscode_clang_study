#ifdef CONFIG_H
#include CONFIG_H
#endif

#ifdef TIME_C
#pragma once
#define RAW_C
#define FLICKS_C
#define DATE_C
#endif

#include "time_raw.c.h"
#include "time_flicks.c.h"
#include "time_date.c.h"
