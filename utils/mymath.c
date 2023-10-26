/*
 * =====================================================================================
 *
 *       Filename:  mymath.c
 *
 *    Description:  implementation of local math library 
 *
 *        Version:  1.0
 *        Created:  19.10.2023 23:25:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  intheloop
 *   Organization:  steagu enterprise
 *
 * =====================================================================================
 */

#include "mymath.h"
#include <stdlib.h>

float getAngleVec2f(vec2f vec) { 
    return atan2(vec.y, vec.x); 
}

vec2f fromAngleVec2f(float angle) { 
    vec2f vec = { cos(angle), sin(angle) }; 
    return vec;
}

float magnitudeVec2f(vec2f vec) { 
    return sqrt(vec.x * vec.x + vec.y * vec.y); 
}

vec2f rotateVec2f(vec2f vec, float angle) { 
    float sina = sin(angle), cosa = cos(angle); 
    vec2f rvec = { 
        vec.x * cosa - vec.y * sina, 
        vec.x * sina + vec.y * cosa 
    };
    return rvec;
}

