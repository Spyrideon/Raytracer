#include "rt_math.h"
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>

#include "Camera.h"
#include "CornellBox.h"
#include "Scene.h"
#include "Screen.h"

constexpr int WIDTH  = 2000;
constexpr int HEIGHT = 2000;
constexpr int   DEPTH  = 8;     // max reflection bounces
constexpr float GAMMA  = 2.2f;  // gamma correction exponent

int main() {
  Screen screen(WIDTH, HEIGHT);

  Camera camera(
        Vector3df{ 0.0f,  0.0f,  9.0f},   // lookFrom: outside, in front of the box
        Vector3df{ 0.0f,  0.0f, -4.0f},   // lookAt:   centre of the box interior
        Vector3df{ 0.0f,  1.0f,  0.0f},   // up
        60.0f,                            // vFov in degrees
        static_cast<float>(WIDTH) / HEIGHT
    );

  Scene scene = buildCornellBox();

  auto toBytes = [](float v) -> uint8_t {
    v = std::clamp(v, 0.0f, 1.0f);
    return static_cast<uint8_t>(255.99f * std::pow(v, 1.0f / GAMMA)); // std::sqrt(v) faster
  };

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      const float u = static_cast<float>(x) / (WIDTH  - 1);
      const float v = 1.0f - static_cast<float>(y) / (HEIGHT - 1);

      const Ray3df ray   = camera.generateRay(u, v);
      const Color  color = scene.traceRay(ray, DEPTH);

      screen.writePixel(x, y,
          toBytes(color[0]),
          toBytes(color[1]),
          toBytes(color[2]));

      std::cout << "x = " << x << ", y = " << y << std::endl;
    }
  }
  screen.save("../output/render.ppm");

  return 0;
}
