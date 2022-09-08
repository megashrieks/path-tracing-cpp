#include<iostream>
#include<math.h>
#include "vec3.h"


//constructor
vec3::vec3(float a, float b, float c): x(a),y(b),z(c) {}
vec3::vec3(): x(0), y(0), z(0) {}

//get length
float vec3::length() const{
    return pow(x*x+y*y+z*z,0.5);
}

//get normal
vec3 vec3::normal() const{
    float l = this->length();
    return vec3(x/l,y/l,z/l);
}



std::ostream& operator <<(std::ostream& os, vec3 v){
    os<<"vec3 { x:"<<v.x<<", y:"<<v.y<<", z:"<<v.z<<" }";
    return os;
}

vec3 vec3::operator+(const vec3& a) const{
    return vec3(x+a.x,y+a.y,z+a.z);
}
vec3 vec3::operator-(const vec3& a) const{
    return vec3(x-a.x,y-a.y,z-a.z);
}
vec3 vec3::operator*(float val) const{
    return vec3(x*val,y*val,z*val);
}

vec3 vec3::operator*(const vec3& t) const{
    return vec3(x*t.x,y*t.y,z*t.z);
}
vec3& vec3::operator+=(const vec3& a){
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
}
vec3& vec3::operator-=(const vec3& a){
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
}
vec3& vec3::operator=(const vec3& v){
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}
vec3& vec3::operator=(vec3&& v){
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

vec3::vec3(vec3&& v){
    x = v.x;
    y = v.y;
    z = v.z;
}
vec3::vec3(const vec3& v){
    x = v.x;
    y = v.y;
    z = v.z;
}
vec3::vec3(float v){
    x = v;
    y = v;
    z = v;
}