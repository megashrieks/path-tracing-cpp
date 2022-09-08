#include "vec3.h"
#include "material.h"
#ifndef SHAPE_H
#define SHAPE_H

class shape {
    public:
    material shapematerial;
    virtual float intersect(const vec3&)=0;
    shape(const material&);
    shape();
    virtual vec3 getpos()=0;
    virtual shape& operator=(const shape&);
    virtual vec3 getnormal(const vec3&)=0;
};

#endif