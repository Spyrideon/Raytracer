#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H
#include "rt_math.h"

using Color = Vector3df;

struct Material {
    Color ambient = {0, 0, 0};
    Color diffuse;
    Color reflective;

    Material(Color ambient, Color diffuse, Color reflective)
        : ambient(ambient), diffuse(diffuse), reflective(reflective) {}
};

inline Material matteBlack() { return { {0.01f, 0.01f, 0.01f}, {0.01f, 0.01f, 0.01f}, {0.0f} }; }
inline Material matteRed()   { return { {0.1f,  0.0f,  0.0f},  {0.8f,  0.0f,  0.0f},  {0.0f} }; }
inline Material matteGreen() { return { {0.0f,  0.1f,  0.0f},  {0.0f,  0.8f,  0.0f},  {0.0f} }; }
inline Material matteWhite() { return { {0.1f,  0.1f,  0.1f},  {0.8f,  0.8f,  0.8f},  {0.0f} }; }
inline Material reflWhite()  { return { {0.05f, 0.05f, 0.05f}, {0.05f, 0.05f, 0.05f}, {0.9f, 0.9f, 0.9f} }; }

#endif //RAYTRACER_MATERIAL_H