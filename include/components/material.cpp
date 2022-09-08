#include "material.h"
#include "vec3.h"

material::material(){
    roughness = 0;
    type = MTYPE::DIFFUSE;
    color = vec3();
}

material::material(float r, MTYPE m, const vec3& col){
    roughness = r;
    type = m;
    color = col;
}