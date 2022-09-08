#include <vector>
#include "shape.h"
class transform3d: public shape{
    shape* s;
    std::vector<std::vector<float>> tt;
    public:
    vec3 getpos();
    transform3d(shape*);
    float intersect(const vec3&);
    vec3 getnormal(const vec3&);
    vec3 tspace(const vec3&);
    void rotate(char, float);
};