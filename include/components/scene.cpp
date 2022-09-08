#include "scene.h"
#include "vec3.h"

float scene::intersect(vec3 &pos, int &objid){
    float d = INT_MAX;
    for(int i = 0;i < objects.size();++i){
        float t = objects[i]->intersect(pos);
        if(t < d) {
            d = t;
            objid = i;
        }
    }
    return d;
}

void scene::addobject(shape &s){
    if(s.shapematerial.type == MTYPE::LIGHT)
        lights.push_back(&s);
    objects.push_back(&s);
}
