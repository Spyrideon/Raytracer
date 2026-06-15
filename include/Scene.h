#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <vector>
#include <memory>
#include <random>
#include "Object.h"
#include "SphereObject.h"
#include "TriangleObject.h"

// returns a random point in the unit sphere
inline Vector3df randomInUnitSphere() {
    static thread_local std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<float> u(-1.0f, 1.0f);
    Vector3df p{ 0.0f, 0.0f, 0.0f };
    do {
        p = Vector3df{ u(rng), u(rng), u(rng) };
    } while (p * p > 1.0f); // reject points outside the unit sphere
    return p;
}

class Scene {
public:
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<Vector3df>               lights;
    Color                                background = {0.0f, 0.0f, 0.0f};

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

        constexpr int   SHADOW_SAMPLES = 64;
        constexpr float LIGHT_RADIUS   = 0.3f;

        for (const auto& light : lights) {
            Vector3df toLight = light - rec.ctx.intersection;
            const float lightDist = toLight.length();
            if (lightDist < 1e-6f) continue;
            toLight /= lightDist; // normalize

            const float cosTheta = toLight * rec.ctx.normal;
            if (cosTheta <= 0.0f) continue; // surface faces away from the light


            int visible = 0;
            for (int s = 0; s < SHADOW_SAMPLES; ++s) {
                const Vector3df target = light + LIGHT_RADIUS * randomInUnitSphere();

                Vector3df toSample = target - rec.ctx.intersection;
                const float sampleDist = toSample.length();
                if (sampleDist < 1e-6f) { ++visible; continue; }
                toSample /= sampleDist;

                const Ray3df shadowRay{ rec.ctx.intersection, toSample };
                HitRecord shadowRec;
                if (!closestHit(shadowRay, shadowRec, 1e-3f, sampleDist - 1e-3f))
                    ++visible;
            }

            const float shadowFactor =
                static_cast<float>(visible) / static_cast<float>(SHADOW_SAMPLES);
            if (shadowFactor <= 0.0f) continue; // fully occluded

            const float attenuation = LIGHT_POWER / (lightDist * lightDist);
            const float k = cosTheta * attenuation * shadowFactor;
            diffuseSum[0] += mat.diffuse[0] * k;
            diffuseSum[1] += mat.diffuse[1] * k;
            diffuseSum[2] += mat.diffuse[2] * k;
        }

        if (!lights.empty()) {
            const float invN = 1.0f / static_cast<float>(lights.size());
            diffuseSum *= invN;
        }

        return diffuseSum + mat.ambient;
    }

    // recursive
    [[nodiscard]] Color traceRay(const Ray3df& ray, int depth = 4) const {
        if (depth <= 0)
            return background;

        HitRecord rec;
        const Object* obj = closestHit(ray, rec);

        if (!obj)
            return background;

        const Material& mat = obj->material;
        Color color = lambertian(rec, mat);

        const float reflStrength = (mat.reflective[0] +
                                    mat.reflective[1] +
                                    mat.reflective[2]) / 3.0f;

        if (reflStrength > 0.001f) {
            Vector3df reflDir = ray.direction.get_reflective(rec.ctx.normal);
            reflDir.normalize();
            const Ray3df reflRay{ rec.ctx.intersection, reflDir };
            const Color reflColor = traceRay(reflRay, depth - 1);

            color[0] += mat.reflective[0] * reflColor[0];
            color[1] += mat.reflective[1] * reflColor[1];
            color[2] += mat.reflective[2] * reflColor[2];
        }

        return color;
    }
};
#endif //RAYTRACER_SCENE_H
