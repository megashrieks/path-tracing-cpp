#include <vector>
#include "vec3.h"
#include "shape.h"
#ifndef SCENE_H
#define SCENE_H

class scene{
    public:
    std::vector<shape*> objects;
    std::vector<shape*> lights;
    float intersect(vec3&, int&);
    float intersectlight(vec3&, int&);
    void addobject(shape &s);

};

#endif