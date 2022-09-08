#include "shape.h"

shape::shape(const material &m){
    this->shapematerial = m;
}
shape::shape(){
    shapematerial = material(0.0f,MTYPE::DIFFUSE, vec3(1,0,0));
}

shape& shape::operator=(const shape& s){
    shapematerial = s.shapematerial;
    return *this;
}
