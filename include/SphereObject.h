#ifndef RAYTRACER_SPHEREOBJECT_H
#define RAYTRACER_SPHEREOBJECT_H
#include "Object.h"

class SphereObject : public Object {
public:
    SphereObject(Vector3df center, float radius, Material mat)
        : Object(mat), sphere(center, radius) {}

    HitRecord intersect(const Ray3df& ray,
                                      float tMin,
                                      float tMax) const override
    {
        HitRecord rec;
        Intersection_Context<float, 3u> ctx;

        if (sphere.intersects(ray, ctx) && ctx.t > tMin && ctx.t < tMax) {
            rec.hit = true;
            rec.ctx = ctx;
        }
        return rec;
    }

private:
    Sphere3df sphere;
};

#endif //RAYTRACER_SPHEREOBJECT_H