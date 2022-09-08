#include "vec3.h"
#include "shape.h"
#ifndef PRIMITIVESHAPE_H
#define PRIMITIVESHAPE_H
class primitivesphere: public shape{
    public:
    vec3 pos;
    float radius;
    primitivesphere(const vec3&, float, material&);
    vec3 getpos();
    float intersect(const vec3&);
    vec3 getnormal(const vec3&);
};

class primitiveplane: public shape{
    public:
    vec3 pos;
    float offset;
    primitiveplane(const vec3&, float, material&);
    vec3 getpos();
    float intersect(const vec3&);
    vec3 getnormal(const vec3&);
};

class primitivebox: public shape{
    public:
    vec3 pos, dim;
    primitivebox(const vec3&, const vec3&, material&);
    vec3 getpos();
    float intersect(const vec3&);
    vec3 getnormal(const vec3&);
};
#endif