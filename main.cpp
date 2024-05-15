#include <iostream>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"


vec3 colour(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)) {
        //vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        //return 0.5*colour(ray(rec.p, target - rec.p), world);
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)) {
            return attenuation * colour(scattered,world,depth+1);
        } else {
            return vec3(0,0,0);
        }
    } else {
        vec3 unit_dir = unit_vector(r.direction());
        float t = 0.5*(unit_dir.y() + 1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
    }
}

hitable *random_scene() {
    int n = 400; 
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec3(0,-1000,0),1000,new lambert(vec3(0.5,0.5,0.5)));
    int i = 1;
    for(int a=-11; a<11; a++) {
        for(int b=-11; b<11; b++) {
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(), 0.2, b+0.9*drand48());
            if(choose_mat < 0.7) {
                list[i++] = new sphere(center, 0.2, new lambert(vec3(drand48()*drand48(),drand48()*drand48(),drand48()*drand48())));
            } else if(choose_mat < 0.90) {
                list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1+drand48()),0.5*(1+drand48()),0.5*(1+drand48())),0.5*(1+drand48())));
            } else {
                list[i++] = new sphere(center, 0.2, new dilectric(1.5));
            }
        }
    }
    list[i++] = new sphere(vec3(0,1,0), 1, new dilectric(1.5));
    list[i++] = new sphere(vec3(-4,1,0), 1, new lambert(vec3(0.7,0.8,0.79)));
    list[i++] = new sphere(vec3(4,1,0), 1, new metal(vec3(0.99,0.55,0.99), 0.4));
    return new hitable_list(list, i);
}

int main() {
    // sphere = vec3(0,0,-1);
    // sphere_radius = 0.5;
    int width = 800;
    int height = 400;
    int ns = 200;
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    
    //0.7,0.8,0.79
    // hitable *list[4];
    // list[0] = new sphere(vec3(0,0,-1),0.5,new lambert(vec3(0.99,0.55,0.99)));
    // list[1] = new sphere(vec3(0,-100.5,-1),100,new lambert(vec3(0.45,0.4,0.3)));
    // list[2] = new sphere(vec3(1,0,-1),0.5, new metal(vec3(0.8,0.8,0.55),0.2));
    // list[3] = new sphere(vec3(-1,0,-1),0.5,new dilectric(1.5));
    // hitable *world = new hitable_list(list, 4);

    // hitable *list[2];
    // float R = cos(M_PI/4);
    // list[0] = new sphere(vec3(-R,0,-3), R, new lambert(vec3(0,0,1)));
    // list[1] = new sphere(vec3(R,0,-3), R, new lambert(vec3(1,0,0)));
    // hitable *world = new hitable_list(list, 2);

    hitable *world = random_scene();
    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(width)/float(height), aperture, dist_to_focus);
    for(int y=height-1; y>=0; y--) {
        for(int x=0; x<width; x++) {
            vec3 col(0,0,0);
            for(int s=0; s<ns; s++){
                float u = float(x+drand48()) / float(width);
                float v = float(y+drand48()) / float(height);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += colour(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    } 
}