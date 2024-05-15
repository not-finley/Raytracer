#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class material;

class sphere: public hitable {
public:
    sphere();
	// Stationary Sphere
    sphere(const vec3& center, float radius, material *mat)
    : center1(center), radius(fmax(0,radius)), mat_ptr(mat), is_moving(false) {}

    // Moving Sphere
    sphere(const vec3& center1, const vec3& center2, float radius, material* mat)
	: center1(center1), radius(fmax(0,radius)), mat_ptr(mat), is_moving(true)
    {
        center_vec = center2 - center1;
    }
	
    // sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    vec3 center; float radius; material *mat_ptr;

	vec3 center1;
	bool is_moving;
    vec3 center_vec;

    vec3 sphere_center(double time) const {
        // Linearly interpolate from center1 to center2 according to time, where t=0 yields
        // center1, and t=1 yields center2.
        return center1 + time*center_vec;
    }
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 center = is_moving ? sphere_center(r.time()) : center1;
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(),r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;
	if(discriminant > 0) {
		float temp = (-b - sqrt(b*b-a*c))/a;
		if(temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(b*b-a*c))/a;
		if(temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.9*vec3(drand48(),drand48(),drand48())-vec3(1,1,1);
    } while(p.length_squared() >= 1.0);
    return p;
}

#endif
