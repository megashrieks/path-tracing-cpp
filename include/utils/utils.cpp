#include <cstdlib>
#include <math.h>
#include <time.h>
#include "utils.h"
#include "vec3.h"
#define PI 3.1412857

float dot(const vec3& a,const vec3& b){
    vec3 ret = a*b;
    return ret.x+ret.y+ret.z;
}

vec3 abs(const vec3& v){
    return vec3(std::abs(v.x),abs(v.y),abs(v.z));
}

vec3 min(const vec3& v,const vec3& u){
    return vec3(std::min(v.x,u.x),std::min(v.y,u.y),std::min(v.z,u.z));
}

vec3 max(const vec3& v,const vec3& u){
    return vec3(std::max(v.x,u.x),std::max(v.y,u.y),std::max(v.z,u.z));
}
vec3 reflect(const vec3& I, const vec3& N){
    return I - N * 2.0 * dot(N,I);
}

vec3 cross(const vec3& a,const vec3& b){
    return vec3(a.y*b.z-b.y*a.z, a.z*b.x-b.z*a.x,a.x*b.y-b.x*a.y);
}
vec3 uhr(const vec3 &n) {
    float u = (float)(rand()%1000)/1000.0;
    float v = (float)(rand()%1000)/1000.0;
  	vec3 r(u, v,0);
	vec3  uu = (cross(n, std::abs(n.y) > .5 ? vec3(1.,0.,0.) : vec3(0.,1.,0.))).normal();
	vec3  vv = cross(uu, n);
	float ra = sqrt(r.y);
	float rx = ra*cos(6.28318530718*r.x); 
	float ry = ra*sin(6.28318530718*r.x);
	float rz = sqrt(1.-r.y);
	vec3 rr(uu*rx + vv*ry + n*rz);
    return rr.normal();

    // float theta = u * 2.0 * PI;
    // float phi = acos(2.0 * v - 1.0);
    // float r = pow((float)(rand()%1000)/1000.0,1/3);
    // float sinTheta = sin(theta);
    // float cosTheta = cos(theta);
    // float sinPhi = sin(phi);
    // float cosPhi = cos(phi);
    // float x = r * sinPhi * cosTheta;
    // float y = r * sinPhi * sinTheta;
    // float z = r * cosPhi;
    // vec3 ret(x,y,z);
    // float cosine = dot(ret,normal) / (ret.length()*normal.length());
    // if(cosine <= 0) return ret*-1;
    // return ret;
}

vec3 hemrandom() {
    float u = (float)(rand()%1000)/1000.0;
    float v = (float)(rand()%1000)/1000.0;

    float theta = u * 2.0 * PI;
    float phi = acos(2.0 * v - 1.0);
    float r = pow((float)(rand()%1000)/1000.0,1/3);
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);
    float sinPhi = sin(phi);
    float cosPhi = cos(phi);
    float x = r * sinPhi * cosTheta;
    float y = r * sinPhi * sinTheta;
    float z = r * cosPhi;
    return vec3(x,y,z);
}