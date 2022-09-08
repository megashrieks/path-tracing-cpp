#include <vector>
#include "vec3.h"
#include "scene.h"
#ifndef RAYTRACE_H
#define RAYRACE_H

class raytrace {
    const float EP = 0.001;
    int width, height;
    scene world;
    vec3 trace(vec3&, vec3&);
    public:
    int iteration;
    std::vector<std::vector<vec3>> image;
    raytrace(int, int);
    raytrace(int, int, scene&);
    void addscene(scene&);
    void setpixel(int, int, vec3&);
    void render();
    vec3 lightray(vec3&,vec3&);
};

#endif