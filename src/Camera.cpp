#include "Camera.h"
#include <cmath>

Camera::Camera(const Vector3df lookFrom,
               const Vector3df lookAt,
               const Vector3df up,
               const float vFovDeg,
               const float aspect)
{
    const float vFovRad = vFovDeg * static_cast<float>(PI) / 180.0f;

    // half-height and half-width of the near plane at distance 1
    const float halfH = std::tan(vFovRad / 2.0f);
    const float halfW = aspect * halfH;

    // build an orthonormal basis for the camera orientation
    Vector3df w = lookFrom - lookAt;   // points AWAY from the scene
    w.normalize();

    Vector3df u = up.cross_product(w); // points right
    u.normalize();

    const Vector3df v = w.cross_product(u);  // points up (recomputed, guaranteed orthogonal)

    origin          = lookFrom;
    horizontal      = 2.0f * halfW * u;
    vertical        = 2.0f * halfH * v;
    lowerLeftCorner = origin - halfW * u - halfH * v - w;
}

Ray3df Camera::generateRay(const float u, const float v) const {
    const Vector3df target = lowerLeftCorner + u * horizontal + v * vertical;
    Vector3df direction = target - origin;
    direction.normalize();
    return Ray3df{ origin, direction };
}
