#ifndef RAYTRACER_CORNELLBOX_H
#define RAYTRACER_CORNELLBOX_H

#include "Scene.h"

// helper: adds two triangles forming a quad with a shared flat normal
inline void addQuad(Scene& scene,
                    Vector3df a, Vector3df b, Vector3df c, Vector3df d,
                    Vector3df normal, Material mat)
{
    scene.objects.push_back(std::make_unique<TriangleObject>(
        a, b, c, normal, mat));
    scene.objects.push_back(std::make_unique<TriangleObject>(
        a, c, d, normal, mat));
}

inline Scene buildCornellBox() {
    Scene scene;

    scene.lights.push_back({ 0.0f, 4.5f, -5.0f });

    // back wall
    addQuad(scene,
        {-5,-5,-8}, { 5,-5,-8}, { 5, 5,-8}, {-5, 5,-8},
        {0, 0, 1}, matteWhite());

    // floor
    addQuad(scene,
        {-5,-5,-8}, { 5,-5,-8}, { 5,-5, 0}, {-5,-5, 0},
        {0, 1, 0}, matteWhite());

    // ceiling
    addQuad(scene,
        {-5, 5,-8}, {-5, 5, 0}, { 5, 5, 0}, { 5, 5,-8},
        {0,-1, 0}, matteWhite());

    // left wall
    addQuad(scene,
        {-5,-5,-8}, {-5,-5, 0}, {-5, 5, 0}, {-5, 5,-8},
        {1, 0, 0}, matteRed());

    // right wall
    addQuad(scene,
        { 5,-5,-8}, { 5, 5,-8}, { 5, 5, 0}, { 5,-5, 0},
        {-1, 0, 0}, matteGreen());

    // front wall
    addQuad(scene,
        {-5,-5, 0}, {-5, 5, 0}, { 5, 5, 0}, { 5,-5, 0},
        {0, 0,-1}, matteWhite());

    scene.objects.push_back(std::make_unique<SphereObject>(
        Vector3df{ 1.5f, -3.5f, -5.0f}, 1.5f, reflWhite()));

    scene.objects.push_back(std::make_unique<SphereObject>(
        Vector3df{-2.0f, -3.5f, -6.0f}, 1.5f, matteRed()));

    scene.objects.push_back((std::make_unique<SphereObject>(
        Vector3df{-1.f, -4.5f, -4}, 0.5, Material({0.0f, 0.0f, 0.1f}, {1.f, 1.f, 0.4f}, {0.1f}))));

    return scene;
}

#endif //RAYTRACER_CORNELLBOX_H
