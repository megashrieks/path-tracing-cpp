#include "vec3.h"
#ifndef MATERIAL_H
#define MATERIAL_H
enum MTYPE {DIFFUSE, SPECULAR, GLOSSY, LIGHT};
class material {
    public:
    float roughness;
    MTYPE type;
    vec3 color;
    material();
    material(float, MTYPE, const vec3&);
};

#endif