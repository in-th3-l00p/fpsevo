/*
 * =====================================================================================
 *
 *       Filename:  math.h
 *
 *    Description:  definition for a math library 
 *
 *        Version:  1.0
 *        Created:  19.10.2023 22:50:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  intheloop
 *   Organization:  steagu enterprise
 *
 * =====================================================================================
 */

#ifndef FPSEVO_MYMATH_H_
#define FPSEVO_MYMATH_H_

#include <math.h>
#include <stdlib.h>

// radians
#define DEG2RAD(a) a * M_PI / 180
#define RAD2DEG(a) a * 180 / M_PI

// vectors
typedef struct { int x, y; } vec2i;
typedef struct { float x, y; } vec2f;

float getAngleVec2f(vec2f vec);
vec2f fromAngleVec2f(float angle);
float magnitudeVec2f(vec2f vec);
vec2f rotateVec2f(vec2f vec, float angle);

#endif