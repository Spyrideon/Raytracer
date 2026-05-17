#include "rt_math.h"
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "Screen.h"

constexpr int WIDTH = 100;
constexpr int HEIGHT = 100;

int main() {
  Screen screen(WIDTH, HEIGHT);

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      screen.writePixel(x, y, 255, 255, 255);
    }
  }
  Vector3df Test = {1.f, 2.f, 3.f};
  screen.save("../output/render.ppm");


  return 0;
}

