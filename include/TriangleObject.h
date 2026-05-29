#ifndef RAYTRACER_TRIANGLEOBJECT_H
#define RAYTRACER_TRIANGLEOBJECT_H
#include "Object.h"

class TriangleObject : public Object {
public:
    TriangleObject(Vector3df a, Vector3df b, Vector3df c,
                   Vector3df normal, Material mat)
        : Object(mat),
          triangle(a, b, c, normal, normal, normal),
          na(normal), nb(normal), nc(normal) {}

    TriangleObject(Vector3df a, Vector3df b, Vector3df c,
                   Vector3df na, Vector3df nb, Vector3df nc,
                   Material mat)
        : Object(mat),
          triangle(a, b, c, na, nb, nc),
          na(na), nb(nb), nc(nc) {}

    [[nodiscard]] HitRecord intersect(const Ray3df& ray,
                                      float tMin,
                                      float tMax) const override
    {
        HitRecord rec;
        Intersection_Context<float, 3u> ctx;

        if (triangle.intersects(ray, ctx) && ctx.t > tMin && ctx.t < tMax) {
            const float w = 1.0f - ctx.u - ctx.v;
            Vector3df interpolated = w * na + ctx.u * nb + ctx.v * nc;
            interpolated.normalize();

            if (ray.direction * interpolated > 0.0f) {
                return rec;
            }

            rec.hit = true;
            rec.ctx = ctx;
            rec.ctx.normal = interpolated;
        }
        return rec;
    }
private:
    Triangle3df triangle;
    Vector3df   na, nb, nc;
};

#endif //RAYTRACER_TRIANGLEOBJECT_H