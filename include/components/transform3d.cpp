#include <iostream>
#include <math.h>
#include <vector>
#include "vec3.h"
#include "transform3d.h"

transform3d::transform3d(shape* s): shape(s->shapematerial) {
    this->s = s;
    this->tt = std::vector<std::vector<float>>(3,std::vector<float>(3));
    tt[0][0] = 1;
    tt[1][1] = 1;
    tt[2][2] = 1;
}
vec3 transform3d::getpos(){
    return this->s->getpos();
}
void transform3d::rotate(char axis, float theta){
    std::vector<std::vector<float>> mat;
    float s = sin(theta), c = cos(theta);
    if(axis == 'x'){
        mat = {{1,0,0},{0,c,-s},{0,s,c}};
    }else if(axis == 'y'){
        mat = {{c,0,s},{0,1,0},{-s,0,c}};
    }else if(axis == 'z'){
        mat = {{c,-s,0},{s,c,0},{0,0,1}};
    }
    std::vector<std::vector<float>> nt(3,std::vector<float>(3));
    for(int i = 0;i < 3;++i){
        for(int j = 0;j < 3;++j){
            for(int k = 0;k < 3;++k){
                nt[i][j] += mat[i][k] * tt[k][j];
            }
        }
    }
    tt = nt;

}
vec3 transform3d::tspace(const vec3& pos){
    vec3 npos(0);
    vec3 nnpos(0);
    nnpos = pos-s->getpos();
    for(int i = 0;i < 3;++i){
        for(int j = 0;j < 3;++j)
            (i == 0? npos.x:(i==1?npos.y:npos.z)) +=
             tt[i][j]*(j == 0?nnpos.x:(j == 1?nnpos.y:nnpos.z));
    }
    npos += s->getpos();
    return npos;
}
float transform3d::intersect(const vec3 &pos) {
    return s->intersect(tspace(pos));
}
vec3 transform3d::getnormal(const vec3 &pos) {
    const float EP = 0.01;
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