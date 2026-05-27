#include "rt_math.h"
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>

#include "Camera.h"
#include "Screen.h"

constexpr int WIDTH = 100;
constexpr int HEIGHT = 100;
constexpr int   DEPTH  = 5;     // max reflection bounces
constexpr float GAMMA  = 2.0f;  // gamma correction exponent

int main() {
  Screen screen(WIDTH, HEIGHT);

  Camera camera(
        Vector3df{ 0.0f,  0.0f,  1.0f},   // lookFrom — in front of the box
        Vector3df{ 0.0f,  0.0f, -5.0f},   // lookAt   — centre of the box
        Vector3df{ 0.0f,  1.0f,  0.0f},   // up
        60.0f,                             // vFov
        static_cast<float>(WIDTH) / HEIGHT
    );

  auto toBytes = [](float v) -> uint8_t {
    v = std::clamp(v, 0.0f, 1.0f);
    return static_cast<uint8_t>(255.99f * std::sqrt(v)); // gamma 2
  };

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      screen.writePixel(x, y, 255, 255, 255);
    }
  }
  Vector3df Test = {1.f, 2.f, 3.f};
  screen.save("../output/render.ppm");


  return 0;
}

