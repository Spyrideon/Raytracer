#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H
#include "rt_math.h"

struct Ray {
    Vector3df origin;
    Vector3df direction;

    Vector3df at(const float t) const{return origin +  t * direction;}
};

#endif //RAYTRACER_RAY_H