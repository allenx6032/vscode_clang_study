#ifdef CONFIG_H
#include CONFIG_H
#endif

#ifdef MATH_C
#pragma once
#define LINEAR_C
#define NOISE_C
#define TRANSFORM_C
#define UTILS_C
#define CAMERA_C
#define GJK_C
#define MTYPES_C
#define GEOMETRY_C
#define EASE_C
#define SHAPE_C
#endif

#include "math_linear.c.h"
#include "math_noise.c.h"
#include "math_transform.c.h"
#include "math_utils.c.h"
#include "math_camera.c.h"
#include "math_gjk.c.h"
#include "math_types.c.h"
#include "math_geometry.c.h"
#include "math_ease.c.h"
#include "math_shape.c.h"
