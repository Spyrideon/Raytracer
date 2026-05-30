#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <vector>
#include <memory>
#include "Object.h"
#include "SphereObject.h"
#include "TriangleObject.h"

class Scene {
public:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<Vector3df>               lights;
    Color                                background = {0.0f, 0.0f, 0.0f};

    // can return nullptr
    [[nodiscard]] const Object* closestHit(const Ray3df& ray,
                                           HitRecord& rec,
                                           float tMin = 0.001f,
                                           float tMax = 1e9f) const
    {
        const Object* closest = nullptr;
        float nearestT = tMax;

        for (const auto& obj : objects) {
            HitRecord candidate = obj->intersect(ray, tMin, nearestT);
            if (candidate.hit && candidate.ctx.t < nearestT) {
                nearestT = candidate.ctx.t;
                rec      = candidate;
                closest  = obj.get();
            }
        }
        return closest;
    }

    /*Color lambertian(const HitRecord& rec, const Material& mat) const { }

    // recursive
    Color traceRay(const Ray3df& ray, int depth = 4) const { }*/
};
#endif //RAYTRACER_SCENE_H
