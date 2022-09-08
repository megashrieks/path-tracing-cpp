#include "primitiveshapes.h"
#include "vec3.h"
#include "utils.h"

const float EP = 0.1;
primitivesphere::primitivesphere(const vec3& pos, float radius, material &m): shape(m){
    this->pos = pos;
    this->radius = radius;
}
vec3 primitivesphere::getpos(){
    return pos;
}
float primitivesphere::intersect(const vec3& point){
    return (point-pos).length() - radius;
}

vec3 primitivesphere::getnormal(const vec3& pos){
    const float EP = 0.1;
    float p = intersect(pos);
    auto diff = [&](const vec3 &a, vec3&& d){
        return (intersect(a+d) - intersect(a-d));
    };
    return vec3(
        diff(pos,vec3(EP,0,0)),
        diff(pos,vec3(0,EP,0)),
        diff(pos,vec3(0,0,EP))
    ).normal();
}

primitiveplane::primitiveplane(const vec3& pos, float h, material &m): shape(m){
    this->pos = pos;
    this->offset = h;
}
vec3 primitiveplane::getpos(){
    return pos;
}
float primitiveplane::intersect(const vec3& point){
    return dot(point,pos) + offset;
}

vec3 primitiveplane::getnormal(const vec3&){
    return pos;
}

primitivebox::primitivebox(const vec3& pos, const vec3& dim, material &m): shape(m){
    this->pos = pos;
    this->dim = dim;
}
vec3 primitivebox::getpos(){
    return pos;
}
float primitivebox::intersect(const vec3& point){
    vec3 q = abs(point-pos) - dim;
    return max(q,vec3(0.0)).length() + std::min(std::max(q.x,std::max(q.y,q.z)),0.0f);
}

vec3 primitivebox::getnormal(const vec3& pos){
    float p = intersect(pos);
    auto diff = [&](const vec3 &a, vec3&& d){
        return (intersect(a+d) - intersect(a-d));
    };
    return vec3(
        diff(pos,vec3(EP,0,0)),
        diff(pos,vec3(0,EP,0)),
        diff(pos,vec3(0,0,EP))
    ).normal();
}