#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H
#include "geometry.h"
#include "Material.h"

// wraps intresection_context with a bool
struct HitRecord {
    bool hit = false;
    Intersection_Context<float, 3u> ctx;
};

class Object {
public:
    Material material;

    explicit Object(Material mat) : material(mat) {}

    [[nodiscard]] virtual HitRecord intersect(const Ray3df& ray, float tMin, float tMax) const = 0;
};

#endif //RAYTRACER_OBJECT_H