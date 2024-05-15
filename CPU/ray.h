#ifndef RAYH
#define RAYH

#include "vec3.h"

class ray {
public: 
    ray() {}
    ray(const vec3& origin, const vec3 direction ) {orig=origin; dir=direction;}

    ray(const vec3& origin, const vec3 direction, double time) : tm(time) {orig=origin; dir=direction;}



    vec3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    double time() const { return tm; }

    vec3 point_at_parameter(float t) const {return orig + t*dir;}

    vec3 orig, dir;
    double tm;
};

#endif
