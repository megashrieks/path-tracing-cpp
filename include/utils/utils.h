#include "vec3.h"
#ifndef UTILS_H
#define UTILS_H
vec3 uhr(const vec3&);
vec3 hemrandom();
float dot(const vec3&,const vec3&);
vec3 abs(const vec3&);
vec3 min(const vec3&, const vec3&);
vec3 max(const vec3&, const vec3&);
vec3 reflect(const vec3&, const vec3&);
vec3 cross(const vec3&,const vec3&);
#endif