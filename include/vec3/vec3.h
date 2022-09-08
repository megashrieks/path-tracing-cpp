#include <fstream>
#ifndef VEC3_H
#define VEC3_H
class vec3 {
public:
    float x, y, z;
    vec3(float,float,float);
    vec3(vec3&&);
    vec3(const vec3&);
    vec3();
    vec3(float val);
    float length() const;
    vec3 normal() const;
    vec3 operator+(const vec3&) const;
    vec3 operator-(const vec3&) const;
    vec3 operator*(float) const;
    vec3 operator*(const vec3&) const;
    vec3& operator+=(const vec3&);
    vec3& operator-=(const vec3&);
    vec3& operator=(const vec3&);
    vec3& operator=(vec3&&);
    friend std::ostream& operator <<(std::ostream&, vec3);
};
#endif