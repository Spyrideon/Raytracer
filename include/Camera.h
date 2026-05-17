#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H
#include "Ray.h"

class Camera {
public:
    // lookFrom  — where the camera sits in the scene
    // lookAt    — the point the camera is aimed at
    // up        — world up vector, usually {0,1,0}
    // vFovDeg   — vertical field of view in degrees
    // aspect    —width / height of the output image
    Camera(Vector3df lookFrom,
           Vector3df lookAt,
           Vector3df up,
           float vFovDeg,
           float aspect);

    [[nodiscard]] Ray generateRay(float u, float v) const;

private:
    Vector3df origin{0.f};
    Vector3df lowerLeftCorner{0.f};
    Vector3df horizontal{0.f};
    Vector3df vertical{0.f};
};

#endif //RAYTRACER_CAMERA_H