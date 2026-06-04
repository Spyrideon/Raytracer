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

    [[nodiscard]] Color lambertian(const HitRecord& rec, const Material& mat) const {
        Color diffuseSum = {0.0f, 0.0f, 0.0f};

        constexpr float LIGHT_POWER = 25.0f;

        for (const auto& light : lights) {
            Vector3df toLight = light - rec.ctx.intersection;
            const float lightDist = toLight.length();
            if (lightDist < 1e-6f) continue;
            toLight /= lightDist; // normalize

            const Ray3df shadowRay{ rec.ctx.intersection, toLight };
            HitRecord shadowRec;
            if (closestHit(shadowRay, shadowRec, 1e-3f, lightDist - 1e-3f))
                continue;

            const float cosTheta = toLight * rec.ctx.normal;
            if (cosTheta > 0.0f) {
                const float attenuation = LIGHT_POWER / (lightDist * lightDist);
                const float k = cosTheta * attenuation;
                diffuseSum[0] += mat.diffuse[0] * k;
                diffuseSum[1] += mat.diffuse[1] * k;
                diffuseSum[2] += mat.diffuse[2] * k;
            }
        }

        if (!lights.empty()) {
            const float invN = 1.0f / static_cast<float>(lights.size());
            diffuseSum *= invN;
        }

        return diffuseSum + mat.ambient;
    }

    /*
    // recursive
    Color traceRay(const Ray3df& ray, int depth = 4) const {

    }*/
};
#endif //RAYTRACER_SCENE_H
